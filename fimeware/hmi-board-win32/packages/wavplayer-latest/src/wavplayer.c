/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2019-07-15     Zero-Free    first implementation
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <wavhdr.h>
#include <wavplayer.h>
#include <unistd.h>
#include <dfs_file.h>

#include "pwm_audio.h"

#define DBG_TAG              "WAV_PLAYER"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#define VOLUME_MIN (-16)
#define VOLUME_MAX (16)

#define WP_BUFFER_SIZE (2048)
#define WP_VOLUME_DEFAULT (0)
#define WP_MSG_SIZE (10)
#define WP_THREAD_STATCK_SIZE (2048)
#define WP_THREAD_PRIORITY (15)

#define __Map(x, in_min, in_max, out_min, out_max) \
    (((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min))

enum MSG_TYPE
{
    MSG_NONE   = 0,
    MSG_START  = 1,
    MSG_STOP   = 2,
    MSG_PAUSE  = 3,
    MSG_RESUME = 4,
};

enum PLAYER_EVENT
{
    PLAYER_EVENT_NONE   = 0,
    PLAYER_EVENT_PLAY   = 1,
    PLAYER_EVENT_STOP   = 2,
    PLAYER_EVENT_PAUSE  = 3,
    PLAYER_EVENT_RESUME = 4,
};

struct play_msg
{
    int type;
    void *data;
};

struct wavplayer
{
    int state;
    char *uri;
    char *buffer;
    size_t BytesRD;
    uint16_t progress;
    rt_mq_t mq;
    rt_mutex_t lock;
    struct rt_completion ack;
    int fp;
    int volume;
};

struct wav_headers
{
    int   riff_datasize;                    /* RIFF chunk data size,exclude riff_id[4] and riff_datasize,total - 8 */
    int   fmt_avg_bytes_per_sec;            /* sample_rate * channels * bit_per_sample / 8 */
    int   data_datasize;                    /* data chunk size,pcm_size - 44 */
};

static struct wavplayer player;
static struct wav_headers wav_dt;

#if (DBG_LEVEL >= DBG_LOG)

static const char *state_str[] =
{
    "STOPPED",
    "PLAYING",
    "PAUSED",
};

static const char *event_str[] =
{
    "NONE",
    "PLAY"
    "STOP"
    "PAUSE"
    "RESUME"
};

#endif

static void play_lock(void)
{
    rt_mutex_take(player.lock, RT_WAITING_FOREVER);
}

static void play_unlock(void)
{
    rt_mutex_release(player.lock);
}

static rt_err_t play_msg_send(struct wavplayer *player, int type, void *data)
{
    struct play_msg msg;

    msg.type = type;
    msg.data = data;

    return rt_mq_send(player->mq, &msg, sizeof(struct play_msg));
}

int wavplayer_play(char *uri)
{
    rt_err_t result = RT_EOK;

    rt_completion_init(&player.ack);

    play_lock();
    if (player.state != PLAYER_STATE_STOPED)
    {
        wavplayer_stop();
    }
    if (player.uri)
    {
        rt_free(player.uri);
    }
    player.uri = rt_strdup(uri);
    result = play_msg_send(&player, MSG_START, RT_NULL);
    rt_completion_wait(&player.ack, RT_WAITING_FOREVER);
    play_unlock();

    return result;
}

int wavplayer_stop(void)
{
    rt_err_t result = RT_EOK;

    rt_completion_init(&player.ack);

    play_lock();
    if (player.state != PLAYER_STATE_STOPED)
    {
        result = play_msg_send(&player, MSG_STOP, RT_NULL);
        rt_completion_wait(&player.ack, RT_WAITING_FOREVER);
    }
    play_unlock();

    return result;
}

int wavplayer_pause(void)
{
    rt_err_t result = RT_EOK;

    rt_completion_init(&player.ack);

    play_lock();
    if (player.state == PLAYER_STATE_PLAYING)
    {
        result = play_msg_send(&player, MSG_PAUSE, RT_NULL);
        rt_completion_wait(&player.ack, RT_WAITING_FOREVER);
    }
    play_unlock();

    return result;
}

int wavplayer_resume(void)
{
    rt_err_t result = RT_EOK;

    rt_completion_init(&player.ack);

    play_lock();
    if (player.state == PLAYER_STATE_PAUSED)
    {
        result = play_msg_send(&player, MSG_RESUME, RT_NULL);
        rt_completion_wait(&player.ack, RT_WAITING_FOREVER);
    }
    play_unlock();

    return result;
}

int wavplayer_volume_set(int volume)
{
    struct rt_audio_caps caps;

    if (volume < VOLUME_MIN)
        volume = VOLUME_MIN;
    else if (volume > VOLUME_MAX)
        volume = VOLUME_MAX;

    player.volume = volume;
    caps.main_type = AUDIO_TYPE_MIXER;
    caps.sub_type  = AUDIO_MIXER_VOLUME;
    caps.udata.value = volume;

    return pwm_audio_set_volume(volume);;
}

int wavplayer_volume_get(void)
{
    return player.volume;
}

int wavplayer_state_get(void)
{
    return player.state;
}

char *wavplayer_uri_get(void)
{
    return player.uri;
}

unsigned char wavplayer_progress_get(void)
{
    return player.progress;
}

#include "pwm_audio.h"
static void audio_init()
{
    pwm_audio_config_t pac;
    pac.duty_resolution    = 10;
    pac.gpio_num_left      = 1;
    pac.gpio_num_right     = -1;
    pac.ringbuf_len        = 1024 * 8;

    pwm_audio_init(&pac);    
}

static rt_err_t wavplayer_open(struct wavplayer *player)
{
    rt_err_t result = RT_EOK;
    struct rt_audio_caps caps;
    struct wav_header wav;

    /* find device */
    /* open file */
    player->fp = open(player->uri, O_RDONLY);
    if (player->fp < 0)
    {
        LOG_E("open file %s failed", player->uri);
        result = -RT_ERROR;
        goto __exit;
    }
	
    /* Audio Init */
    audio_init();

    LOG_I("open wavplayer, device %s", PKG_WP_PLAY_DEVICE);
    /* read wavfile header information from file */
    wavheader_read(&wav, player->fp);

    LOG_I("Information:");
    LOG_I("samplerate %d", wav.fmt_sample_rate);
    LOG_I("channels %d", wav.fmt_channels);
    LOG_I("sample bits width %d", wav.fmt_bit_per_sample);

    /* set sampletate,channels, samplebits */
    caps.main_type = AUDIO_TYPE_OUTPUT;
    caps.sub_type  = AUDIO_DSP_PARAM;
    caps.udata.config.samplerate = wav.fmt_sample_rate;
    caps.udata.config.channels = wav.fmt_channels;
    caps.udata.config.samplebits = wav.fmt_bit_per_sample;
    
    wav_dt.data_datasize = wav.data_datasize;
    wav_dt.fmt_avg_bytes_per_sec = wav.fmt_avg_bytes_per_sec;
    wav_dt.riff_datasize = wav.riff_datasize;

    pwm_audio_set_param(wav.fmt_sample_rate, wav.fmt_bit_per_sample, wav.fmt_channels);

    /* set volume according to configuration */
    caps.main_type = AUDIO_TYPE_MIXER;
    caps.sub_type  = AUDIO_MIXER_VOLUME;
    caps.udata.value = player->volume;
    pwm_audio_set_volume(player->volume);

    return RT_EOK;

__exit:
    if (player->fp)
    {
        close(player->fp);
    }

    pwm_audio_deinit();

    return result;
}


static void wavplayer_close(struct wavplayer *player)
{
    if (player->fp)
    {
        close(player->fp);
    }

    pwm_audio_deinit();
    
    player->BytesRD = 0;

    LOG_I("close wavplayer");
}

static int wavplayer_event_handler(struct wavplayer *player, int timeout)
{
    int event;
    rt_err_t result;
    struct play_msg msg;
#if (DBG_LEVEL >= DBG_LOG)
    rt_uint8_t last_state;
#endif

    result = rt_mq_recv(player->mq, &msg, sizeof(struct play_msg), timeout);
    if (result == RT_NULL)
    {
        event = PLAYER_EVENT_NONE;
        return event;
    }

#if (DBG_LEVEL >= DBG_LOG)
    last_state = player->state;
#endif

    switch (msg.type)
    {
    case MSG_START:
        event = PLAYER_EVENT_PLAY;
        player->state = PLAYER_STATE_PLAYING;
        break;

    case MSG_STOP:
        event = PLAYER_EVENT_STOP;
        player->state = PLAYER_STATE_STOPED;
        break;

    case MSG_PAUSE:
        event = PLAYER_EVENT_PAUSE;
        player->state = PLAYER_STATE_PAUSED;
        break;

    case MSG_RESUME:
        event = PLAYER_EVENT_NONE;
        player->state = PLAYER_STATE_PLAYING;
        break;

    default:
        event = PLAYER_EVENT_NONE;
        break;
    }

    rt_completion_done(&player->ack);
#if (DBG_LEVEL >= DBG_LOG)
    LOG_I("EVENT:%s, STATE:%s -> %s", event_str[event], state_str[last_state], state_str[player->state]);
#endif

    return event;
}

static void wavplayer_entry(void *parameter)
{
    rt_err_t result = RT_EOK;
    rt_int32_t size;
    int event;
    uint16_t process;

    player.buffer = rt_malloc(WP_BUFFER_SIZE);
    if (player.buffer == RT_NULL)
        return;
    rt_memset(player.buffer, 0, WP_BUFFER_SIZE);

    player.mq = rt_mq_create("wav_p", sizeof(struct play_msg), 10, RT_IPC_FLAG_PRIO);
    if (player.mq == RT_NULL)
        goto __exit;

    player.lock = rt_mutex_create("wav_p", RT_IPC_FLAG_PRIO);
    if (player.lock == RT_NULL)
        goto __exit;

    player.volume = WP_VOLUME_DEFAULT;

    while (1)
    {
        /* wait play event forever */
        event = wavplayer_event_handler(&player, RT_WAITING_FOREVER);
        if (event != PLAYER_EVENT_PLAY)
            continue;

        /* open wavplayer */
        result = wavplayer_open(&player);
        if (result != RT_EOK)
        {
            player.state = PLAYER_STATE_STOPED;
            LOG_I("open wav player failed");
            continue;
        }

        LOG_I("play start, uri=%s", player.uri);
        while (1)
        {
            event = wavplayer_event_handler(&player, RT_WAITING_NO);

            switch (event)
            {
            case PLAYER_EVENT_NONE:
            {
                /* read raw data from file stream */
                size = read(player.fp, player.buffer, WP_BUFFER_SIZE);
                player.BytesRD += size + 8;
                process = ((double)player.BytesRD / wav_dt.riff_datasize) * wav_dt.fmt_avg_bytes_per_sec;
                player.progress = __Map((int32_t)process, 0, wav_dt.fmt_avg_bytes_per_sec, 0, 100);
                
                if (size == 0)
                {
                    /* FILE END*/
                    player.state = PLAYER_STATE_STOPED;
                }
                else
                {
                    /*witte data to sound device*/
					size_t cnt;
					pwm_audio_write((uint8_t *)player.buffer, WP_BUFFER_SIZE, &cnt, 500);
                }
                break;
            }

            case PLAYER_EVENT_PAUSE:
            {
                /* wait resume or stop event forever */
                event = wavplayer_event_handler(&player, RT_WAITING_FOREVER);
            }

            default:
                break;
            }

            if (player.state == PLAYER_STATE_STOPED)
                break;
        }

        /* close wavplayer */
        wavplayer_close(&player);
        LOG_I("play end");
    }

__exit:
    if (player.buffer)
    {
        rt_free(player.buffer);
        player.buffer = RT_NULL;
    }

    if (player.mq)
    {
        rt_mq_delete(player.mq);
        player.mq = RT_NULL;
    }

    if (player.lock)
    {
        rt_mutex_delete(player.lock);
        player.lock = RT_NULL;
    }

	pwm_audio_deinit();
}


int wavplayer_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("wav_p",
                           wavplayer_entry,
                           RT_NULL,
                           WP_THREAD_STATCK_SIZE,
                           WP_THREAD_PRIORITY, 10);
    if (tid)
        rt_thread_startup(tid);

    return RT_EOK;
}

INIT_APP_EXPORT(wavplayer_init);

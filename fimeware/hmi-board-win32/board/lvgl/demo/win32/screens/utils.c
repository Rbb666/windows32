#include "player.h"
#include "wlan_mgnt.h"
#include "utils.h"
#include "lvgl.h"

#define DBG_TAG "WLAN"
#define DBG_LVL DBG_LOG

#include <rtdbg.h>

#define __Sizeof(arr) (sizeof(arr)/sizeof(arr[0]))

static struct rt_thread wifi_scan_thread;
static struct rt_thread wifi_connect_thread;
static rt_uint8_t wifi_scan_thread_stack[2048];
static rt_uint8_t wifi_connect_thread_stack[1024];
static wifi_info_t Wifi_Info;

wifi_info_t Wifi_InfoS[20];
int wifi_index = 0;

void PageDelay(uint32_t ms)
{
    uint32_t lastTime = lv_tick_get();

    while (lv_tick_elaps(lastTime) <= ms)
    {
        lv_task_handler();
        rt_thread_mdelay(LV_DISP_DEF_REFR_PERIOD);
    }
}

static rt_err_t wifi_scan_result_cache(struct rt_wlan_info *info)
{
    rt_err_t err = RT_EOK;
    if ((info == RT_NULL) || (info->ssid.len == 0)) return -RT_EINVAL;
    LOG_D("ssid:%s len:%d mac:%02x:%02x:%02x:%02x:%02x:%02x", info->ssid.val, info->ssid.len,
          info->bssid[0], info->bssid[1], info->bssid[2], info->bssid[3], info->bssid[4], info->bssid[5]);
    return err;
}

static void user_ap_info_callback(int event, struct rt_wlan_buff *buff, void *parameter)
{
    struct rt_wlan_info *info = RT_NULL;
    int ret = RT_EOK;

    RT_ASSERT(event == RT_WLAN_EVT_SCAN_REPORT);
    RT_ASSERT(buff != RT_NULL);
    RT_ASSERT(parameter != RT_NULL);

    info = (struct rt_wlan_info *)buff->data;

    ret = wifi_scan_result_cache(info);
    if (ret == RT_EOK)
    {
        /*Print the info*/
        rt_sprintf(Wifi_InfoS[wifi_index].ssid, "%s", &(info->ssid.val[0]));
        LOG_I("Scan info :[%s]\n", Wifi_InfoS[wifi_index].ssid);
        wifi_index++;
    }
}

static void wifi_scan_thread_entry(void *parameter)
{
    struct rt_wlan_info *info = RT_NULL;
    int ret = 0;
    int i = 0;

    while (rt_wlan_get_mode(RT_WLAN_DEVICE_STA_NAME) != RT_WLAN_STATION)
    {
        rt_thread_mdelay(500);
    }

    ret = rt_wlan_register_event_handler(RT_WLAN_EVT_SCAN_REPORT, user_ap_info_callback, &i);
    if (ret != RT_EOK)
    {
        LOG_E("Scan register user callback error:%d!\n", ret);
        return;
    }
    /*Todo: what can i do for it return val */
    ret = rt_wlan_scan_with_info(info);
    if (ret != RT_EOK)
    {
        LOG_E("Scan with info error:%d!\n", ret);
        return;
    }
}

int WiFi_Scan(void)
{
    rt_err_t err;

    if ((wifi_scan_thread.stat & RT_THREAD_RUNNING) == RT_THREAD_RUNNING)
        return -1;

    err = rt_thread_init(&wifi_scan_thread, "WIFI_SCAN", wifi_scan_thread_entry, RT_NULL,
                         &wifi_scan_thread_stack[0], sizeof(wifi_scan_thread_stack), 22, 0);
    if (err != RT_EOK)
    {
        LOG_E("Failed to create WIFI thread");
        return -1;
    }

    rt_thread_startup(&wifi_scan_thread);
    return 0;
}

static void wifi_connect_thread_entry(void *parameter)
{
    wifi_info_t *wf = (wifi_info_t *)parameter;
    int ret = rt_wlan_connect(wf->ssid, wf->password);
    LOG_I("ssid: %s pwd: %s", wf->ssid, wf->password);
}

int WiFi_Join(const char *ssid, const char *password)
{
    rt_err_t err;
    if ((wifi_connect_thread.stat & RT_THREAD_RUNNING) == RT_THREAD_RUNNING)
        return -1;
//    Wifi_Info.ssid = (char *)ssid;
//    Wifi_Info.password = (char *)password;
    err = rt_thread_init(&wifi_connect_thread, "WIFI_JOIN", wifi_connect_thread_entry, &Wifi_Info,
                         &wifi_connect_thread_stack[0], sizeof(wifi_connect_thread_stack), 22, 0);
    if (err != RT_EOK)
    {
        LOG_E("Failed to create WIFI thread");
        return -1;
    }
    rt_thread_startup(&wifi_connect_thread);
    return 0;
}

void palyer_list_clear(player_t p)
{
    LOG_I("palyer_list_clear..");
    p->song_current = 0;
    p->video_num = 0;
    int i;
    for (i = 0; i < __Sizeof(p->video_list); i++)
    {
        if (p->video_list[i] != RT_NULL)
        {
            LOG_I("DEL: %s", p->video_list[i]);
            p->video_list[i] = RT_NULL;
        }
    }
}

void play_video(const char *video_name)
{
	palyer_list_clear(&v_player);
	player_control(&v_player, PLAYER_CMD_INIT, (char *)video_name);
}

void exit_play_video(void)
{
	player_control(&v_player, PLAYER_CMD_DELETE, RT_NULL);
}

#include "utils.h"
#include "lvgl.h"
#include "ui.h"

#define DBG_TAG "WLAN"
#define DBG_LVL DBG_LOG

#include <rtdbg.h>

typedef struct wifi
{
    char *ssid;
    char *password;
} wifi_info;

static struct rt_thread wifi_scan_thread;
static struct rt_thread wifi_connect_thread;
static rt_uint8_t wifi_scan_thread_stack[2048];
static rt_uint8_t wifi_connect_thread_stack[1024];
static wifi_info Info;

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
    wifi_info *wf = (wifi_info *)parameter;
    rt_wlan_connect(wf->ssid, wf->password);
    LOG_I("ssid: %s pwd: %s", wf->ssid, wf->password);
}

int WiFi_Join(const char *ssid, const char *password)
{
    rt_err_t err;
    if ((wifi_connect_thread.stat & RT_THREAD_RUNNING) == RT_THREAD_RUNNING)
        return -1;
    Info.ssid = (char *)ssid;
    Info.password = (char *)password;
    err = rt_thread_init(&wifi_connect_thread, "WIFI_JOIN", wifi_connect_thread_entry, &Info,
                         &wifi_connect_thread_stack[0], sizeof(wifi_connect_thread_stack), 22, 0);
    if (err != RT_EOK)
    {
        LOG_E("Failed to create WIFI thread");
        return -1;
    }
    rt_thread_startup(&wifi_connect_thread);
    return 0;
}

void lv_amin_start(void *obj,
                   int32_t start_value,
                   int32_t end_value,
                   uint32_t repeat_count,
                   uint32_t duration,
                   uint32_t delay,
                   lv_anim_exec_xcb_t exec_cb,
                   lv_anim_path_cb_t path_cb)
{
    lv_anim_t anim;
    lv_anim_init(&anim);
    lv_anim_set_var(&anim, obj);
    lv_anim_set_values(&anim, start_value, end_value);
    lv_anim_set_repeat_count(&anim, repeat_count);
    lv_anim_set_exec_cb(&anim, exec_cb);
    lv_anim_set_time(&anim, duration);
    lv_anim_set_delay(&anim, delay);
    lv_anim_set_path_cb(&anim, path_cb);
    lv_anim_start(&anim);
}

void wifi_show_ui(void)
{
    uint16_t i = 0, ops_y = 0, duration = 0;

    if (rt_wlan_is_connected() == RT_TRUE)
    {
        wifiname_list_btn = lv_list_add_btn(ui_main_network_panel, RT_NULL, Wifi_InfoS[wifi_index].ssid);
        lv_obj_set_size(wifiname_list_btn, 250, 25);
        lv_obj_align(wifiname_list_btn, LV_ALIGN_TOP_MID, 0, ops_y);
        lv_obj_clear_flag(wifiname_list_btn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
        lv_obj_set_style_radius(wifiname_list_btn, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_color(wifiname_list_btn, lv_color_hex(0x565656), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(wifiname_list_btn, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(wifiname_list_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

        lv_obj_t *label = lv_obj_get_child(wifiname_list_btn, 0);
        lv_obj_set_style_text_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(label, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_wifi_icon = lv_img_create(wifiname_list_btn);
        lv_img_set_src(ui_wifi_icon, &ui_img_wifi_png);
        lv_obj_set_width(ui_wifi_icon, LV_SIZE_CONTENT);   /// 1
        lv_obj_set_height(ui_wifi_icon, LV_SIZE_CONTENT);    /// 1
        lv_obj_set_align(ui_wifi_icon, LV_ALIGN_LEFT_MID);
        lv_obj_add_flag(ui_wifi_icon, LV_OBJ_FLAG_ADV_HITTEST);    /// Flags
        lv_obj_clear_flag(ui_wifi_icon, LV_OBJ_FLAG_SCROLLABLE);     /// Flags

        lv_amin_start(wifiname_list_btn, 100, 0,
                      1, 500 + duration, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, lv_anim_path_bounce);
    }
    else
    {
        for (i = 0, duration = 100, ops_y = 0; i < 8; i++, duration += 100, ops_y += 30)
        {
            wifiname_list_btn = lv_list_add_btn(ui_main_network_panel, RT_NULL, Wifi_InfoS[i].ssid);
            lv_obj_set_size(wifiname_list_btn, 250, 25);
            lv_obj_align(wifiname_list_btn, LV_ALIGN_TOP_MID, 0, ops_y);
            lv_obj_clear_flag(wifiname_list_btn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
            lv_obj_set_style_radius(wifiname_list_btn, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(wifiname_list_btn, lv_color_hex(0x565656), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(wifiname_list_btn, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(wifiname_list_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_add_event_cb(wifiname_list_btn, wifi_event_handler, LV_EVENT_CLICKED, NULL);

            lv_obj_t *label = lv_obj_get_child(wifiname_list_btn, 0);
            lv_obj_set_style_text_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(label, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

            ui_wifi_icon = lv_img_create(wifiname_list_btn);
            lv_img_set_src(ui_wifi_icon, &ui_img_wifi_png);
            lv_obj_set_width(ui_wifi_icon, LV_SIZE_CONTENT);   /// 1
            lv_obj_set_height(ui_wifi_icon, LV_SIZE_CONTENT);    /// 1
            lv_obj_set_align(ui_wifi_icon, LV_ALIGN_LEFT_MID);
            lv_obj_add_flag(ui_wifi_icon, LV_OBJ_FLAG_ADV_HITTEST);    /// Flags
            lv_obj_clear_flag(ui_wifi_icon, LV_OBJ_FLAG_SCROLLABLE);     /// Flags

            lv_amin_start(wifiname_list_btn, 100, 0,
                          1, 500 + duration, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, lv_anim_path_bounce);
        }
    }
}

void backlight_setvalue(int value)
{
#define LCD_PWM_DEV_NAME    "pwm5"
#define LCD_PWM_DEV_CHANNEL 0

    struct rt_device_pwm *pwm_dev;

    if (value < 3000) value = 3000;
    /* turn on the LCD backlight */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(LCD_PWM_DEV_NAME);
    /* pwm frequency:100K = 10000ns */
    rt_pwm_set(pwm_dev, LCD_PWM_DEV_CHANNEL, 10000, value);
    rt_pwm_enable(pwm_dev, LCD_PWM_DEV_CHANNEL);
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
            rt_free(p->video_list[i]);
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

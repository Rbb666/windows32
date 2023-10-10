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
        // LOG_I("Scan info :[%s]\n", Wifi_InfoS[wifi_index].ssid);
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
        rt_thread_mdelay(200);
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
    wifi_show_ui();
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

void scalewin_Animation2(lv_obj_t *TargetObject, int delay, int direction)
{
    ui_anim_user_data_t *PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_width);
    lv_anim_set_values(&PropertyAnimation_0, 0, direction);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_width);
    lv_anim_start(&PropertyAnimation_0);
    ui_anim_user_data_t *PropertyAnimation_1_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_1_user_data->target = TargetObject;
    PropertyAnimation_1_user_data->val = -1;
    lv_anim_t PropertyAnimation_1;
    lv_anim_init(&PropertyAnimation_1);
    lv_anim_set_time(&PropertyAnimation_1, 500);
    lv_anim_set_user_data(&PropertyAnimation_1, PropertyAnimation_1_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_height);
    lv_anim_set_values(&PropertyAnimation_1, 0, direction);
    lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_1, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_1, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_1, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
    lv_anim_set_early_apply(&PropertyAnimation_1, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_1, &_ui_anim_callback_get_height);
    lv_anim_start(&PropertyAnimation_1);

}

void wifi_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED)
    {
        const char *ssid = lv_list_get_btn_text(ui_Network_panel, obj);
        LV_LOG_USER("Clicked: %s", ssid);
        for (int i = 0; i < __Sizeof(Wifi_InfoS); i++)
        {
            if (rt_strcmp(ssid, Wifi_InfoS[i].ssid) == 0)
            {
                wifi_index = i;
                break;
            }
        }
        //lv_label_set_text(ui_wifiTextArea, s);
        _ui_opacity_set(ui_wifi_input_panel, 0);
        _ui_flag_modify(ui_wifi_input_panel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        fadein_Animation(ui_wifi_input_panel, 0);
    }
}

void wifi_show_ui(void)
{
    uint16_t i = 0, ops_y = 0, duration = 0;

    if (rt_wlan_is_connected() == RT_TRUE)
    {
        wifiname_list_btn = lv_list_add_btn(ui_Network_panel, RT_NULL, Wifi_InfoS[wifi_index].ssid);
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
        lv_obj_set_y(ui_wifi_icon, -2);
        lv_obj_add_flag(ui_wifi_icon, LV_OBJ_FLAG_ADV_HITTEST);    /// Flags
        lv_obj_clear_flag(ui_wifi_icon, LV_OBJ_FLAG_SCROLLABLE);     /// Flags

        lv_amin_start(wifiname_list_btn, 100, 0,
                      1, 500 + duration, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, lv_anim_path_bounce);
    }
    else
    {
        for (i = 0, duration = 100, ops_y = 0; i < 8; i++, duration += 100, ops_y += 30)
        {
            wifiname_list_btn = lv_list_add_btn(ui_Network_panel, RT_NULL, Wifi_InfoS[i].ssid);
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
//    palyer_list_clear(&v_player);
//    player_control(&v_player, PLAYER_CMD_INIT, (char *)video_name);
}

void exit_play_video(void)
{
//    player_control(&v_player, PLAYER_CMD_DELETE, RT_NULL);
}

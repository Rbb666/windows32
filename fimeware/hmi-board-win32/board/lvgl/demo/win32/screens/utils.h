#ifndef __UTILS_H
#define __UTILS_H

#include <rtthread.h>
#include <rtdevice.h>
#include <ctype.h>

#include "player.h"
#include "wlan_mgnt.h"
#include <wavplayer.h>
#include "lv_file_explorer.h"

#define __Sizeof(arr) (sizeof(arr)/sizeof(arr[0]))

#define __Map(x, in_min, in_max, out_min, out_max) \
    (((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min))

typedef struct wifi_info
{
    char ssid[24];
    char password[24];
} wifi_info_t;

extern wifi_info_t Wifi_InfoS[20];
extern struct player v_player;
extern int wifi_index;
extern uint8_t *v_pbuffer;

extern char *alarm_temp_data;
extern char *alarm_humi_data;

void PageDelay(uint32_t ms);
void extract_numbers(const char *input_str, char *output_str, int output_str_length);
int WiFi_Scan(void);
void backlight_setvalue(int value);
void play_video(const char *video_name);
void exit_play_video(void);
void wifi_show_ui(lv_obj_t *obj);
int WiFi_Join(const char *ssid, const char *password);
void scalewin_Animation2(lv_obj_t *TargetObject, int delay, int direction);

extern lv_obj_t *wifiname_list_btn;
extern lv_obj_t *ui_wifi_icon;

extern void ui_acquire(void);
extern void ui_release(void);

LV_IMG_DECLARE(ui_img_wifi_png);    // assets\wifi.png

#endif

#ifndef __UTILS_H
#define __UTILS_H

#include <rtthread.h>
#include <rtdevice.h>

#include "player.h"
#include "wlan_mgnt.h"
#include <wavplayer.h>
#include "lv_file_explorer.h"

#define __Sizeof(arr) (sizeof(arr)/sizeof(arr[0]))

typedef struct wifi_info
{
    char ssid[24];
    char password[24];
} wifi_info_t;

extern wifi_info_t Wifi_InfoS[20];
extern struct player v_player;
extern int wifi_index;
extern uint8_t *v_pbuffer;

void PageDelay(uint32_t ms);
int WiFi_Scan(void);
void backlight_setvalue(int value);
void play_video(const char *video_name);
void exit_play_video(void);
void wifi_show_ui(void);
int WiFi_Join(const char *ssid, const char *password);

#endif

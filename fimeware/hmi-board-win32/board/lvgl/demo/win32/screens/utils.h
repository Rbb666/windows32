#ifndef __UTILS_H
#define __UTILS_H

#include <rtthread.h>

typedef struct wifi_info
{
    char ssid[24];
    char password[24];
} wifi_info_t;

extern struct player v_player;
extern wifi_info_t Wifi_InfoS[20];
extern int wifi_index;

void PageDelay(uint32_t ms);
int WiFi_Scan(void);
void play_video(const char *video_name);
void exit_play_video(void);

#endif

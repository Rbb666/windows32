#ifndef __UTILS_H
#define __UTILS_H

typedef struct wifi_info
{
    char ssid[24];
    char password[24];
} wifi_info_t;

extern wifi_info_t Wifi_InfoS[20];
extern int wifi_index;

#endif

// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#ifndef _UI_EVENTS_H
#define _UI_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

void shutdown_music(lv_event_t * e);
void switch_player1_func(lv_event_t * e);
void switch_player2_func(lv_event_t * e);
void play_next_music(lv_event_t * e);
void play_music_function(lv_event_t * e);
void pause_music_function(lv_event_t * e);
void play_pre_music(lv_event_t * e);
void move_video_panel_to_left(lv_event_t * e);
void backlight_slider_event_cb(lv_event_t * e);
void voice_slider_event_cb(lv_event_t * e);
void connect_wifi_event(lv_event_t * e);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

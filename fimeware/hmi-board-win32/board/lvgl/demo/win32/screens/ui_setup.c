// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"
#include "utils.h"

struct player v_player;
static lv_timer_t *timer;
extern int WiFi_Scan(void);

void video_timer(lv_timer_t *timer)
{
    _ui_screen_change(&ui_main, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_main_screen_init);
}

void ui_setup_screen_init(void)
{
    ui_setup = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_setup, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_setup, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_setup, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_setup, ui_event_setup, LV_EVENT_ALL, NULL);
    player_start(&v_player);
    player_control(&v_player, PLAYER_CMD_INIT, "video/start.avi");
    timer = lv_timer_create(video_timer, 5500, NULL);
    lv_timer_set_repeat_count(timer, 1);
    WiFi_Scan();
}

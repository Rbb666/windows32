// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "components/ui_comp.h"
#include "components/ui_comp_hook.h"
#include "ui_events.h"
#include "utils.h"
void turnon_Animation(lv_obj_t *TargetObject, int delay);
void passed_Animation(lv_obj_t *TargetObject, int delay);
void turndown_Animation(lv_obj_t *TargetObject, int delay);
void turnupkeyboard_Animation(lv_obj_t *TargetObject, int delay);
void scalewin_Animation(lv_obj_t *TargetObject, int delay);
void openwin_Animation(lv_obj_t *TargetObject, int delay);
void fadeout_Animation(lv_obj_t *TargetObject, int delay);
void fadein_Animation(lv_obj_t *TargetObject, int delay);
void EjectRight_Animation(lv_obj_t *TargetObject, int delay);
void EjectLeft_Animation(lv_obj_t *TargetObject, int delay);
void amplify_Animation(lv_obj_t *TargetObject, int delay);
void reduce_Animation(lv_obj_t *TargetObject, int delay);
void cardin_Animation(lv_obj_t *TargetObject, int delay);
void bloodL_Animation(lv_obj_t *TargetObject, int delay);
void bloodR_Animation(lv_obj_t *TargetObject, int delay);
void movetoleft_Animation(lv_obj_t *TargetObject, int delay);
void movetocenter_Animation(lv_obj_t *TargetObject, int delay);
void albumrotate_Animation(lv_obj_t *TargetObject, int delay);
void albumleft_Animation(lv_obj_t *TargetObject, int delay);
void albumright_Animation(lv_obj_t *TargetObject, int delay);
void photoleft_Animation(lv_obj_t *TargetObject, int delay);
void photoright_Animation(lv_obj_t *TargetObject, int delay);
// SCREEN: ui_setup
void ui_setup_screen_init(void);
void ui_event_setup(lv_event_t *e);
extern lv_obj_t *ui_setup;
// SCREEN: ui_main
void ui_main_screen_init(void);
void ui_event_main(lv_event_t *e);
extern lv_obj_t *ui_main;
extern lv_obj_t *ui_wallpaper_main_img;
extern lv_obj_t *ui_Panel1;
void ui_event_win_btn(lv_event_t *e);
extern lv_obj_t *ui_win_btn;
void ui_event_file_btn(lv_event_t *e);
extern lv_obj_t *ui_file_btn;
void ui_event_button_panel(lv_event_t *e);
extern lv_obj_t *ui_button_panel;
void ui_event_wifi(lv_event_t *e);
extern lv_obj_t *ui_wifi;
void ui_event_voice(lv_event_t *e);
extern lv_obj_t *ui_voice;
extern lv_obj_t *ui_time;
extern lv_obj_t *ui_Setting_Pannel;
void ui_event_sys_display_panel(lv_event_t *e);
extern lv_obj_t *ui_sys_display_panel;
extern lv_obj_t *ui_Image4;
extern lv_obj_t *ui_Label5;
void ui_event_sys_win_panel(lv_event_t *e);
extern lv_obj_t *ui_sys_win_panel;
extern lv_obj_t *ui_Image1;
extern lv_obj_t *ui_Label2;
void ui_event_sys_network_panel(lv_event_t *e);
extern lv_obj_t *ui_sys_network_panel;
extern lv_obj_t *ui_Image2;
extern lv_obj_t *ui_Label3;
void ui_event_sys_info_panel(lv_event_t *e);
extern lv_obj_t *ui_sys_info_panel;
extern lv_obj_t *ui_Image3;
extern lv_obj_t *ui_Label4;
extern lv_obj_t *ui_sys_main_panel;
extern lv_obj_t *ui_main_display_panel;
void ui_event_set_wallpaper_panel(lv_event_t *e);
extern lv_obj_t *ui_set_wallpaper_panel;
extern lv_obj_t *ui_wallpaper_text;
extern lv_obj_t *ui_img_right1;
void ui_event_set_backlight_panel(lv_event_t *e);
extern lv_obj_t *ui_set_backlight_panel;
extern lv_obj_t *ui_backlight_text;
extern lv_obj_t *ui_img_right2;
void ui_event_set_resolution_panel(lv_event_t *e);
extern lv_obj_t *ui_set_resolution_panel;
extern lv_obj_t *ui_backlight_text1;
extern lv_obj_t *ui_Dropdown1;
extern lv_obj_t *ui_main_win_panel;
void ui_event_Disk_panel(lv_event_t *e);
extern lv_obj_t *ui_Disk_panel;
extern lv_obj_t *ui_disk_letter;
extern lv_obj_t *ui_disk_img;
extern lv_obj_t *ui_disk_free_img;
extern lv_obj_t *ui_disk_storge_text;
void ui_event_download_panel(lv_event_t *e);
extern lv_obj_t *ui_download_panel;
extern lv_obj_t *ui_download_img;
extern lv_obj_t *ui_download_letter1;
extern lv_obj_t *ui_fixation;
void ui_event_desktop_panel(lv_event_t *e);
extern lv_obj_t *ui_desktop_panel;
extern lv_obj_t *ui_desktop_img;
extern lv_obj_t *ui_desktop_letter1;
extern lv_obj_t *ui_fixation1;
void ui_event_photo_panel(lv_event_t *e);
extern lv_obj_t *ui_photo_panel;
extern lv_obj_t *ui_desktop_img1;
extern lv_obj_t *ui_photo_letter1;
extern lv_obj_t *ui_fixation2;
void ui_event_main_filesys_panel(lv_event_t *e);
extern lv_obj_t *ui_main_filesys_panel;
extern lv_obj_t *ui_main_network_panel;
extern lv_obj_t *ui_wifi_icon;
extern lv_obj_t *ui_main_info_panel;
extern lv_obj_t *ui_blood_group;
extern lv_obj_t *ui_wave_img1;
extern lv_obj_t *ui_wave_img;
extern lv_obj_t *ui_title;
extern lv_obj_t *ui_company;
extern lv_obj_t *ui_position;
extern lv_obj_t *ui_link;
extern lv_obj_t *ui_Label7;
extern lv_obj_t *ui_Label1;
extern lv_obj_t *ui_Label8;
extern lv_obj_t *ui_position1;
extern lv_obj_t *ui_position2;
extern lv_obj_t *ui_position3;
extern lv_obj_t *ui_back_panel;
void ui_event_close(lv_event_t *e);
extern lv_obj_t *ui_close;
void ui_event_scale(lv_event_t *e);
extern lv_obj_t *ui_scale;
void ui_event_hide(lv_event_t *e);
extern lv_obj_t *ui_hide;
extern lv_obj_t *ui_Head;
extern lv_obj_t *ui_name;
extern lv_obj_t *ui_panel_name;
void ui_event_music_panel(lv_event_t *e);
extern lv_obj_t *ui_music_panel;
extern lv_obj_t *ui_album;
void ui_event_album_card2(lv_event_t *e);
extern lv_obj_t *ui_album_card2;
void ui_event_album_card1(lv_event_t *e);
extern lv_obj_t *ui_album_card1;
extern lv_obj_t *ui_music_title;
extern lv_obj_t *ui_author;
void ui_event_next_song(lv_event_t *e);
extern lv_obj_t *ui_next_song;
void ui_event_play(lv_event_t *e);
extern lv_obj_t *ui_play;
void ui_event_pre_song(lv_event_t *e);
extern lv_obj_t *ui_pre_song;
extern lv_obj_t *ui_music_process;
extern lv_obj_t *ui_collect;
extern lv_obj_t *ui_talking;
extern lv_obj_t *ui_download;
void ui_event_photos_panel(lv_event_t *e);
extern lv_obj_t *ui_photos_panel;
void ui_event_photo_s1(lv_event_t *e);
extern lv_obj_t *ui_photo_s1;
void ui_event_photo_s2(lv_event_t *e);
extern lv_obj_t *ui_photo_s2;
void ui_event_photo_s3(lv_event_t *e);
extern lv_obj_t *ui_photo_s3;
void ui_event_photo_s5(lv_event_t *e);
extern lv_obj_t *ui_photo_s5;
extern lv_obj_t *ui_album_panel;
void ui_event_photo_album5(lv_event_t *e);
extern lv_obj_t *ui_photo_album5;
void ui_event_photo_album4(lv_event_t *e);
extern lv_obj_t *ui_photo_album4;
void ui_event_photo_album3(lv_event_t *e);
extern lv_obj_t *ui_photo_album3;
void ui_event_photo_album2(lv_event_t *e);
extern lv_obj_t *ui_photo_album2;
extern lv_obj_t *ui_magnification;
extern lv_obj_t *ui_photo_scroll;
void ui_event_photo_small2(lv_event_t *e);
extern lv_obj_t *ui_photo_small2;
void ui_event_photo_small3(lv_event_t *e);
extern lv_obj_t *ui_photo_small3;
void ui_event_photo_small4(lv_event_t *e);
extern lv_obj_t *ui_photo_small4;
void ui_event_photo_small5(lv_event_t *e);
extern lv_obj_t *ui_photo_small5;
extern lv_obj_t *ui_amplify;
extern lv_obj_t *ui_reduce;
extern lv_obj_t *ui_photo_icon;
void ui_event_photo_close(lv_event_t *e);
extern lv_obj_t *ui_photo_close;
void ui_event_video_panel(lv_event_t *e);
extern lv_obj_t *ui_video_panel;
void ui_event_video_01(lv_event_t *e);
extern lv_obj_t *ui_video_01;
extern lv_obj_t *ui_video_title_img1;
extern lv_obj_t *ui_days1;
extern lv_obj_t *ui_resolution1;
extern lv_obj_t *ui_Label9;
extern lv_obj_t *ui_video_name1;
void ui_event_video_02(lv_event_t *e);
extern lv_obj_t *ui_video_02;
extern lv_obj_t *ui_video_title_img2;
extern lv_obj_t *ui_days2;
extern lv_obj_t *ui_resolution2;
extern lv_obj_t *ui_Label6;
extern lv_obj_t *ui_video_name2;
void ui_event_video_03(lv_event_t *e);
extern lv_obj_t *ui_video_03;
extern lv_obj_t *ui_video_title_img3;
extern lv_obj_t *ui_days3;
extern lv_obj_t *ui_resolution3;
extern lv_obj_t *ui_Label10;
extern lv_obj_t *ui_video_name3;
void ui_event_video_04(lv_event_t *e);
extern lv_obj_t *ui_video_04;
extern lv_obj_t *ui_video_title_img4;
extern lv_obj_t *ui_days4;
extern lv_obj_t *ui_resolution4;
extern lv_obj_t *ui_Label11;
extern lv_obj_t *ui_video_name4;
void ui_event_video_player_panel(lv_event_t *e);
extern lv_obj_t *ui_video_player_panel;
extern lv_obj_t *ui_system_ctrl_panel;
void ui_event_wifi_control(lv_event_t *e);
extern lv_obj_t *ui_wifi_control;
extern lv_obj_t *ui_wifi_icon5;
extern lv_obj_t *ui_wifi_icon6;
extern lv_obj_t *ui_midline;
void ui_event_ble_control(lv_event_t *e);
extern lv_obj_t *ui_ble_control;
extern lv_obj_t *ui_ble_icon13;
extern lv_obj_t *ui_wifi_icon2;
extern lv_obj_t *ui_midline1;
extern lv_obj_t *ui_battery_control;
extern lv_obj_t *ui_ble_icon1;
extern lv_obj_t *ui_wifi_icon3;
extern lv_obj_t *ui_midline2;
extern lv_obj_t *ui_mode_control;
extern lv_obj_t *ui_ble_icon2;
extern lv_obj_t *ui_wifi_icon4;
extern lv_obj_t *ui_midline3;
void ui_event_backlight_control__slider(lv_event_t *e);
extern lv_obj_t *ui_backlight_control__slider;
void ui_event_voice_control__slider(lv_event_t *e);
extern lv_obj_t *ui_voice_control__slider;
extern lv_obj_t *ui_Image5;
extern lv_obj_t *ui_Image6;
extern lv_obj_t *ui_menu;
extern lv_obj_t *ui_search_img;
void ui_event_search_TextArea(lv_event_t *e);
extern lv_obj_t *ui_search_TextArea;
void ui_event_setting(lv_event_t *e);
extern lv_obj_t *ui_setting;
void ui_event_photo(lv_event_t *e);
extern lv_obj_t *ui_photo;
void ui_event_music(lv_event_t *e);
extern lv_obj_t *ui_music;
void ui_event_edge(lv_event_t *e);
extern lv_obj_t *ui_edge;
void ui_event_file(lv_event_t *e);
extern lv_obj_t *ui_file;
void ui_event_pc(lv_event_t *e);
extern lv_obj_t *ui_pc;
void ui_event_video(lv_event_t *e);
extern lv_obj_t *ui_video;
void ui_event_Keyboard(lv_event_t *e);
extern lv_obj_t *ui_Keyboard;
void ui_event_message_panel(lv_event_t *e);
extern lv_obj_t *ui_message_panel;
extern lv_obj_t *ui_wallpaper_setting;
void ui_event_wallpaper_img1(lv_event_t *e);
extern lv_obj_t *ui_wallpaper_img1;
void ui_event_wallpaper_img2(lv_event_t *e);
extern lv_obj_t *ui_wallpaper_img2;
extern lv_obj_t *ui_backlight_setting;
void ui_event_backlight_Slider(lv_event_t *e);
extern lv_obj_t *ui_backlight_Slider;
extern lv_obj_t *ui_wifi_input_panel;
void ui_event_wifiTextArea(lv_event_t *e);
extern lv_obj_t *ui_wifiTextArea;
void ui_event_cancel_btn(lv_event_t *e);
extern lv_obj_t *ui_cancel_btn;
extern lv_obj_t *ui_Label12;
void ui_event_cancel_btn1(lv_event_t *e);
extern lv_obj_t *ui_cancel_btn1;
extern lv_obj_t *ui_Label13;
extern lv_obj_t *ui____initial_actions0;
extern lv_obj_t *file_explorer_panel;
extern lv_obj_t *file_explorer_label;
extern lv_obj_t *wifiname_list_btn;
void file_explorer_event_cb(lv_event_t *e);
void wifi_event_handler(lv_event_t *e);

LV_IMG_DECLARE(ui_img_bg1_png);    // assets\bg1.png
LV_IMG_DECLARE(ui_img_win_png);    // assets\win.png
LV_IMG_DECLARE(ui_img_file_25x25_png);    // assets\file_25x25.png
LV_IMG_DECLARE(ui_img_wifi_15_png);    // assets\wifi_15.png
LV_IMG_DECLARE(ui_img_voice_png);    // assets\voice.png
LV_IMG_DECLARE(ui_img_display_png);    // assets\display.png
LV_IMG_DECLARE(ui_img_pc_png);    // assets\pc.png
LV_IMG_DECLARE(ui_img_network_png);    // assets\network.png
LV_IMG_DECLARE(ui_img_info_png);    // assets\info.png
LV_IMG_DECLARE(ui_img_right_png);    // assets\right.png
LV_IMG_DECLARE(ui_img_disk_png);    // assets\Disk.png
LV_IMG_DECLARE(ui_img_disk_storge_png);    // assets\disk_storge.png
LV_IMG_DECLARE(ui_img_forder_png);    // assets\forder.png
LV_IMG_DECLARE(ui_img_fixation_png);    // assets\fixation.png
LV_IMG_DECLARE(ui_img_desktop_png);    // assets\desktop.png
LV_IMG_DECLARE(ui_img_photo_icon_png);    // assets\photo_icon.png
LV_IMG_DECLARE(ui_img_wifi_png);    // assets\wifi.png
LV_IMG_DECLARE(ui_img_wave2_png);    // assets\wave2.png
LV_IMG_DECLARE(ui_img_wave1_png);    // assets\wave1.png
LV_IMG_DECLARE(ui_img_company_png);    // assets\company.png
LV_IMG_DECLARE(ui_img_position_png);    // assets\position.png
LV_IMG_DECLARE(ui_img_link_png);    // assets\link.png
LV_IMG_DECLARE(ui_img_star1_png);    // assets\star1.png
LV_IMG_DECLARE(ui_img_star2_png);    // assets\star2.png
LV_IMG_DECLARE(ui_img_close_png);    // assets\close.png
LV_IMG_DECLARE(ui_img_scale_png);    // assets\Scale.png
LV_IMG_DECLARE(ui_img_hide_png);    // assets\hide.png
LV_IMG_DECLARE(ui_img_head_png);    // assets\head.png
LV_IMG_DECLARE(ui_img_album2_png);    // assets\album2.png
LV_IMG_DECLARE(ui_img_album1_png);    // assets\album1.png
LV_IMG_DECLARE(ui_img_next_png);    // assets\next.png
LV_IMG_DECLARE(ui_img_play_png);    // assets\play.png
LV_IMG_DECLARE(ui_img_suspend_png);    // assets\suspend.png
LV_IMG_DECLARE(ui_img_play_png);    // assets\play.png
LV_IMG_DECLARE(ui_img_previous__png);    // assets\Previous .png
LV_IMG_DECLARE(ui_img_knob_png);    // assets\knob.png
LV_IMG_DECLARE(ui_img_like_png);    // assets\like.png
LV_IMG_DECLARE(ui_img_talk_png);    // assets\talk.png
LV_IMG_DECLARE(ui_img_download_png);    // assets\download.png
LV_IMG_DECLARE(ui_img_photo1_png);    // assets\photo1.png
LV_IMG_DECLARE(ui_img_photo2_png);    // assets\photo2.png
LV_IMG_DECLARE(ui_img_photo3_png);    // assets\photo3.png
LV_IMG_DECLARE(ui_img_photo5_png);    // assets\photo5.png
LV_IMG_DECLARE(ui_img_photo_3205_png);    // assets\photo_3205.png
LV_IMG_DECLARE(ui_img_photo_3204_png);    // assets\photo_3204.png
LV_IMG_DECLARE(ui_img_photo_3203_png);    // assets\photo_3203.png
LV_IMG_DECLARE(ui_img_photo_3202_png);    // assets\photo_3202.png
LV_IMG_DECLARE(ui_img_photos2_png);    // assets\photos2.png
LV_IMG_DECLARE(ui_img_photos3_png);    // assets\photos3.png
LV_IMG_DECLARE(ui_img_photos4_png);    // assets\photos4.png
LV_IMG_DECLARE(ui_img_photos5_png);    // assets\photos5.png
LV_IMG_DECLARE(ui_img_amplify_png);    // assets\amplify.png
LV_IMG_DECLARE(ui_img_reduce_png);    // assets\reduce.png
LV_IMG_DECLARE(ui_img_photo_icon_png);    // assets\photo icon.png
LV_IMG_DECLARE(ui_img_video1_png);    // assets\video1.png
LV_IMG_DECLARE(ui_img_video2_png);    // assets\video2.png
LV_IMG_DECLARE(ui_img_video3_png);    // assets\video3.png
LV_IMG_DECLARE(ui_img_video4_png);    // assets\video4.png
LV_IMG_DECLARE(ui_img_wifi_13_png);    // assets\wifi_13.png
LV_IMG_DECLARE(ui_img_ble_png);    // assets\ble.png
LV_IMG_DECLARE(ui_img_battary_png);    // assets\battary.png
LV_IMG_DECLARE(ui_img_plane_png);    // assets\plane.png
LV_IMG_DECLARE(ui_img_sun_png);    // assets\sun.png
LV_IMG_DECLARE(ui_img_speaker_png);    // assets\speaker.png
LV_IMG_DECLARE(ui_img_search_png);    // assets\search.png
LV_IMG_DECLARE(ui_img_setting_png);    // assets\setting.png
LV_IMG_DECLARE(ui_img_photo_png);    // assets\photo.png
LV_IMG_DECLARE(ui_img_music_png);    // assets\music.png
LV_IMG_DECLARE(ui_img_edge_png);    // assets\edge.png
LV_IMG_DECLARE(ui_img_file_png);    // assets\file.png
LV_IMG_DECLARE(ui_img_pc_big_png);    // assets\pc_big.png
LV_IMG_DECLARE(ui_img_video_png);    // assets\video.png
LV_IMG_DECLARE(ui_img_bg1_small_png);    // assets\bg1_small.png
LV_IMG_DECLARE(ui_img_bg2_small_png);    // assets\bg2_small.png
LV_IMG_DECLARE(ui_img_bg2_png);    // assets\bg2.png
LV_IMG_DECLARE(ui_img_slider_bg_mario_png);    // assets\slider_bg_mario.png
LV_IMG_DECLARE(ui_img_suppermario_png);    // assets\supperMario.png
LV_IMG_DECLARE(ui_img_photo4_png);    // assets\photo4.png
LV_IMG_DECLARE(ui_img_photos1_png);    // assets\photos1.png
LV_IMG_DECLARE(ui_img_photo_3201_png);    // assets\photo_3201.png
LV_IMG_DECLARE(ui_img_video5_png);    // assets\video5.png

LV_FONT_DECLARE(ui_font_Mona_Sans);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

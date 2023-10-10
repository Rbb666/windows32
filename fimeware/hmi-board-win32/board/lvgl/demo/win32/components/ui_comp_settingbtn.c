// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"


// COMPONENT settingbtn

lv_obj_t *ui_settingbtn_create(lv_obj_t *comp_parent) {

lv_obj_t *cui_settingbtn;
cui_settingbtn = lv_imgbtn_create(comp_parent);
lv_imgbtn_set_src(cui_settingbtn, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_setting_png, NULL);
lv_imgbtn_set_src(cui_settingbtn, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_setting_png, NULL);
lv_obj_set_width( cui_settingbtn, 30);
lv_obj_set_height( cui_settingbtn, 28);
lv_obj_set_x( cui_settingbtn, 5 );
lv_obj_set_y( cui_settingbtn, 1 );
lv_obj_set_style_radius(cui_settingbtn, 5, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_SETTINGBTN_NUM);
children[UI_COMP_SETTINGBTN_SETTINGBTN] = cui_settingbtn;
lv_obj_add_event_cb(cui_settingbtn, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
lv_obj_add_event_cb(cui_settingbtn, del_component_child_event_cb, LV_EVENT_DELETE, children);
ui_comp_settingbtn_create_hook(cui_settingbtn);
return cui_settingbtn; 
}


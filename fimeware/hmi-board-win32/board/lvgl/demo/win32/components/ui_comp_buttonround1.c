// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"


// COMPONENT buttonround1

lv_obj_t *ui_buttonround1_create(lv_obj_t *comp_parent) {

lv_obj_t *cui_buttonround1;
cui_buttonround1 = lv_btn_create(comp_parent);
lv_obj_set_width( cui_buttonround1, 40);
lv_obj_set_height( cui_buttonround1, 40);
lv_obj_set_x( cui_buttonround1, 0 );
lv_obj_set_y( cui_buttonround1, 5 );
lv_obj_set_align( cui_buttonround1, LV_ALIGN_BOTTOM_MID );
lv_obj_add_flag( cui_buttonround1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( cui_buttonround1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(cui_buttonround1, 150, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(cui_buttonround1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(cui_buttonround1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_img_src( cui_buttonround1, &TemporaryImage, LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_width(cui_buttonround1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_outline_color(cui_buttonround1, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_outline_opa(cui_buttonround1, 255, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_shadow_color(cui_buttonround1, lv_color_hex(0x7A7A7A), LV_PART_MAIN | LV_STATE_PRESSED );
lv_obj_set_style_shadow_opa(cui_buttonround1, 255, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_shadow_width(cui_buttonround1, 50, LV_PART_MAIN| LV_STATE_PRESSED);
lv_obj_set_style_shadow_spread(cui_buttonround1, 2, LV_PART_MAIN| LV_STATE_PRESSED);

lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_BUTTONROUND1_NUM);
children[UI_COMP_BUTTONROUND1_BUTTONROUND1] = cui_buttonround1;
lv_obj_add_event_cb(cui_buttonround1, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
lv_obj_add_event_cb(cui_buttonround1, del_component_child_event_cb, LV_EVENT_DELETE, children);
ui_comp_buttonround1_create_hook(cui_buttonround1);
return cui_buttonround1; 
}


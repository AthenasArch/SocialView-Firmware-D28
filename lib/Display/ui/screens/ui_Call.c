// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.1
// LVGL version: 8.3.6
// Project name: Smart_Gadget

#include "../ui.h"

void ui_Call_screen_init(void)
{
    ui_Call = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Call, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Call, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Call, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Call, &ui_img_pattern_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_tiled(ui_Call, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Scrolldots1 = ui_Scrolldots_create(ui_Call);
    lv_obj_set_x(ui_Scrolldots1, 0);
    lv_obj_set_y(ui_Scrolldots1, -8);

    lv_obj_set_width(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D1), 4);
    lv_obj_set_height(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D1), 4);

    lv_obj_set_width(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D2), 8);
    lv_obj_set_height(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D2), 8);
    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D2), 11);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D2), 0);
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D2), lv_color_hex(0x101C52),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D2), 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Call, ui_event_Call, LV_EVENT_ALL, NULL);

}

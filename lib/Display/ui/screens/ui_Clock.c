// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.1
// LVGL version: 8.3.6
// Project name: Smart_Gadget

#include "../ui.h"

void ui_Clock_screen_init(void)
{
    ui_Clock = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Clock, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_Clock, &ui_img_pattern_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_tiled(ui_Clock, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Clock_Panel = lv_obj_create(ui_Clock);
    lv_obj_set_width(ui_Clock_Panel, 180);
    lv_obj_set_height(ui_Clock_Panel, 180);
    lv_obj_set_x(ui_Clock_Panel, 0);
    lv_obj_set_y(ui_Clock_Panel, 40);
    lv_obj_set_align(ui_Clock_Panel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Clock_Panel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Clock_Panel, 500, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Clock_Panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Clock_Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Dot1 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot1, -40);
    lv_obj_set_y(ui_Dot1, 15);
    lv_obj_set_align(ui_Dot1, LV_ALIGN_TOP_RIGHT);

    ui_Dot2 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot2, -10);
    lv_obj_set_y(ui_Dot2, 50);

    ui_Dot3 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot3, 40);
    lv_obj_set_y(ui_Dot3, 15);
    lv_obj_set_align(ui_Dot3, LV_ALIGN_TOP_LEFT);

    ui_Dot4 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot4, 10);
    lv_obj_set_y(ui_Dot4, 50);
    lv_obj_set_align(ui_Dot4, LV_ALIGN_TOP_LEFT);

    ui_Dot5 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot5, 10);
    lv_obj_set_y(ui_Dot5, -50);
    lv_obj_set_align(ui_Dot5, LV_ALIGN_BOTTOM_LEFT);

    ui_Dot6 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot6, 40);
    lv_obj_set_y(ui_Dot6, -15);
    lv_obj_set_align(ui_Dot6, LV_ALIGN_BOTTOM_LEFT);

    ui_Dot7 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot7, -10);
    lv_obj_set_y(ui_Dot7, -50);
    lv_obj_set_align(ui_Dot7, LV_ALIGN_BOTTOM_RIGHT);

    ui_Dot8 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot8, -40);
    lv_obj_set_y(ui_Dot8, -15);
    lv_obj_set_align(ui_Dot8, LV_ALIGN_BOTTOM_RIGHT);

    ui_Clock_Number1 = ui_Small_Label_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Clock_Number1, 0);
    lv_obj_set_y(ui_Clock_Number1, 0);

    ui_Clock_Number2 = ui_Small_Label_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Clock_Number2, 0);
    lv_obj_set_y(ui_Clock_Number2, 0);
    lv_obj_set_align(ui_Clock_Number2, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Clock_Number2, "6");

    ui_Clock_Number3 = ui_Small_Label_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Clock_Number3, 0);
    lv_obj_set_y(ui_Clock_Number3, 0);
    lv_obj_set_align(ui_Clock_Number3, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Clock_Number3, "9");

    ui_Clock_Number4 = ui_Small_Label_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Clock_Number4, 0);
    lv_obj_set_y(ui_Clock_Number4, 0);
    lv_obj_set_align(ui_Clock_Number4, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_Clock_Number4, "3");

    ui_Min = lv_img_create(ui_Clock_Panel);
    lv_img_set_src(ui_Min, &ui_img_clock_min_png);
    lv_obj_set_width(ui_Min, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Min, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Min, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Min, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Min, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Hour = lv_img_create(ui_Clock_Panel);
    lv_img_set_src(ui_Hour, &ui_img_clock_hour_png);
    lv_obj_set_width(ui_Hour, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Hour, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Hour, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Hour, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Hour, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Sec = lv_img_create(ui_Clock_Panel);
    lv_img_set_src(ui_Sec, &ui_img_clock_sec_png);
    lv_obj_set_width(ui_Sec, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Sec, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Sec, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Sec, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Sec, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_angle(ui_Sec, 150);

    ui_Clock_Center = lv_obj_create(ui_Clock_Panel);
    lv_obj_set_width(ui_Clock_Center, 8);
    lv_obj_set_height(ui_Clock_Center, 8);
    lv_obj_set_align(ui_Clock_Center, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Clock_Center, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Clock_Center, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Clock_Center, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Clock_Center, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Clock_Center, lv_color_hex(0x1937D2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Clock_Center, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Clock_Center, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Clock_Number = lv_label_create(ui_Clock);
    lv_obj_set_width(ui_Clock_Number, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Clock_Number, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Clock_Number, 0);
    lv_obj_set_y(ui_Clock_Number, 15);
    lv_obj_set_align(ui_Clock_Number, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Clock_Number, "09:25");
    lv_obj_set_style_text_color(ui_Clock_Number, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Clock_Number, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Clock_Number, &ui_font_Number, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Date = ui_Small_Label_create(ui_Clock);
    lv_obj_set_x(ui_Date, 0);
    lv_obj_set_y(ui_Date, 76);
    lv_label_set_text(ui_Date, "Mon 28 Oct");
    lv_obj_set_style_text_color(ui_Date, lv_color_hex(0x9C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Date, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Scrolldots = ui_Scrolldots_create(ui_Clock);
    lv_obj_set_x(ui_Scrolldots, 0);
    lv_obj_set_y(ui_Scrolldots, -8);

    lv_obj_set_style_bg_color(ui_comp_get_child(ui_Scrolldots, UI_COMP_SCROLLDOTS_D1), lv_color_hex(0x101C52),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_Scrolldots, UI_COMP_SCROLLDOTS_D1), 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Clock, ui_event_Clock, LV_EVENT_ALL, NULL);

}

#include "menu_windows.h"
#include "menu_windows.h"
#include "lvgl/lvgl.h"
#include "stdlib.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

extern "C" {
    LV_FONT_DECLARE(font_72);
    LV_FONT_DECLARE(font_48);
    LV_FONT_DECLARE(font_48_ch);
    LV_FONT_DECLARE(font_24_ch);
    
}

menu_windows::menu_windows(_lv_obj_t *parent)
{
    if(parent!=NULL)
    {
        parent_windos=parent;

    }
    else
    {
        parent_windos=lv_scr_act();

    }

    menu_button_0x0 = lv_btn_create(parent_windos);
    menu_button_0x1 = lv_btn_create(parent_windos);
    menu_button_0x2 = lv_btn_create(parent_windos);

    menu_button_1x0 = lv_btn_create(parent_windos);
    menu_button_1x1 = lv_btn_create(parent_windos);
    menu_button_1x2 = lv_btn_create(parent_windos);

    menu_button_2x0 = lv_btn_create(parent_windos);
    menu_button_2x1 = lv_btn_create(parent_windos);
    menu_button_2x2 = lv_btn_create(parent_windos);

}
menu_windows::~menu_windows()
{

}

void menu_windows::drawing()
{
    lv_obj_set_pos(menu_button_0x0, 90, 50);
    lv_obj_set_size(menu_button_0x0, 200, 120);
    


    lv_obj_set_pos(menu_button_0x1, 300, 50);
    lv_obj_set_size(menu_button_0x1, 200, 120);

    lv_obj_set_pos(menu_button_0x2, 510, 50);
    lv_obj_set_size(menu_button_0x2, 200, 120);

    lv_obj_set_pos(menu_button_1x0, 90, 180);
    lv_obj_set_size(menu_button_1x0, 200, 120);

    lv_obj_set_pos(menu_button_1x1, 300, 180);
    lv_obj_set_size(menu_button_1x1, 200, 120);

    lv_obj_set_pos(menu_button_1x2, 510, 180);
    lv_obj_set_size(menu_button_1x2, 200, 120);

    lv_obj_set_pos(menu_button_2x0, 90, 310);
    lv_obj_set_size(menu_button_2x0, 200, 120);

    lv_obj_set_pos(menu_button_2x1, 300, 310);
    lv_obj_set_size(menu_button_2x1, 200, 120);

    lv_obj_set_pos(menu_button_2x2, 510, 310);
    lv_obj_set_size(menu_button_2x2, 200, 120);

}
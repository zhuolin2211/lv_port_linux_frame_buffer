#include "menu_windows.h"
#include "menu_windows.h"
#include "lvgl/lvgl.h"
#include "stdlib.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "music_player.h"
using namespace std;

extern "C" {
    LV_FONT_DECLARE(font_72);
    LV_FONT_DECLARE(font_48);
    LV_FONT_DECLARE(font_48_ch);
    LV_FONT_DECLARE(font_24_ch);
    LV_IMG_DECLARE(back_menu);
    LV_IMG_DECLARE(music);
    LV_IMG_DECLARE(xiaoshuo);
    LV_IMG_DECLARE(shiping);
    LV_IMG_DECLARE(dengguang);
    LV_IMG_DECLARE(chuanglian);
    LV_IMG_DECLARE(kongtiao);
    LV_IMG_DECLARE(shezhi);
    LV_IMG_DECLARE(xitong);
    LV_IMG_DECLARE(home);
    
}

menu_windows::menu_windows(_lv_obj_t *parent)
{
    parent_screen=parent;
    Current_screen = lv_obj_create(NULL);
    lv_scr_load(Current_screen);
    lv_obj_set_pos(Current_screen, 0, 0);
    lv_obj_set_size(Current_screen, 800, 480);
    windows_open_flg=1;

}
menu_windows::~menu_windows()
{

}

void menu_windows::drawing()
{

    back_img=lv_img_create(Current_screen);

    menu_button_0x0 = lv_btn_create(Current_screen);
    menu_button_0x1 = lv_btn_create(Current_screen);
    menu_button_0x2 = lv_btn_create(Current_screen);

    menu_button_1x0 = lv_btn_create(Current_screen);
    menu_button_1x1 = lv_btn_create(Current_screen);
    menu_button_1x2 = lv_btn_create(Current_screen);

    menu_button_2x0 = lv_btn_create(Current_screen);
    menu_button_2x1 = lv_btn_create(Current_screen);
    menu_button_2x2 = lv_btn_create(Current_screen);

    menu_img_0x0 = lv_img_create(menu_button_0x0);
    menu_img_0x1 = lv_img_create(menu_button_0x1);
    menu_img_0x2 = lv_img_create(menu_button_0x2);

    menu_img_1x0 = lv_img_create(menu_button_1x0);
    menu_img_1x1 = lv_img_create(menu_button_1x1);
    menu_img_1x2 = lv_img_create(menu_button_1x2);

    menu_img_2x0 = lv_img_create(menu_button_2x0);
    menu_img_2x1 = lv_img_create(menu_button_2x1);
    menu_img_2x2 = lv_img_create(menu_button_2x2);


    menu_label_0x0 = lv_label_create(menu_button_0x0);
    menu_label_0x1 = lv_label_create(menu_button_0x1);
    menu_label_0x2 = lv_label_create(menu_button_0x2);

    menu_label_1x0 = lv_label_create(menu_button_1x0);
    menu_label_1x1 = lv_label_create(menu_button_1x1);
    menu_label_1x2 = lv_label_create(menu_button_1x2);

    menu_label_2x0 = lv_label_create(menu_button_2x0);
    menu_label_2x1 = lv_label_create(menu_button_2x1);
    menu_label_2x2 = lv_label_create(menu_button_2x2);

    lv_img_set_src(back_img, &back_menu);
    lv_obj_set_pos(back_img, 0, 0);
    lv_obj_set_size(back_img, 800, 480);
    //lv_img_set_zoom(back_img,400);
    
    static lv_style_t text_style;
    lv_style_init(&text_style);

    

    lv_obj_set_pos(menu_button_0x0, 90, 50);
    lv_obj_set_size(menu_button_0x0, 200, 120);
    lv_obj_set_style_bg_color(menu_button_0x0,lv_color_hex(0xff2d51),LV_STATE_DEFAULT);
    lv_img_set_src(menu_img_0x0, &music);
    lv_obj_set_align(menu_img_0x0,LV_ALIGN_CENTER);
    lv_img_set_zoom(menu_img_0x0,398);
    lv_label_set_text(menu_label_0x0,"音乐");
    lv_obj_set_pos(menu_label_0x0,-10,0);
    lv_obj_set_align(menu_label_0x0,LV_ALIGN_BOTTOM_LEFT);
    lv_style_set_text_font(&text_style,&font_24_ch);
    lv_obj_add_style(menu_label_0x0,&text_style,LV_STATE_DEFAULT);
    lv_obj_add_event_cb(menu_button_0x0,&menu_windows::music_button_cb,LV_EVENT_CLICKED,this);


    


    lv_obj_set_pos(menu_button_0x1, 300, 50);
    lv_obj_set_size(menu_button_0x1, 200, 120);
    lv_obj_set_style_bg_color(menu_button_0x1,lv_color_hex(0xf2be45 ),LV_STATE_DEFAULT);
     lv_img_set_src(menu_img_0x1, &xiaoshuo);
    lv_obj_set_align(menu_img_0x1,LV_ALIGN_CENTER);
    lv_img_set_zoom(menu_img_0x1,398);
    lv_label_set_text(menu_label_0x1,"小说");
    lv_obj_set_pos(menu_label_0x1,-10,0);
    lv_obj_set_align(menu_label_0x1,LV_ALIGN_BOTTOM_LEFT);
    lv_style_set_text_font(&text_style,&font_24_ch);
    lv_obj_add_style(menu_label_0x1,&text_style,LV_STATE_DEFAULT);


    lv_obj_set_pos(menu_button_0x2, 510, 50);
    lv_obj_set_size(menu_button_0x2, 200, 120);
    lv_obj_set_style_bg_color(menu_button_0x2,lv_color_hex(0xa1afc9),LV_STATE_DEFAULT);
    lv_img_set_src(menu_img_0x2, &shiping);
    lv_obj_set_align(menu_img_0x2,LV_ALIGN_CENTER);
    lv_img_set_zoom(menu_img_0x2,398);
    lv_label_set_text(menu_label_0x2,"电影");
    lv_obj_set_pos(menu_label_0x2,-10,0);
    lv_obj_set_align(menu_label_0x2,LV_ALIGN_BOTTOM_LEFT);
    lv_style_set_text_font(&text_style,&font_24_ch);
    lv_obj_add_style(menu_label_0x2,&text_style,LV_STATE_DEFAULT);


    lv_obj_set_pos(menu_button_1x0, 90, 180);
    lv_obj_set_size(menu_button_1x0, 200, 120);
    lv_obj_set_style_bg_color(menu_button_1x0,lv_color_hex(0xedd1d8 ),LV_STATE_DEFAULT);
    lv_img_set_src(menu_img_1x0, &dengguang);
    lv_obj_set_align(menu_img_1x0,LV_ALIGN_CENTER);
    lv_img_set_zoom(menu_img_1x0,398);
    lv_label_set_text(menu_label_1x0,"灯光");
    lv_obj_set_pos(menu_label_1x0,-10,0);
    lv_obj_set_align(menu_label_1x0,LV_ALIGN_BOTTOM_LEFT);
    lv_style_set_text_font(&text_style,&font_24_ch);
    lv_obj_add_style(menu_label_1x0,&text_style,LV_STATE_DEFAULT);


    lv_obj_set_pos(menu_button_1x1, 300, 180);
    lv_obj_set_size(menu_button_1x1, 200, 120);
    lv_obj_set_style_bg_color(menu_button_1x1,lv_color_hex(0xe29c45 ),LV_STATE_DEFAULT);
    lv_img_set_src(menu_img_1x1, &chuanglian);
    lv_obj_set_align(menu_img_1x1,LV_ALIGN_CENTER);
    lv_img_set_zoom(menu_img_1x1,398);
    lv_label_set_text(menu_label_1x1,"窗帘");
    lv_obj_set_pos(menu_label_1x1,-10,0);
    lv_obj_set_align(menu_label_1x1,LV_ALIGN_BOTTOM_LEFT);
    lv_style_set_text_font(&text_style,&font_24_ch);
    lv_obj_add_style(menu_label_1x1,&text_style,LV_STATE_DEFAULT);


    lv_obj_set_pos(menu_button_1x2, 510, 180);
    lv_obj_set_size(menu_button_1x2, 200, 120);
    lv_obj_set_style_bg_color(menu_button_1x2,lv_color_hex(0xe29c45 ),LV_STATE_DEFAULT);
    lv_img_set_src(menu_img_1x2, &kongtiao);
    lv_obj_set_align(menu_img_1x2,LV_ALIGN_CENTER);
    lv_img_set_zoom(menu_img_1x2,398);
    lv_label_set_text(menu_label_1x2,"空调");
    lv_obj_set_pos(menu_label_1x2,-10,0);
    lv_obj_set_align(menu_label_1x2,LV_ALIGN_BOTTOM_LEFT);
    lv_style_set_text_font(&text_style,&font_24_ch);
    lv_obj_add_style(menu_label_1x2,&text_style,LV_STATE_DEFAULT);


    lv_obj_set_pos(menu_button_2x0, 90, 310);
    lv_obj_set_size(menu_button_2x0, 200, 120);
    lv_obj_set_style_bg_color(menu_button_2x0,lv_color_hex(0xa88462),LV_STATE_DEFAULT);
    lv_img_set_src(menu_img_2x0, &shezhi);
    lv_obj_set_align(menu_img_2x0,LV_ALIGN_CENTER);
    lv_img_set_zoom(menu_img_2x0,398);
    lv_label_set_text(menu_label_2x0,"设置");
    lv_obj_set_pos(menu_label_2x0,-10,0);
    lv_obj_set_align(menu_label_2x0,LV_ALIGN_BOTTOM_LEFT);
    lv_style_set_text_font(&text_style,&font_24_ch);
    lv_obj_add_style(menu_label_2x0,&text_style,LV_STATE_DEFAULT);


    lv_obj_set_pos(menu_button_2x1, 300, 310);
    lv_obj_set_size(menu_button_2x1, 200, 120);
    lv_obj_set_style_bg_color(menu_button_2x1,lv_color_hex(0x8d4bbb ),LV_STATE_DEFAULT);
    lv_img_set_src(menu_img_2x1, &xitong);
    lv_obj_set_align(menu_img_2x1,LV_ALIGN_CENTER);
    lv_img_set_zoom(menu_img_2x1,398);
    lv_label_set_text(menu_label_2x1,"系统");
    lv_obj_set_pos(menu_label_2x1,-10,0);
    lv_obj_set_align(menu_label_2x1,LV_ALIGN_BOTTOM_LEFT);
    lv_style_set_text_font(&text_style,&font_24_ch);
    lv_obj_add_style(menu_label_2x1,&text_style,LV_STATE_DEFAULT);


    lv_obj_set_pos(menu_button_2x2, 510, 310);
    lv_obj_set_size(menu_button_2x2, 200, 120);
    lv_obj_set_style_bg_color(menu_button_2x2,lv_color_hex(0x8d4bbb ),LV_STATE_DEFAULT);
     lv_img_set_src(menu_img_2x2, &home);
    lv_obj_set_align(menu_img_2x2,LV_ALIGN_CENTER);
    lv_img_set_zoom(menu_img_2x2,398);
    lv_label_set_text(menu_label_2x2,"主页");
    lv_obj_set_pos(menu_label_2x2,-10,0);
    lv_obj_set_align(menu_label_2x2,LV_ALIGN_BOTTOM_LEFT);
    lv_style_set_text_font(&text_style,&font_24_ch);
    lv_obj_add_style(menu_label_2x2,&text_style,LV_STATE_DEFAULT);


}
void menu_windows::close_windows()
{
    windows_open_flg=0;
    lv_obj_clean(this->Current_screen);
    lv_obj_del(this->Current_screen);
}
void menu_windows::hide_windows()
{
    windows_open_flg=0;
    lv_obj_add_flag(this->Current_screen,LV_OBJ_FLAG_HIDDEN);
}

void menu_windows::music_button_cb(lv_event_t * e)
{
    printf("music_button_cb\n");
    menu_windows* menu = (menu_windows*)lv_event_get_user_data(e);
    menu->hide_windows();
    music_player *player= new music_player(menu->Current_screen);
    player->drawing();
}
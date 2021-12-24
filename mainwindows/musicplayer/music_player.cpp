#include "music_player.h"
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
    LV_IMG_DECLARE(music_backgroud);
    LV_IMG_DECLARE(circular);
    LV_IMG_DECLARE(next_file);
    LV_IMG_DECLARE(next_push);
    LV_IMG_DECLARE(previous);
    LV_IMG_DECLARE(previous_push);
    LV_IMG_DECLARE(stop_img_file);
    LV_IMG_DECLARE(stop_push_img_file);
  
    
}

music_player::music_player(_lv_obj_t *parent)
{
    if(parent!=NULL)
    {
        parent_windos=parent;

    }
    else
    {
        parent_windos=lv_scr_act();

    }

    back_img=lv_img_create(parent_windos);
    music_list=lv_roller_create(parent_windos);
    circular_img=lv_img_create(parent_windos);
    previous_push_img=lv_imgbtn_create(parent_windos);
    next_push_img=lv_imgbtn_create(parent_windos);
    stop_push_img=lv_imgbtn_create(parent_windos);
    progress_bar=lv_bar_create(parent_windos);


    windows_open_flg=1;

}
music_player::~music_player()
{

}

void music_player::drawing()
{
   lv_img_set_src(back_img, &music_backgroud);
    lv_obj_set_pos(back_img, 0, 0);
    lv_obj_set_size(back_img, 800, 480);

    lv_obj_set_pos(music_list, 50  , 41);
    lv_obj_set_size(music_list, 261, 398);

    lv_obj_set_pos(circular_img,   422, 87);
    lv_obj_set_size(circular_img, 260, 260);
    lv_img_set_src(circular_img,&circular);

    lv_obj_set_pos(previous_push_img,   453, 353);
    lv_obj_set_size(previous_push_img, 36 ,36);
    lv_imgbtn_set_src(previous_push_img,LV_IMGBTN_STATE_PRESSED,NULL,&previous_push,NULL);
    lv_imgbtn_set_src(previous_push_img,LV_IMGBTN_STATE_RELEASED,NULL,&previous,NULL);

    

    lv_obj_set_pos(stop_push_img,   537, 353);
    lv_obj_set_size(stop_push_img, 36, 36);
     lv_imgbtn_set_src(stop_push_img,LV_IMGBTN_STATE_PRESSED,NULL,&stop_push_img_file,NULL);
    lv_imgbtn_set_src(stop_push_img,LV_IMGBTN_STATE_RELEASED,NULL,&stop_img_file,NULL);

     
    lv_obj_set_pos(next_push_img,   621, 353);
    lv_obj_set_size(next_push_img, 36, 36);
    lv_imgbtn_set_src(next_push_img,LV_IMGBTN_STATE_PRESSED,NULL,&next_push,NULL);
    lv_imgbtn_set_src(next_push_img,LV_IMGBTN_STATE_RELEASED,NULL,&next_file,NULL);

    

     lv_obj_set_pos(progress_bar,   353, 418);
    lv_obj_set_size(progress_bar, 400, 12);
    lv_bar_set_range(progress_bar,0,100);
    /*test code*/
    lv_bar_set_value(progress_bar,30,LV_ANIM_OFF);
    lv_obj_set_style_bg_color(progress_bar,lv_color_hex(0xFFFFFF),LV_PART_MAIN);
    lv_obj_set_style_bg_color(progress_bar,lv_color_hex(0xFF0033),LV_PART_INDICATOR );
    





}
void music_player::close_windows()
{
    windows_open_flg=0;
    lv_obj_clean(lv_scr_act());
}
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
    LV_IMG_DECLARE(play_flg);
  
    
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
    music_list=lv_obj_create(parent_windos);
    circular_img=lv_img_create(parent_windos);
    previous_push_img=lv_imgbtn_create(parent_windos);
    next_push_img=lv_imgbtn_create(parent_windos);
    stop_push_img=lv_imgbtn_create(parent_windos);
    progress_bar=lv_bar_create(parent_windos);


    windows_open_flg=1;
    circular_angle=0;

}
music_player::~music_player()
{

}

void music_player::drawing()
{
   lv_img_set_src(back_img, &music_backgroud);
    lv_obj_set_pos(back_img, 0, 0);
    lv_obj_set_size(back_img, 800, 480);


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
    

    // circular_time=lv_timer_create(&music_player::circular_time_cb,500,this);
    
    // lv_anim_t a;
    // lv_anim_init(&a);
    // lv_anim_set_var(&a, circular_img);
    // lv_anim_set_time(&a, 20000);
    // lv_anim_set_values(&a,0,3600);
    // lv_anim_set_repeat_count(&a,LV_ANIM_REPEAT_INFINITE);
    // lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_img_set_angle);
    // lv_anim_start(&a);

    lv_obj_set_pos(music_list, 0  , 0);
    lv_obj_set_size(music_list, 310, 480);

    static lv_style_t list_style;
     lv_style_init(&list_style);
     lv_style_set_bg_opa(&list_style, LV_OPA_COVER);
     lv_style_set_bg_color(&list_style, lv_color_hex(0xDCDCDC));
    lv_style_set_pad_right(&list_style, 4);
    lv_obj_add_style(music_list,&list_style,LV_PART_MAIN);
    lv_obj_set_flex_flow(music_list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scroll_dir(music_list,LV_DIR_VER);
    
    

    

    add_music(music_list);
    add_music(music_list);
    add_music(music_list);
    add_music(music_list);
    add_music(music_list);
    add_music(music_list);
    add_music(music_list);
    add_music(music_list);
    add_music(music_list);
    add_music(music_list);
    add_music(music_list);
    add_music(music_list);
    add_music(music_list);
    add_music(music_list);



}
void music_player::add_music(lv_obj_t* parent)
{
    lv_obj_t *music_btn;
    music_btn = lv_obj_create(parent);
    lv_obj_remove_style_all(music_btn);
    lv_obj_set_size(music_btn,310,48);
    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    static const lv_coord_t grid_cols[] = {40, 90, 80, LV_GRID_TEMPLATE_LAST};
    static const lv_coord_t grid_rows[] = {24,  24, LV_GRID_TEMPLATE_LAST};
    lv_style_set_bg_opa(&style_btn, LV_OPA_TRANSP);
    lv_style_set_grid_column_dsc_array(&style_btn, grid_cols);
    lv_style_set_grid_row_dsc_array(&style_btn, grid_rows);
    lv_style_set_grid_row_align(&style_btn, LV_GRID_ALIGN_CENTER);
    lv_style_set_layout(&style_btn, LV_LAYOUT_GRID);
    lv_obj_add_style(music_btn, &style_btn, 0);

    lv_obj_t * icon = lv_img_create(music_btn);
    lv_img_set_src(icon, &play_flg);
    lv_obj_set_grid_cell(icon, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 2);

    lv_obj_t * title_label = lv_label_create(music_btn);
    lv_label_set_text(title_label, "歌手");
    lv_obj_set_grid_cell(title_label, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    static lv_style_t style_title;
    lv_style_init(&style_title);
    lv_style_set_text_font(&style_title,&font_24_ch);
    lv_obj_add_style(title_label, &style_title, 0);

    lv_obj_t * artist_label = lv_label_create(music_btn);
    lv_label_set_text(artist_label, "想你的夜");
    static lv_style_t style_artist;
    lv_style_init(&style_artist);
    lv_style_set_text_font(&style_artist,&font_24_ch);
    lv_obj_add_style(artist_label, &style_artist, 0);
    lv_obj_set_grid_cell(artist_label, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 1, 1);

    lv_obj_t * time_label = lv_label_create(music_btn);
    lv_label_set_text(time_label, "12:1");
    static lv_style_t style_time;
    lv_style_init(&style_time);
    lv_style_set_text_font(&style_time,&lv_font_montserrat_24);
    lv_obj_add_style(time_label, &style_time, 0);
    lv_obj_set_grid_cell(time_label, LV_GRID_ALIGN_END, 2, 1, LV_GRID_ALIGN_CENTER, 0, 2);

}
void music_player::close_windows()
{
    windows_open_flg=0;
    lv_obj_clean(lv_scr_act());
}
void music_player::circular_time_cb(struct _lv_timer_t * timer)
{
    music_player* player=(music_player*)timer->user_data;
    lv_img_set_angle( player->circular_img,player->circular_angle+=100);
    if(player->circular_angle>=3600)
    {
        player->circular_angle=100;
    }
}
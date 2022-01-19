#include "music_player.h"
#include "lvgl/lvgl.h"
#include "stdlib.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <vector>
#include <iomanip>
#include "playaudio.h"
extern std::vector<std::string> readFileList(const char * basePath, std::vector<std::string> & result);
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
LV_IMG_DECLARE(play);
LV_IMG_DECLARE(play_push);
LV_IMG_DECLARE(back_button_img);
}

music_player::music_player(lv_obj_t * parent)
{
    parent_screen=parent;
    Current_screen = lv_obj_create(NULL);
    lv_scr_load(Current_screen);
    lv_obj_set_pos(Current_screen, 0, 0);
    lv_obj_set_size(Current_screen, 800, 480);
    windows_open_flg    = 1;
    circular_angle      = 0;
    current_music_index = 0;
    play_startup        = 0;
}
music_player::~music_player()
{}

void music_player::drawing()
{

    back_img          = lv_img_create(Current_screen);
    back_button       = lv_imgbtn_create(Current_screen);
    music_list        = lv_obj_create(Current_screen);
    circular_img      = lv_img_create(Current_screen);
    previous_push_img = lv_imgbtn_create(Current_screen);
    next_push_img     = lv_imgbtn_create(Current_screen);
    stop_push_img     = lv_imgbtn_create(Current_screen);
    progress_bar      = lv_bar_create(Current_screen);

    lv_img_set_src(back_img, &music_backgroud);
    lv_obj_set_pos(back_img, 0, 0);
    lv_obj_set_size(back_img, 800, 480);

    static lv_style_t button_style2;
    lv_style_init(&button_style2);
    lv_style_set_img_recolor(&button_style2, lv_color_black());
    lv_style_set_img_recolor_opa(&button_style2, LV_OPA_30);
    lv_obj_add_style(back_button, &button_style2, LV_STATE_PRESSED);

    lv_obj_set_pos(back_button, 15, 9);
    lv_obj_set_size(back_button, 32, 32);
    lv_imgbtn_set_src(back_button, LV_IMGBTN_STATE_RELEASED, NULL, &back_button_img, NULL);
    lv_imgbtn_set_src(back_button, LV_IMGBTN_STATE_PRESSED, NULL, &back_button_img, NULL);
    lv_obj_add_event_cb(back_button, &music_player::back_button_cb, LV_EVENT_CLICKED, this);

    lv_obj_set_pos(circular_img, 422, 87);
    lv_obj_set_size(circular_img, 260, 260);
    lv_img_set_src(circular_img, &circular);

    lv_obj_set_pos(previous_push_img, 453, 353);
    lv_obj_set_size(previous_push_img, 36, 36);
    lv_imgbtn_set_src(previous_push_img, LV_IMGBTN_STATE_PRESSED, NULL, &previous_push, NULL);
    lv_imgbtn_set_src(previous_push_img, LV_IMGBTN_STATE_RELEASED, NULL, &previous, NULL);
    lv_obj_add_event_cb(previous_push_img, &music_player::music_last_button_cb, LV_EVENT_CLICKED, this);

    lv_obj_set_pos(stop_push_img, 537, 353);
    lv_obj_set_size(stop_push_img, 36, 36);
    lv_imgbtn_set_src(stop_push_img, LV_IMGBTN_STATE_PRESSED, NULL, &play_push, NULL);
    lv_imgbtn_set_src(stop_push_img, LV_IMGBTN_STATE_RELEASED, NULL, &play, NULL);
    lv_obj_add_event_cb(stop_push_img, &music_player::music_stop_button_cb, LV_EVENT_CLICKED, this);

    lv_obj_set_pos(next_push_img, 621, 353);
    lv_obj_set_size(next_push_img, 36, 36);
    lv_imgbtn_set_src(next_push_img, LV_IMGBTN_STATE_PRESSED, NULL, &next_push, NULL);
    lv_imgbtn_set_src(next_push_img, LV_IMGBTN_STATE_RELEASED, NULL, &next_file, NULL);
    lv_obj_add_event_cb(next_push_img, &music_player::music_next_button_cb, LV_EVENT_CLICKED, this);

    lv_obj_set_pos(progress_bar, 353, 418);
    lv_obj_set_size(progress_bar, 400, 12);
    lv_bar_set_range(progress_bar, 0, 100);
    /*test code*/
    lv_bar_set_value(progress_bar, 30, LV_ANIM_OFF);
    lv_obj_set_style_bg_color(progress_bar, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_bg_color(progress_bar, lv_color_hex(0xFF0033), LV_PART_INDICATOR);

    circular_time = lv_timer_create(&music_player::circular_time_cb, 500, this);

    // lv_anim_t a;
    // lv_anim_init(&a);
    // lv_anim_set_var(&a, circular_img);
    // lv_anim_set_time(&a, 20000);
    // lv_anim_set_values(&a,0,3600);
    // lv_anim_set_repeat_count(&a,LV_ANIM_REPEAT_INFINITE);
    // lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_img_set_angle);
    // lv_anim_start(&a);

    lv_obj_set_pos(music_list, 5, 55);
    lv_obj_set_size(music_list, 305, 420);

    static lv_style_t list_style;
    lv_style_init(&list_style);
    lv_style_set_bg_opa(&list_style, LV_OPA_COVER);
    lv_style_set_bg_color(&list_style, lv_color_hex(0xDCDCDC));
    lv_style_set_pad_left(&list_style, 0);
    lv_style_set_pad_top(&list_style, 0);
    lv_style_set_pad_row(&list_style, 0);
    lv_style_set_pad_bottom(&list_style, 0);
    lv_obj_add_style(music_list, &list_style, LV_PART_MAIN);
    lv_obj_set_flex_flow(music_list, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scroll_dir(music_list, LV_DIR_VER);

    readFileList("/music", music_file);
    int music_qty = music_file.size();
    if(music_qty > 0) {
        for(int i = 0; i < music_qty; i++) {
            add_music(music_list, music_file.at(i), 90);
        }
    }
    player_deive = new Playaudio();
}

std::vector<std::string> readFileList(const char * basePath, std::vector<std::string> & result)
{
    DIR * dir;
    struct dirent * ptr;
    char base[1000];

    if((dir = opendir(basePath)) == NULL) {
        perror("Open dir error...");
        exit(1);
    }

    while((ptr = readdir(dir)) != NULL) {
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) /// current dir OR parrent dir
            continue;
        else if(ptr->d_type == 8) /// file
        {
            printf("d_name:%s/%s\n", basePath, ptr->d_name);
            result.push_back(std::string(ptr->d_name));
        } else if(ptr->d_type == 10) /// link file
        {
            printf("d_name:%s/%s\n", basePath, ptr->d_name);
            result.push_back(std::string(ptr->d_name));
        } else if(ptr->d_type == 4) /// dir
        {
            memset(base, '\0', sizeof(base));
            strcpy(base, basePath);
            strcat(base, "/");
            strcat(base, ptr->d_name);
            result.push_back(std::string(ptr->d_name));
            readFileList(base, result);
        }
    }
    closedir(dir);
    return result;
}
void music_player::add_music(lv_obj_t * parent, string & music_name, uint16_t music_sec)
{
    lv_obj_t * music_btn;
    music_btn = lv_obj_create(parent);
    lv_obj_remove_style_all(music_btn);
    lv_obj_set_size(music_btn, 310, 48);
    lv_obj_set_x(music_btn, 0);

    // lv_obj_add_flag(music_btn,LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_event_cb(music_btn, &music_player::music_list_button_cb, LV_EVENT_CLICKED, this);

    static lv_style_t style_btn;
    lv_style_init(&style_btn);
    static const lv_coord_t grid_cols[] = {40, 140, 80, LV_GRID_TEMPLATE_LAST};
    static const lv_coord_t grid_rows[] = {48, LV_GRID_TEMPLATE_LAST};
    lv_style_set_bg_opa(&style_btn, LV_OPA_TRANSP);
    lv_style_set_border_width(&style_btn, 1);
    lv_style_set_border_opa(&style_btn, LV_OPA_30);
    lv_style_set_border_side(&style_btn, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_pad_left(&style_btn, 20);
    lv_style_set_pad_top(&style_btn, 0);
    lv_style_set_pad_bottom(&style_btn, 0);
    lv_style_set_grid_column_dsc_array(&style_btn, grid_cols);
    lv_style_set_grid_row_dsc_array(&style_btn, grid_rows);
    lv_style_set_grid_row_align(&style_btn, LV_GRID_ALIGN_CENTER);
    lv_style_set_layout(&style_btn, LV_LAYOUT_GRID);

    static lv_style_t style_btn_pre;
    lv_style_init(&style_btn_pre);
    lv_style_set_bg_opa(&style_btn_pre, LV_OPA_COVER);
    lv_style_set_bg_color(&style_btn_pre, lv_color_hex(0xD3D3D3));

    static lv_style_t style_btn_che;
    lv_style_init(&style_btn_che);
    lv_style_set_bg_opa(&style_btn_che, LV_OPA_COVER);
    lv_style_set_bg_color(&style_btn_che, lv_color_hex(0xD3D3D3));

    lv_obj_add_style(music_btn, &style_btn, 0);
    lv_obj_add_style(music_btn, &style_btn_che, LV_STATE_CHECKED);
    // lv_obj_add_style(music_btn, &style_btn_pre, LV_STATE_PRESSED);

    lv_obj_t * icon = lv_img_create(music_btn);
    lv_img_set_src(icon, &play_flg);
    lv_obj_set_grid_cell(icon, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    // lv_obj_t * title_label = lv_label_create(music_btn);
    // lv_label_set_text(title_label, "歌手");
    // lv_obj_set_grid_cell(title_label, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);
    // static lv_style_t style_title;
    // lv_style_init(&style_title);
    // lv_style_set_text_font(&style_title,&font_24_ch);
    // lv_obj_add_style(title_label, &style_title, 0);

    lv_obj_t * artist_label = lv_label_create(music_btn);
    lv_label_set_text(artist_label, music_name.c_str());
    static lv_style_t style_artist;
    lv_style_init(&style_artist);
    lv_style_set_text_font(&style_artist, &font_24_ch);
    lv_obj_add_style(artist_label, &style_artist, 0);
    lv_obj_set_grid_cell(artist_label, LV_GRID_ALIGN_START, 1, 1, LV_GRID_ALIGN_CENTER, 0, 1);

    lv_obj_t * time_label = lv_label_create(music_btn);
    lv_label_set_text(time_label, (to_string(music_sec / 60) + ":" + to_string(music_sec % 60)).c_str());
    static lv_style_t style_time;
    lv_style_init(&style_time);
    lv_style_set_text_font(&style_time, &lv_font_montserrat_24);
    lv_obj_add_style(time_label, &style_time, 0);
    lv_obj_set_grid_cell(time_label, LV_GRID_ALIGN_END, 2, 1, LV_GRID_ALIGN_CENTER, 0, 1);
}
void music_player::music_list_button_cb(lv_event_t * e)
{
    lv_obj_t * btn             = lv_event_get_target(e);
    lv_obj_t * list            = lv_obj_get_parent(btn);
    uint16_t music_id          = lv_obj_get_child_id(btn);
    music_player * this_player = (music_player *)lv_event_get_user_data(e);
    for(int i = 0; i < lv_obj_get_child_cnt(list); i++) {
        lv_obj_t * other_btn = lv_obj_get_child(list, i);
        if(other_btn != btn) {
            lv_obj_clear_state(other_btn, LV_STATE_CHECKED);
        }
    }
    lv_obj_add_state(btn, LV_STATE_CHECKED);
    this_player->current_music_index = music_id;
    this_player->play_startup        = 1;
    this_player->player_deive->wait_stop_play();
    this_player->player_deive->start("/music/" + this_player->music_file.at(music_id));
    this_player->player_deive->start_play();
}
void music_player::music_next_button_cb(lv_event_t * e)
{
    music_player * this_player = (music_player *)lv_event_get_user_data(e);
    if(lv_obj_get_child_cnt(this_player->music_list) <= 0) {
        return;
    }
    this_player->current_music_index++;
    if(this_player->current_music_index >= lv_obj_get_child_cnt(this_player->music_list)) {
        this_player->current_music_index = 0;
    }
    for(int i = 0; i < lv_obj_get_child_cnt(this_player->music_list); i++) {
        lv_obj_t * other_btn = lv_obj_get_child(this_player->music_list, i);
        if(i != this_player->current_music_index) {
            lv_obj_clear_state(other_btn, LV_STATE_CHECKED);
        } else {
            lv_obj_add_state(other_btn, LV_STATE_CHECKED);
        }
    }
    this_player->play_startup = 1;
    this_player->player_deive->wait_stop_play();
    this_player->player_deive->start("/music/" + this_player->music_file.at(this_player->current_music_index));
    this_player->player_deive->start_play();
}
void music_player::music_last_button_cb(lv_event_t * e)
{
    music_player * this_player = (music_player *)lv_event_get_user_data(e);
    if(lv_obj_get_child_cnt(this_player->music_list) <= 0) {
        return;
    }
    this_player->current_music_index--;
    if(this_player->current_music_index < 0) {
        this_player->current_music_index = lv_obj_get_child_cnt(this_player->music_list) - 1;
    }
    for(int i = 0; i < lv_obj_get_child_cnt(this_player->music_list); i++) {
        lv_obj_t * other_btn = lv_obj_get_child(this_player->music_list, i);
        if(i != this_player->current_music_index) {
            lv_obj_clear_state(other_btn, LV_STATE_CHECKED);
        } else {
            lv_obj_add_state(other_btn, LV_STATE_CHECKED);
        }
    }
    this_player->play_startup = 1;
    this_player->player_deive->wait_stop_play();
    this_player->player_deive->start("/music/" + this_player->music_file.at(this_player->current_music_index));
    this_player->player_deive->start_play();
}
void music_player::music_stop_button_cb(lv_event_t * e)
{
    music_player * this_player = (music_player *)lv_event_get_user_data(e);
    if(lv_obj_get_child_cnt(this_player->music_list) <= 0) {
        return;
    }
    if(this_player->player_deive->is_playing()) {
        lv_imgbtn_set_src(this_player->stop_push_img, LV_IMGBTN_STATE_PRESSED, NULL, &play_push, NULL);
        lv_imgbtn_set_src(this_player->stop_push_img, LV_IMGBTN_STATE_RELEASED, NULL, &play, NULL);

        this_player->player_deive->suspend_play();
    } else {
        lv_imgbtn_set_src(this_player->stop_push_img, LV_IMGBTN_STATE_PRESSED, NULL, &stop_push_img_file, NULL);
        lv_imgbtn_set_src(this_player->stop_push_img, LV_IMGBTN_STATE_RELEASED, NULL, &stop_img_file, NULL);
        if(this_player->play_startup == 0) {

            this_player->player_deive->wait_stop_play();
            this_player->player_deive->start("/music/" + this_player->music_file.at(this_player->current_music_index));
        }
        this_player->player_deive->start_play();
    }
}
void music_player::back_button_cb(lv_event_t * e)
{
    music_player * this_player = (music_player *)lv_event_get_user_data(e);
    this_player->player_deive->wait_stop_play();
    lv_scr_load(this_player->parent_screen);
    lv_obj_clear_flag(this_player->parent_screen,LV_OBJ_FLAG_HIDDEN);
    this_player->close_windows();
    std::cout<<lv_scr_act()<<"  "<<this_player->parent_screen<<"  "<<this_player->parent_screen<<std::endl;

}
void music_player::close_windows()
{
    windows_open_flg = 0;
    lv_obj_clean(this->Current_screen);
    lv_obj_del(this->Current_screen);
}
void music_player::circular_time_cb(struct _lv_timer_t * timer)
{
    music_player * player = (music_player *)timer->user_data;
    lv_img_set_angle(player->circular_img, player->circular_angle += 100);
    if(player->circular_angle >= 3600) {
        player->circular_angle = 100;
    }
    uint16_t music_total_time   = player->player_deive->get_totaltime_s();
    uint8_t music_play_progress = player->player_deive->get_progress();
    lv_bar_set_value(player->progress_bar, music_play_progress, LV_ANIM_ON);
}
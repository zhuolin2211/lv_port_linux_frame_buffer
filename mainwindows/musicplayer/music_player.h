#pragma once
#include "time.h"
#include "lvgl/lvgl.h"
#include <string>
using namespace std;

class music_player
{
public:
    music_player(_lv_obj_t *parent=NULL);
    ~music_player();
    void drawing();
    void close_windows();
    void add_music(lv_obj_t* parent);

private:
/*创建该界面的父对象，通常为屏幕对象，当为自定义对象时用它作为动画的参数*/
    _lv_obj_t *parent_windos;

    /**
     * 控件
    */
   lv_obj_t *back_img;
   lv_obj_t *music_list;
   lv_obj_t *circular_img;
   lv_obj_t *previous_push_img;
   lv_obj_t *next_push_img;
   lv_obj_t *stop_push_img;
   lv_obj_t * progress_bar;

    lv_timer_t *circular_time;
   


   /*界面打开与关闭的flg，用于在关闭界面时停止一些服务*/
  uint8_t windows_open_flg;

  /*播放器的内部变量*/

  uint16_t circular_angle;


   static void circular_time_cb(struct _lv_timer_t * timer);


    
};

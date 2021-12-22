#pragma once
#include "time.h"
#include "lvgl/lvgl.h"
#include <string>
using namespace std;

class menu_windows
{
public:
    menu_windows(_lv_obj_t *parent=NULL);
    ~menu_windows();
    void drawing();
    void close_windows();

private:
    _lv_obj_t *parent_windos;
     _lv_obj_t *this_windos;
    /**
     * 控件
    */
   lv_obj_t * menu_button_0x0;
   lv_obj_t * menu_button_0x1;
   lv_obj_t * menu_button_0x2;

   lv_obj_t * menu_button_1x0;
   lv_obj_t * menu_button_1x1;
   lv_obj_t * menu_button_1x2;

   lv_obj_t * menu_button_2x0;
   lv_obj_t * menu_button_2x1;
   lv_obj_t * menu_button_2x2;

   lv_obj_t* back_img;

    lv_obj_t * menu_img_0x0;
   lv_obj_t * menu_img_0x1;
   lv_obj_t * menu_img_0x2;

   lv_obj_t * menu_img_1x0;
   lv_obj_t * menu_img_1x1;
   lv_obj_t * menu_img_1x2;

   lv_obj_t * menu_img_2x0;
   lv_obj_t * menu_img_2x1;
   lv_obj_t * menu_img_2x2;

   lv_obj_t * menu_label_0x0;
   lv_obj_t * menu_label_0x1;
   lv_obj_t * menu_label_0x2;

   lv_obj_t * menu_label_1x0;
   lv_obj_t * menu_label_1x1;
   lv_obj_t * menu_label_1x2;

   lv_obj_t * menu_label_2x0;
   lv_obj_t * menu_label_2x1;
   lv_obj_t * menu_label_2x2;

  uint8_t windows_open_flg;


    
};

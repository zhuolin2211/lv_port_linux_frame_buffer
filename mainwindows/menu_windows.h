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





    
};

#pragma once
#include "time.h"
#include "lvgl/lvgl.h"
#include "networkttask.h"
#include "menu_windows.h"
#include <string>
using namespace std;
struct TEMP
{
    double ave_temp;
    double max_temp;
    double min_temp;
};
class main_windows
{
public:
    main_windows(_lv_obj_t *parent=NULL);
    void close_windows();
    void hide_windows();
    void drawing();
    void update(void);
    void update_time(void);
    void update_temp(void);
    void set_temp(double max, double min, double ave);
    void update_weather(void);
    void set_weather(string wea);
    string  to_my_string(double number);
static  void zhiwen_event_clicked(lv_event_t* event);

    struct TEMP temp;
    string weather;
pthread_mutex_t lock;
private:
    _lv_obj_t *parent_windos;
    _lv_obj_t *this_windos;

    /*
    * view
    */
    menu_windows *menu;
    lv_obj_t *parent_screen;
    lv_obj_t *Current_screen;
    /**
     * 控件
    */
    lv_obj_t* back_img;
    lv_obj_t* zhiwen_img;
    lv_obj_t* time_label;
    lv_obj_t* date_label;
    lv_obj_t* temp_label;
    lv_obj_t* temp_up_label;
    lv_obj_t* temp_down_label;
    lv_obj_t* triangle_up_img;
    lv_obj_t* triangle_down_img;
    lv_obj_t* addr_label;
    lv_obj_t* addr_img;
    lv_obj_t* weather_label;
    lv_obj_t* weather_img;

    /*变量*/
    struct tm time_date;
    time_t cycle_count_temp,cycle_count_weather,cycle_count_time;
    uint8_t windows_open_flg;

    NetworkTtask task;

    
};

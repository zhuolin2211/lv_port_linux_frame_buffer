#pragma once
#include "time.h"
#include "lvgl/lvgl.h"
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
    main_windows();
    void drawing();
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

    
};

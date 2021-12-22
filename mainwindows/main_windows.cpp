#include "main_windows.h"
#include "lvgl/lvgl.h"
#include "stdlib.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "menu_windows.h"
using namespace std;

extern "C" {
    LV_FONT_DECLARE(font_72);
    LV_FONT_DECLARE(font_48);
    LV_FONT_DECLARE(font_48_ch);
    LV_FONT_DECLARE(font_24_ch);
    LV_IMG_DECLARE(backimage);
    LV_IMG_DECLARE(triangleimage);
    LV_IMG_DECLARE(duoyun);
    LV_IMG_DECLARE(weizhi);
    LV_IMG_DECLARE(zhiwen);
    LV_IMG_DECLARE(zhiwen_clicked);
    
}

main_windows::main_windows(_lv_obj_t *parent): task(this)
{
    if(parent!=NULL)
    {
        parent_windos=parent;
    }
    else
    {
        parent_windos=lv_scr_act();

    }
     back_img = lv_img_create(parent_windos);
     zhiwen_img = lv_img_create(parent_windos);
     time_label = lv_label_create(parent_windos);
     date_label = lv_label_create(parent_windos);
     temp_label = lv_label_create(parent_windos);
     temp_up_label = lv_label_create(parent_windos);
     temp_down_label = lv_label_create(parent_windos);
     triangle_up_img = lv_img_create(parent_windos);
     triangle_down_img = lv_img_create(parent_windos);
     addr_label = lv_label_create(parent_windos);
     addr_img = lv_img_create(parent_windos);
     weather_label = lv_label_create(parent_windos);
     weather_img = lv_img_create(parent_windos);

     pthread_mutex_init(&this->lock,NULL);

     temp.ave_temp=0;
     temp.max_temp=0;
     temp.min_temp=0;

     windows_open_flg=1;

}

void main_windows::close_windows()
{
    windows_open_flg=0;
    lv_obj_clean(lv_scr_act());
}
void main_windows::zhiwen_event_clicked(lv_event_t* event)
{
    main_windows* windows = (main_windows*)lv_event_get_user_data(event);
    if (lv_event_get_code(event) == LV_EVENT_PRESSED)
    {
        lv_img_set_src(windows->zhiwen_img, &zhiwen_clicked);
    }
    if (lv_event_get_code(event) == LV_EVENT_RELEASED)
    {
        lv_img_set_src(windows->zhiwen_img, &zhiwen);
        //lv_obj_clean(lv_scr_act());
        windows->close_windows();
        menu_windows *menu=new menu_windows();
        menu->drawing();
        //lv_scr_load_anim(menu_scr, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);

    }
}
void main_windows::drawing()
{
    /*backimage*/
    
    lv_img_set_src(back_img, &backimage);
    lv_obj_set_pos(back_img, 0, 0);
    lv_obj_set_size(back_img, 800, 480);
    lv_img_set_zoom(back_img,400);

    lv_img_set_src(zhiwen_img, &zhiwen);
    lv_obj_set_pos(zhiwen_img, 368, 260);
    lv_obj_set_size(zhiwen_img, 64, 64);
    lv_obj_add_flag(zhiwen_img, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(zhiwen_img,LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_event_cb(zhiwen_img, &main_windows::zhiwen_event_clicked, LV_EVENT_PRESSED, this);
    lv_obj_add_event_cb(zhiwen_img, &main_windows::zhiwen_event_clicked, LV_EVENT_RELEASED, this);

    /*time*/
    static lv_style_t time_label_style;
    
    lv_obj_set_size(time_label,301,107);
    lv_label_set_recolor(time_label,true);
    lv_label_set_text(time_label, "#2A82E4 12:38");
    lv_obj_set_pos(time_label,250,106);
    lv_obj_set_style_text_align(time_label, LV_TEXT_ALIGN_CENTER, 0);

    lv_style_init(&time_label_style);
    lv_style_set_text_font(&time_label_style, &font_72);
    lv_obj_add_style(time_label,&time_label_style,LV_STATE_DEFAULT);

    /*date*/
    static lv_style_t date_label_style;
    
    lv_obj_set_size(date_label, 330, 36);
    lv_label_set_recolor(date_label, true);
    lv_label_set_text(date_label, "#707070 December-06-2021");
    lv_obj_set_pos(date_label, 235, 204);
    lv_obj_set_style_text_align(date_label, LV_TEXT_ALIGN_CENTER, 0);

    lv_style_init(&date_label_style);
    lv_style_set_text_font(&date_label_style, &lv_font_montserrat_24);
    lv_obj_add_style(date_label, &date_label_style, LV_STATE_DEFAULT);

    /*temp*/
    static lv_style_t temp_label_style;
    
    lv_obj_set_size(temp_label, 250, 72);
    lv_label_set_recolor(temp_label, true);
    lv_label_set_text(temp_label, "#2A82E4 15°C");
    lv_obj_set_pos(temp_label, 0, 390);
    lv_obj_set_style_text_align(temp_label, LV_TEXT_ALIGN_RIGHT, 0);

    lv_style_init(&temp_label_style);
    lv_style_set_text_font(&temp_label_style, &font_72);
    lv_obj_add_style(temp_label, &temp_label_style, LV_STATE_DEFAULT);

    /*temp up*/
    static lv_style_t temp_up_label_style;
    
    lv_obj_set_size(temp_up_label, 80, 16);
    lv_label_set_recolor(temp_up_label, true);
    lv_label_set_text(temp_up_label, "#707070 25°C");
    lv_obj_set_pos(temp_up_label, 292, 398);
    lv_obj_set_style_text_align(temp_up_label, LV_TEXT_ALIGN_LEFT, 0);

    lv_style_init(&temp_up_label_style);
    lv_style_set_text_font(&temp_up_label_style, &lv_font_montserrat_16);
    lv_obj_add_style(temp_up_label, &temp_up_label_style, LV_STATE_DEFAULT);

    /*temp down*/
    static lv_style_t temp_down_label_style;
    
    lv_obj_set_size(temp_down_label, 80, 16);
    lv_label_set_recolor(temp_down_label, true);
    lv_label_set_text(temp_down_label, "#707070 13°C");
    lv_obj_set_pos(temp_down_label, 292, 422);
    lv_obj_set_style_text_align(temp_down_label, LV_TEXT_ALIGN_LEFT, 0);

    lv_style_init(&temp_down_label_style);
    lv_style_set_text_font(&temp_down_label_style, &lv_font_montserrat_16);
    lv_obj_add_style(temp_down_label, &temp_down_label_style, LV_STATE_DEFAULT);


    /*triangleimage*/
    
    lv_img_set_src(triangle_up_img, &triangleimage);
    lv_obj_set_pos(triangle_up_img, 265, 392);
    lv_obj_set_size(triangle_up_img, 32, 32);
    lv_img_set_zoom(triangle_up_img, 96);
    
    
    lv_img_set_src(triangle_down_img, &triangleimage);
    lv_obj_set_pos(triangle_down_img, 265, 414);
    lv_obj_set_size(triangle_down_img, 32, 32);
    lv_img_set_zoom(triangle_down_img, 96);
    lv_img_set_angle(triangle_down_img,1800);
    



   

    /*addr*/
    static lv_style_t addr_label_style;
    
    lv_obj_set_size(addr_label, 97, 48);
    lv_label_set_recolor(addr_label, true);
    lv_label_set_text(addr_label, "#707070 大连");
    lv_obj_set_pos(addr_label, 645, 363);
    lv_obj_set_style_text_align(addr_label, LV_TEXT_ALIGN_CENTER, 0);

    lv_style_init(&addr_label_style);
    lv_style_set_text_font(&addr_label_style, &font_48_ch);
    lv_obj_add_style(addr_label, &addr_label_style, LV_STATE_DEFAULT);

    /*位置图标*/
    
    lv_img_set_src(addr_img, &weizhi);
    lv_obj_set_pos(addr_img, 613, 373);
    lv_obj_set_size(addr_img, 32, 32);

    

    /*天气*/
    static lv_style_t weather_label_style;
    
    lv_obj_set_size(weather_label, 150, 48);
    lv_label_set_recolor(weather_label, true);
    lv_label_set_text(weather_label, "#707070 雨夹雪");
    lv_obj_set_pos(weather_label, 599, 412);
    lv_obj_set_style_text_align(weather_label, LV_TEXT_ALIGN_CENTER, 0);

    lv_style_init(&weather_label_style);
    lv_style_set_text_font(&weather_label_style, &font_48_ch);
    lv_obj_add_style(weather_label, &weather_label_style, LV_STATE_DEFAULT);

    /*天气图标*/
    
    lv_img_set_src(weather_img, &duoyun);
    lv_obj_set_pos(weather_img, 567, 422);
    lv_obj_set_size(weather_img, 32, 32);

}

void main_windows::update(void)
{
    if(windows_open_flg!=0)
    {
        update_time();
        update_temp();
        update_weather();
    }
}
void  main_windows::update_time(void)
{
    time_t raw_time = time(NULL);
    if (raw_time != cycle_count_time)
    {
        cycle_count_time=raw_time;
        memcpy(&time_date, localtime(&raw_time), sizeof(struct tm));

            string time;
            time.append("#2A82E4 ");
            time_date.tm_hour >= 10 ? time.append(to_my_string(time_date.tm_hour) + ":") : time.append("0" + to_my_string(time_date.tm_hour)+":");
            time_date.tm_min >= 10 ? time.append(to_my_string(time_date.tm_min)) : time.append("0" + to_my_string(time_date.tm_min));
            lv_label_set_text(time_label, time.c_str());
            string date;
            switch (time_date.tm_mon)
            {
            case 0:date.append("January"); break;
            case 1:date.append("February"); break;
            case 2:date.append("March"); break;
            case 3:date.append("April"); break;
            case 4:date.append("May"); break;
            case 5:date.append("June"); break;
            case 6:date.append("July"); break;
            case 7:date.append("August"); break;
            //case 8:date.append("September"); break;
            case 9:date.append("October"); break;
            case 10:date.append("November"); break;
            case 11:date.append("December"); break;
            }
            time_date.tm_mday > 9 ? date.append("-" + to_my_string(time_date.tm_mday )) : date.append("-0" + to_my_string(time_date.tm_mon));
            date.append("-"+to_my_string(1900+time_date.tm_year));
            lv_label_set_text(date_label, ("#707070 "+date).c_str());
    }
    
}
void main_windows::update_temp(void)
{
    struct TEMP T;
    /*http get temp*/
    time_t raw_time = time(NULL);
    if (raw_time != cycle_count_temp)
    {
        cycle_count_temp=raw_time;
    printf("call %d\n",time_date.tm_sec);
    /*互斥访问*/
    pthread_mutex_lock(&this->lock);
    memcpy(&T, &temp, sizeof(struct TEMP));
    pthread_mutex_unlock(&this->lock);
    /**/
    lv_label_set_text(temp_label, ("#2A82E4 "+ to_my_string(T.ave_temp)+"°C").c_str());
    lv_label_set_text(temp_up_label, ("#707070 " + to_my_string(T.max_temp) + "°C").c_str());
    lv_label_set_text(temp_down_label, ("#707070 " + to_my_string(T.min_temp) + "°C").c_str());
    }
}
void main_windows::update_weather(void)
{
    /*互斥访问*/
    time_t raw_time = time(NULL);
    if (raw_time != cycle_count_weather)
    {
        cycle_count_weather=raw_time;
    string wea="12";
    pthread_mutex_lock(&this->lock);
    wea=this->weather;
    pthread_mutex_unlock(&this->lock);
    lv_label_set_text(weather_label, ("#707070 "+wea).c_str());
    }
}
void main_windows::set_weather(string wea)
{
    pthread_mutex_lock(&this->lock);
    this->weather=wea;
    pthread_mutex_unlock(&this->lock);
}
void main_windows::set_temp(double max, double min, double ave)
{
    /*互斥访问*/
    pthread_mutex_lock(&this->lock);
    main_windows::temp.ave_temp = ave;
    main_windows::temp.max_temp = max;
    main_windows::temp.min_temp = min;
    pthread_mutex_unlock(&this->lock);
    /**/ 
}

string main_windows::to_my_string(double number)
{
    std::ostringstream oss;
    oss << number << std::setprecision(2) ;
    oss.unsetf(ios::fixed);
    return oss.str();
}


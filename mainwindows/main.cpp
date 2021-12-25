#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "lv_demos/lv_demo.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include "stdio.h"
#include <sys/time.h>
#include <main_windows.h>
#include <networkttask.h>
#include <menu_windows.h>
#include "playaudio.h"
#include "music_player.h"
#define DISP_BUF_SIZE (800 * 480)

int main(void)
{
    /*LittlevGL init*/
    lv_init();

    /*Linux frame buffer device init*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 800;
    disp_drv.ver_res    = 480;
    
    lv_disp_drv_register(&disp_drv);

    /*input initalize*/
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(& indev_drv);
    evdev_init();
    indev_drv.type=LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb=evdev_read;
    lv_indev_drv_register(&indev_drv);

    /*Create a Demo*/
    //lv_demo_widgets();
    // lv_demo_music();

    // main_windows mw=main_windows();
    // mw.drawing();
    
    // Playaudio play("/root/Mojito.wav");
    // play.start_play();

    // menu_windows menu_w=menu_windows();
    // menu_w.drawing();

    music_player player=music_player();
    player.drawing();

    printf("init evdev over\n");
    time_t t;
    time(&t);
    /*Handle LitlevGL tasks (tickless mode)*/
    while(1) {
        // mw.update();
        lv_task_handler();
        usleep(1000);
        time_t t2=time(NULL);
        if(t2-t>5)
        {
            t=t2;
            printf("tick\n");
        }
    }

    return 0;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}

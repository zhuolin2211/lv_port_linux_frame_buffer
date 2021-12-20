#include "networkttask.h"
#include <pthread.h>
#include <stdio.h>
#include "stdlib.h"
#include "time.h"
#include "unistd.h"
#include "http/http.h"
#include <vector>
#include <iostream>
#include "json.h"
#include "cstdlib"
#include "string"
#include "main_windows.h"
int http_init_flg = 0;
http http_client;
NetworkTtask::NetworkTtask(void * parent)
{
    if(http_init_flg == 0) {
        http_client.Init_Http();
        http_init_flg = 1;
    }
    int ret = pthread_create(&thread_task_id, NULL, &NetworkTtask::cycle, parent);
    if(ret != 0) {
        printf("creat pthread failed %s %d\n", __FUNCTION__, __LINE__);
    }
}

void * NetworkTtask::cycle(void * arge)
{
    time_t weather_cycle    = 0;
    uint8_t weather_fistrun = 0;
    uint8_t date_fistrun    = 0;

    while(1) {
        if(time(NULL) - weather_cycle > 3600 || weather_fistrun == 0) // 1hour
        {
            weather_fistrun = 1;
            weather_cycle   = time(NULL);
            weather_request(arge);
        }
        if(date_fistrun == 0) {
            date_fistrun = 1;
            date_request(arge);
        }
        sleep(1);
    }
}

void NetworkTtask::weather_request(void * parent)
{
    par_group par;
    vector<par_group> parameter;
    string url = "http://v0.yiketianqi.com/api";
    string response;
    par.key   = "appid";
    par.value = "48422558";
    parameter.push_back(par);
    par.key   = "appsecret";
    par.value = "4DfASqf0 ";
    parameter.push_back(par);
    par.key   = "version";
    par.value = "v62";
    parameter.push_back(par);
    par.key   = "cityid";
    par.value = "CN101070211";
    parameter.push_back(par);
    par.key   = "unescape";
    par.value = "1";
    parameter.push_back(par);
    http_client.Http_Get_addParameter(&url, parameter);
    std::cout << url << std::endl;
    response = http_client.Http_Get(url);
    if(response.empty() == true) {
        printf("get request is failed\n");
    } else {
        std::cout << response << std::endl;
        Json::Reader read;
        Json::Value value;
        read.parse(response, value);
        try {
            double ave_temp = stod(value["tem"].asCString());
            double max_temp = stod(value["tem1"].asCString());
            double min_temp = stod(value["tem2"].asCString());
            ((main_windows *)parent)->set_temp( max_temp, min_temp,ave_temp);
            ((main_windows *)parent)->set_weather(value["wea"].asString());
        } catch(const std::exception& e) {
            cout <<e.what()<< " json parse is error state" << endl;
        }
    }
}

void NetworkTtask::date_request(void * parent)
{
    string url = "http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp";
    string response;
    response = http_client.Http_Get(url);
    if(response.empty() == true) {
        printf("get request is failed\n");
    } else {
        std::cout << response << std::endl;
        Json::Reader read;
        Json::Value value;
        read.parse(response, value);
        try {
            uint64_t timestamp = strtoull (value["data"]["t"].asString().c_str(),NULL,10);
            /*set system time*/
            struct timeval tv;
            struct timezone tz;
            tv.tv_sec  = timestamp/1000;
            tv.tv_usec = timestamp%1000;
            settimeofday(&tv, &tz);
        } catch(const std::exception& e) {
            cout <<e.what()<< " json parse is error state" << endl;
        }
        
    }
}
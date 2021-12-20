#ifndef NETWORKTTASK_H
#define NETWORKTTASK_H
#include <pthread.h>

class NetworkTtask
{
public:
    NetworkTtask(void* parent);

private:
    pthread_t thread_task_id;
    static void* cycle(void *arge);
    static void weather_request(void* parent);
    static void date_request(void* parent);
};

#endif // NETWORKTTASK_H

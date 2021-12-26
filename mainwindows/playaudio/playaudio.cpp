#include "playaudio.h"
#include "string"
#include "stdio.h"
#include "time.h"
#include "sys/stat.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
Playaudio::Playaudio()
{
    channels     = 2;
    sample_rate  = 48100;
    bufferFrames = 512;
    device       = 0;
    offset       = 0;

    play_flg        = 0;
    play_flg_change = 0;
    play_time       = 0;

    play_progress = 0;
    play_done_flg = 0;
    pthread_mutex_init(&lock, NULL);
}
void Playaudio::start(const string & filename)
{
    audio_file = filename;
    int ret    = pthread_create(&thread_task_id, NULL, &Playaudio::run, this);
    if(ret != 0) {
        printf("creat pthread failed %s %d\n", __FUNCTION__, __LINE__);
    }
}
void * Playaudio::run(void * par)
{
    Playaudio * parent = (Playaudio *)par;
    /*open file*/
    parent->data.fd = fopen(parent->audio_file.c_str(), "rb");
    if(!parent->data.fd) {
        std::cout << "Unable to find or open file!\n";
        parent->my_exit(openfile_error);
    }
    parent->play_time            = parent->get_totaltime_s();
    parent->data.channels        = parent->channels;
    parent->oParams.deviceId     = parent->device;
    parent->oParams.nChannels    = parent->channels;
    parent->oParams.firstChannel = parent->offset;
    parent->oParams.deviceId     = parent->dac.getDefaultOutputDevice();

    try {
        parent->dac.openStream(&parent->oParams, NULL, FORMAT, parent->sample_rate, &parent->bufferFrames,
                               &stream_callback, (void *)&parent->data);

    } catch(RtAudioError & e) {
        std::cout << '\n' << e.getMessage() << '\n' << std::endl;
        fclose(parent->data.fd);
        parent->dac.closeStream();
        parent->my_exit(openstream_error);
    }
    parent->play_done_flg = 1;
    while(1) {
        usleep(50 * 1000); // wake every 100 ms to check if we're done
        parent->progress_signal((parent->dac.getStreamTime() / (double)parent->play_time) * 100);
        if(parent->play_operation() < 0) {
            parent->dac.closeStream();
            return (void *)NULL;
        }
    }
}

int Playaudio::stream_callback(void * outputBuffer, void * /*inputBuffer*/, unsigned int nBufferFrames,
                               double /*streamTime*/, RtAudioStreamStatus /*status*/, void * data)
{
    OutputData * oData = (OutputData *)data;

    // In general, it's not a good idea to do file input in the audio
    // callback function but I'm doing it here because I don't know the
    // length of the file we are reading.
    unsigned int count = fread(outputBuffer, oData->channels * sizeof(MY_TYPE), nBufferFrames, oData->fd);
    if(count < nBufferFrames) {
        unsigned int bytes     = (nBufferFrames - count) * oData->channels * sizeof(MY_TYPE);
        unsigned int startByte = count * oData->channels * sizeof(MY_TYPE);
        memset((char *)(outputBuffer) + startByte, 0, bytes);
        return 1;
    }

    return 0;
}

void Playaudio::my_exit(audio_error code)
{

    switch(code) {
        case no_error: {
            std::cout << "play over\r\n";
            break;
        }
        case openfile_error: {
            std::cout << "open file error \r\n";
            break;
        }
        case openstream_error: {
            std::cout << "open stream error \r\n";
            break;
        }
        default: {
            std::cout << "unknow error\r\n";
        }
    }
    play_flg = 0;
}
void Playaudio::start_play(void)
{
    pthread_mutex_lock(&lock);
    if(play_flg != 1) {
        play_flg        = 1;
        play_flg_change = 1;
    }
    pthread_mutex_unlock(&lock);
}
void Playaudio::suspend_play(void)
{
    pthread_mutex_lock(&lock);
    if(play_flg == 1) {
        play_flg        = 2;
        play_flg_change = 1;
    }
    pthread_mutex_unlock(&lock);
}
void Playaudio::stop_play(void)
{
    pthread_mutex_lock(&lock);
    if(play_flg != 0) {
        play_flg        = 0;
        play_flg_change = 1;
    }
    pthread_mutex_unlock(&lock);
}
void Playaudio::wait_stop_play(void)
{
    stop_play();
    while(1) {
        pthread_mutex_lock(&lock);
        if(play_done_flg == 0) {
            pthread_mutex_unlock(&lock);
            break;
        }
        pthread_mutex_unlock(&lock);
    }
}
int Playaudio::play_operation(void)
{
    if(pthread_mutex_trylock(&lock) == 0) {
        if(play_flg_change != 0) {
            play_flg_change = 0;
            switch(play_flg) {
                case 0: // stop
                {

                    dac.abortStream();
                    std::cout << "stop play music\r\n";
                    my_exit(no_error);
                    fclose(data.fd);
                    play_done_flg = 0;
                    pthread_mutex_unlock(&lock);
                    return -1;
                }
                case 1: // start
                {
                    play_done_flg = 1;
                    dac.startStream();
                    std::cout << "start play music\r\n";
                    break;
                }
                case 2: // suspend
                {
                    dac.stopStream();
                    std::cout << "suspend play music\r\n";
                    break;
                }
            }
        } else {
            if(dac.isStreamRunning() == false && (play_flg == 1)) {
                this->play_flg = 0;
                my_exit(no_error);
                pthread_mutex_unlock(&lock);
                return -1;
            }
        }
        pthread_mutex_unlock(&lock);
    }
    return 0;
}

/**/
unsigned long Playaudio::get_StrameSize(void)
{
    unsigned long filesize = 0;
    struct stat statbuff;
    if(stat(this->audio_file.c_str(), &statbuff) >= 0) {
        filesize = statbuff.st_size;
    }
    return filesize;
}
unsigned long Playaudio::get_totaltime_s(void)
{
    unsigned long file_size;
    unsigned long totaltime = 0;
    file_size               = this->get_StrameSize();
    if(file_size > 0) {
        totaltime = file_size / this->sample_rate / 2 / 2;
    }
    return totaltime;
}

void Playaudio::progress_signal(unsigned char pro)
{
    pthread_mutex_lock(&lock);
    play_progress = pro;
    pthread_mutex_unlock(&lock);
}
unsigned char Playaudio::get_progress(void)
{
    unsigned char pro;
    pthread_mutex_lock(&lock);
    pro = play_progress;
    pthread_mutex_unlock(&lock);
    return pro;
}

unsigned char Playaudio::is_play_done()
{
    return play_flg;
}
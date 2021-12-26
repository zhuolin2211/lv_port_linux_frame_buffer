#ifndef PLAYAUDIO_H
#define PLAYAUDIO_H

#include <string>
#include <pthread.h>
#include "pthread.h"
#include "rtrudio/RtAudio.h"
using namespace std;
typedef enum {
    no_error         = 0,
    openfile_error   = 1,
    openstream_error = 2,

} audio_error;
struct OutputData
{
    FILE * fd;
    unsigned int channels;
};
typedef signed short MY_TYPE;
#define FORMAT RTAUDIO_SINT16
#define SCALE 32767.0

class Playaudio {

  public:
    Playaudio();
    void start_play(void);
    void suspend_play(void);
    void stop_play(void);
    void wait_stop_play(void);
    unsigned long get_StrameSize(void);
    unsigned long get_totaltime_s(void);
  void start(const string & filename);
  protected:
    
    static void *run(void* par);
    void stop_run();
    void my_exit(audio_error code);
    void progress_signal(unsigned char pro);
    unsigned char get_progress(void);
    unsigned char is_play_done();

  private:
    string audio_file;
    OutputData data;
    RtAudio::StreamParameters oParams;
    RtAudio dac;

    /*parmeter*/
    unsigned int bufferFrames;
    unsigned int channels;
    unsigned int sample_rate;
    unsigned int device;
    unsigned int offset;

    unsigned char play_flg; // play 1 suspend 2 stop 0
    unsigned char play_flg_change;

    unsigned char play_progress;
    unsigned play_done_flg;

    pthread_mutex_t lock;
    pthread_t thread_task_id;
    int play_operation(void);
    static int stream_callback(void * outputBuffer, void * /*inputBuffer*/, unsigned int nBufferFrames,
                               double /*streamTime*/, RtAudioStreamStatus /*status*/, void * data);
    unsigned long play_time;
};

#endif // PLAYAUDIO_H

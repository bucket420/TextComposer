#include "Wave.h"
#include "Input.h"
#include "portaudio.h"
#include "sciter-x.h"
#include "sciter-x-window.hpp"
#include <math.h>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <chrono>
#include <thread>

#define FRAMES_PER_BUFFER  (64)

class ScopedPaHandler
{
public:
    ScopedPaHandler()
        : _result(Pa_Initialize())
    {
    }
    ~ScopedPaHandler()
    {
        if (_result == paNoError)
        {
            Pa_Terminate();
        }
    }

    PaError result() const { return _result; }

private:
    PaError _result;
};

class frame : public sciter::window {
public:
    frame() : window(SW_TITLEBAR | SW_RESIZEABLE | SW_CONTROLS | SW_MAIN | SW_ENABLE_DEBUG) {}

    std::vector<double> getWavetable(int mode, std::string key, std::string scaleType, std::string input, std::string timeSignatureLower, std::string BPM)
    {
        Wave wave;
        switch (mode)
        {
        case 1:
            wave = Input::inputToWavetableFirstMode(input, timeSignatureLower, BPM);
            break;
        case 2:
            wave = Input::inputToWavetableSecondMode(input, key, scaleType, timeSignatureLower, BPM);
            break;
        }
        return wave.waveTable;
    }

    struct Data
    {
        std::vector<double>* waveTable;
        int phase = 0;
    };

    PaStream* stream;
    bool stopPlayback;
    static int paCallback(const void* inputBuffer, void* outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void* userData)
    {
        float* out = (float*)outputBuffer;
        unsigned long i;

        (void)timeInfo; /* Prevent unused variable warnings. */
        (void)statusFlags;
        (void)inputBuffer;

        Data* data = (Data*) userData;
        double duration = framesPerBuffer / Wave::SAMPLE_RATE;
        int increment = 1;

        for (i = 0; i < framesPerBuffer; i++)
        {
            *out++ = (*(data->waveTable))[data->phase];  /* left */
            *out++ = (*(data->waveTable))[data->phase];  /* right */
            data->phase += increment;
        }

        return paContinue;

    }

    void start(int mode, std::string key, std::string scaleType, std::string input, std::string timeSignatureLower, std::string BPM)
    {
        if (Pa_IsStreamActive(stream) == 1)
        {
            return;
        }

        ScopedPaHandler paInit;
        if (paInit.result() != paNoError) return;
        std::vector<double> waveTable = getWavetable(mode, key, scaleType, input, timeSignatureLower, BPM);
        double duration = (double)waveTable.size() / (double)Wave::SAMPLE_RATE;

        if (waveTable.empty())
        {
            return;
        }

        Data data;
        data.waveTable = &waveTable;

        int err = Pa_OpenDefaultStream(&stream,
            0,          /* no input channels */
            2,          /* stereo output */
            paFloat32,  /* 32 bit floating point output */
            Wave::SAMPLE_RATE,
            512,        /* frames per buffer */
            paCallback,
            &data);

        if (err != paNoError)
        {
            Pa_CloseStream(stream);
            return;
        }

        err = Pa_StartStream(stream);

        if (err != paNoError)
        {
            Pa_StopStream(stream);
            Pa_CloseStream(stream);
            return;
        }
        stopPlayback = false;
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        while (!stopPlayback)
        {
            if (std::chrono::steady_clock::now() - start > std::chrono::milliseconds((int)(duration * 1000)))
            {
                break;
            }
        }
        if (stream != 0)
        {
            Pa_StopStream(stream);
            Pa_CloseStream(stream);
        }


        return;
    }

    // passport - lists native functions and properties exposed to script:
    SOM_PASSPORT_BEGIN(frame)
        SOM_FUNCS(
            SOM_FUNC(stop),
            SOM_FUNC(play),
            SOM_FUNC(getDuration)
        )
        SOM_PASSPORT_END

    // function exposed to script:
    void play(int mode, std::string key, std::string scaleType, std::string input, std::string timeSignatureLower, std::string BPM)
    {
        std::thread t1(&frame::start, this, mode, key, scaleType, input, timeSignatureLower, BPM);
        t1.detach();
    }

    void stop()
    {
        stopPlayback = true;
    }

    double getDuration(int mode, std::string key, std::string scaleType, std::string input, std::string timeSignatureLower, std::string BPM)
    {
        return (double)(getWavetable(mode, key, scaleType, input, timeSignatureLower, BPM).size()) / (double)Wave::SAMPLE_RATE;
    }
};

#include "resources.cpp" // resources packaged into binary blob.

int uimain(std::function<int()> run) {

    sciter::archive::instance().open(aux::elements_of(resources)); // bind resources[] (defined in "resources.cpp") with the archive

    sciter::om::hasset<frame> pwin = new frame();

    // note: this:://app URL is dedicated to the sciter::archive content associated with the application
    pwin->load(WSTR("this://app/main.htm"));
    //or use this to load UI from  
    //  pwin->load( WSTR("file:///home/andrew/Desktop/Project/res/main.htm") );

    pwin->expand();

    return run();
}

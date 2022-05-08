#pragma once
#include "TextToAudio.h"
#include "Melody.h"
#include "ChordProgression.h"
#include <chrono>


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

bool TextToAudio::isPlaying()
{
    return Pa_IsStreamActive(stream) == 1;
}

void TextToAudio::setWave(int mode, std::string key, std::string scaleType, std::string input)
{
    switch (mode)
    {
    case 1:
        *signal = ChordProgression::ChordProgression(input, key, scaleType);
        break;
    case 2:
        *signal = Melody::Melody(input);
        break;
    }
}

int TextToAudio::paCallback(const void* inputBuffer, void* outputBuffer,
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

    Signal* data = (Signal*)userData;
    double duration = framesPerBuffer / Signal::SAMPLE_RATE;
    int increment = 1;

    for (i = 0; i < framesPerBuffer; i++)
    {
        *out++ = data->get(data->phase);  /* left */
        *out++ = data->get(data->phase);  /* right */
        data->phase += increment;
    }

    return paContinue;

}

void TextToAudio::start()
{
    if (Pa_IsStreamActive(stream) == 1)
    {
        return;
    }
    ScopedPaHandler paInit;
    if (paInit.result() != paNoError) return;
    double duration = signal->getDuration();

    if (signal->isEmpty())
    {
        return;
    }

    int err = Pa_OpenDefaultStream(&stream,
        0,          /* no input channels */
        2,          /* stereo output */
        paFloat32,  /* 32 bit floating point output */
        Signal::SAMPLE_RATE,
        512,        /* frames per buffer */
        paCallback,
        signal.get());

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

void TextToAudio::stop()
{
    stopPlayback = true;
}

double TextToAudio::getDuration()
{
    return signal->getDuration();
}
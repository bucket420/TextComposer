#pragma once
#include <stdio.h>
#include <map>
#include <string>
#include <math.h>
#include <vector>
#include "portaudio.h"
#include "AudioOutput.h"
#include "Constants.h"

#define M_PI  (3.14159265)

AudioOutput::AudioOutput(std::vector<double>* waveTable) : left_phase(0), right_phase(0)
{
    this->waveTable = waveTable;
    //sprintf_s(message, "No Message");
};

bool AudioOutput::open(PaDeviceIndex index)
{
    PaStreamParameters outputParameters;

    outputParameters.device = index;
    if (outputParameters.device == paNoDevice) {
        return false;
    }

    const PaDeviceInfo* pInfo = Pa_GetDeviceInfo(index);
    //if (pInfo != 0)
    //{
    //    printf("Output device name: '%s'\r", pInfo->name);
    //}

    outputParameters.channelCount = 2;       /* stereo output */
    outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    PaError err = Pa_OpenStream(
        &stream,
        NULL, /* no input */
        &outputParameters,
        SAMPLE_RATE,
        paFramesPerBufferUnspecified,
        paClipOff,      /* we won't output out of range samples so don't bother clipping them */
        &AudioOutput::paCallback,
        this            /* Using 'this' for userData so we can cast to AudioOutput* in paCallback method */
    );

    if (err != paNoError)
    {
        /* Failed to open stream to device !!! */
        return false;
    }

    err = Pa_SetStreamFinishedCallback(stream, &AudioOutput::paStreamFinished);

    if (err != paNoError)
    {
        Pa_CloseStream(stream);
        stream = 0;

        return false;
    }

    return true;
}

bool AudioOutput::close()
{
    if (stream == 0)
        return false;

    PaError err = Pa_CloseStream(stream);
    stream = 0;

    return (err == paNoError);
}


bool AudioOutput::start()
{
    if (stream == 0)
        return false;

    PaError err = Pa_StartStream(stream);

    return (err == paNoError);
}

bool AudioOutput::stop()
{
    if (stream == 0)
        return false;

    PaError err = Pa_StopStream(stream);

    return (err == paNoError);
}

/* The instance callback, where we have access to every method/variable in object of class AudioOutput */
int AudioOutput::paCallbackMethod(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags)
{
    float* out = (float*)outputBuffer;
    unsigned long i;

    (void)timeInfo; /* Prevent unused variable warnings. */
    (void)statusFlags;
    (void)inputBuffer;

    int increment = 1;

    for (i = 0; i < framesPerBuffer; i++)
    {
        *out++ = (*waveTable)[left_phase];  /* left */
        *out++ = (*waveTable)[right_phase];  /* right */
        left_phase += increment;
        right_phase += increment;
        if (left_phase == waveTable->size()) return paComplete;
    }

    return paContinue;

}

/* This routine will be called by the PortAudio engine when audio is needed.
** It may called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
int AudioOutput::paCallback(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData)
{
    /* Here we cast userData to AudioOutput* type so we can call the instance method paCallbackMethod, we can do that since
       we called Pa_OpenStream with 'this' for userData */
    return ((AudioOutput*)userData)->paCallbackMethod(inputBuffer, outputBuffer,
        framesPerBuffer,
        timeInfo,
        statusFlags);
}


void AudioOutput::paStreamFinishedMethod()
{
    //printf("Stream Completed: %s\n", message);
}

/*
 * This routine is called by portaudio when playback is done.
 */
void AudioOutput::paStreamFinished(void* userData)
{
    return ((AudioOutput*)userData)->paStreamFinishedMethod();
}

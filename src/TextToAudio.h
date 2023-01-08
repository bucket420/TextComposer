#pragma once
#include <memory>
#include "portaudio.h"
#include "Signal.h"

class TextToAudio
{
public:
    /* Audio stream */
	PaStream* stream;

    /* Stop the track if this is true */
	bool stopPlayback;

    /* The signal to be played */
    std::unique_ptr<Signal> signal = std::unique_ptr<Signal>(new Signal);

    /* Get the duration of the signal */
    double getDuration();

    /* True if the audio is being played */
    bool isPlaying();

    /* Called by portaudio engine when audio is needed */
    static int paCallback(const void* inputBuffer, void* outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void* userData);

    /* Set the wavetable of the signal */
    void setWave(int mode, std::string key, std::string scaleType, std::string input);

    /* Start playing */
    void start();

    /* Stop playing*/
    void stop();

private:

};
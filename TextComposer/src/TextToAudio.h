#pragma once
#include "Signal.h"
#include "portaudio.h"
#include <memory>

class TextToAudio
{
public:
	PaStream* stream;
	bool stopPlayback;
    std::unique_ptr<Signal> signal = std::unique_ptr<Signal>(new Signal);

    void setWave(int mode, std::string key, std::string scaleType, std::string input);
    double getDuration();
    static int paCallback(const void* inputBuffer, void* outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void* userData);
    bool isPlaying();
    void start();
    void stop();

private:

};
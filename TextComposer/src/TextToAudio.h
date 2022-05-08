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

    double getDuration();
    bool isPlaying();
    static int paCallback(const void* inputBuffer, void* outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void* userData);
    void setWave(int mode, std::string key, std::string scaleType, std::string input);
    void start();
    void stop();

private:

};
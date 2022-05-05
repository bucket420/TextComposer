#pragma once
#include "Wave.h"
#include "Melody.h"
#include "ChordProgression.h"
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

class TextToAudio
{
public:
	PaStream* stream;
	bool stopPlayback;
    std::vector<double> waveTable;

    void setWavetable(int mode, std::string key, std::string scaleType, std::string input);
    double getDuration();
    static int paCallback(const void* inputBuffer, void* outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void* userData);
    void start();
    void stop();

private:

};
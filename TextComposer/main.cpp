#include "Wave.h"
#include "Input.h"
#include "Constants.h"
#include "portaudio.h"
#include "AudioOutput.h"
#include "sciter-x.h"
#include "sciter-x-window.hpp"
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <map>
#include <string>
#include <vector>
#include <functional>

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

    // passport - lists native functions and properties exposed to script:
    SOM_PASSPORT_BEGIN(frame)
        SOM_FUNCS(
            SOM_FUNC(output),
        )
        SOM_PASSPORT_END

    // function expsed to script:
    int output(std::string mode, std::string key, std::string scaleType, std::string input, std::string timeSignatureLower, std::string BPM)
    {
        std::vector<double> waveTable;
        ScopedPaHandler paInit;

        if (mode == "1")
        {
            waveTable = Input::inputToWavetableFirstMode(input, timeSignatureLower, BPM);
        }
        if (mode == "2")
        {
            waveTable = Input::inputToWavetableSecondMode(input, key, scaleType, timeSignatureLower, BPM);
        }
        AudioOutput output(waveTable);
        AudioOutput* outputPointer = &output;

        if (paInit.result() != paNoError) goto error;


        if (outputPointer->open(Pa_GetDefaultOutputDevice()))
        {
            std::cout << "Playing" << std::endl;
            if (outputPointer->start())
            {
                Pa_Sleep((outputPointer->waveTable.size()) / 44.1);
                outputPointer->stop();
            }

            outputPointer->close();
        }


    return paNoError;

    error:
        fprintf(stderr, "An error occurred while using the portaudio stream\n");
        fprintf(stderr, "Error number: %d\n", paInit.result());
        fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(paInit.result()));
        return 1;
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

/*******************************************************************/
//int main(void);
//int main(void)
//{
//    int mode;
//    std::string key;
//    std::string scaleType;
//    std::string input;
//    std::string timeSignatureLower;
//    std::string BPM;
//    std::vector<double> waveTable;
//    ScopedPaHandler paInit;
//    char keepGoing = 'y';
//
//    while (keepGoing == 'y')
//    {
//        std::cout << "Choose your mode:     1. Notes        2. Chord Progression Formula" << std::endl;
//        std::cin >> mode;
//        std::cout << "Time signature lower numeral: " << std::endl;
//        std::cin >> timeSignatureLower;
//        std::cout << "Beats per minute: " << std::endl;
//        std::cin >> BPM;
//
//        if (mode == 2)
//        {
//            std::cout << "Choose your scale: " << std::endl;
//            std::cin >> key >> scaleType;
//        }
//
//        std::cout << "Your score: " << std::endl;
//
//        std::cin >> input;
//
//
//        if (mode == 1)
//        {
//            waveTable = Input::inputToWavetableFirstMode(input, timeSignatureLower, BPM);
//            /*for (int i = 0; i < 300; i++)
//            {
//                std::cout << waveTable[i] << std::endl;
//            }*/
//        }
//        if (mode == 2)
//        {
//            waveTable = Input::inputToWavetableSecondMode(input, key, scaleType, timeSignatureLower, BPM);
//        }
//        AudioOutput output(waveTable);
//        AudioOutput* outputPointer = &output;
//
//
//
//        if (paInit.result() != paNoError) goto error;
//
//
//        if (outputPointer->open(Pa_GetDefaultOutputDevice()))
//        {
//            std::cout << "Playing" << std::endl;
//            if (outputPointer->start())
//            {
//                Pa_Sleep((outputPointer->waveTable.size()) / 44.1);
//                outputPointer->stop();
//            }
//
//            outputPointer->close();
//        }
//        std::cout << "Continue? (y/n)" << std::endl;
//        std::cin >> keepGoing;
//    }
//
//    return paNoError;
//
//error:
//    fprintf(stderr, "An error occurred while using the portaudio stream\n");
//    fprintf(stderr, "Error number: %d\n", paInit.result());
//    fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(paInit.result()));
//    return 1;
//}

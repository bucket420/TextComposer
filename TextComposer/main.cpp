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
    int output(int mode, std::string key, std::string scaleType, std::string input, std::string timeSignatureLower, std::string BPM)
    {
        std::vector<double> waveTable;
        ScopedPaHandler paInit;

        switch (mode)
        {
            case 1:
                waveTable = Input::inputToWavetableFirstMode(input, timeSignatureLower, BPM);
                break;
            case 2:
                waveTable = Input::inputToWavetableSecondMode(input, key, scaleType, timeSignatureLower, BPM);
                break;
        }
        if (waveTable.empty())
        {
            return 1;
        }
        AudioOutput output(&waveTable);

        if (paInit.result() != paNoError) goto error;

        if ((&output)->open(Pa_GetDefaultOutputDevice()))
        {
            if ((&output)->start())
            {
                Pa_Sleep(((&waveTable)->size()) / 44.1);
                (&output)->stop();
            }

            (&output)->close();
        }


    return paNoError;

    error:
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

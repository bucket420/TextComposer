#pragma once
#include <thread>
#include "portaudio.h"
#include "sciter-x.h"
#include "sciter-x-window.hpp"
#include "TextToAudio.h"

class frame : public sciter::window {
public:
    frame() : window(SW_TITLEBAR | SW_RESIZEABLE | SW_CONTROLS | SW_MAIN | SW_ENABLE_DEBUG) {}

    TextToAudio Player;
    bool validInput = true;

    void start()
    {
        (&Player)->start();
    }

    // passport - lists native functions and properties exposed to script:
    SOM_PASSPORT_BEGIN(frame)
        SOM_FUNCS(
            SOM_FUNC(stop),
            SOM_FUNC(play),
            SOM_FUNC(isValid)
        )
        SOM_PASSPORT_END

    // function exposed to script:
    void play(int mode, std::string key, std::string scaleType, std::string input, std::string timeSignatureLower, std::string BPM)
    {
        if ((&Player)->isPlaying())
        {
            return;
        }
        Signal::setTimeSignatureLowerAndBPM(timeSignatureLower, BPM);
        (&Player)->setWave(mode, key, scaleType, input);
        validInput = (&Player)->getDuration() > 0;
        std::thread t1(&frame::start, this);
        t1.detach();
    }

    void stop()
    {
        (&Player)->stop();
    }

    double isValid()
    {
        return validInput;
    }
};

#include "resources.cpp" // resources packaged into binary blob.

int uimain(std::function<int()> run) {

    sciter::archive::instance().open(aux::elements_of(resources)); // bind resources[] (defined in "resources.cpp") with the archive
    sciter::om::hasset<frame> pwin = new frame();

    pwin->load(WSTR("this://app/main.htm"));
    pwin->expand();

    return run();
}

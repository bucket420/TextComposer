#include "Wave.h"
#include "Input.h"
#include "Constants.h"
#include "portaudio.h"
#include "AudioOutput.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <map>
#include <string>
#include <vector>

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

/*******************************************************************/
int main(void);
int main(void)
{
    int mode;
    std::string key;
    std::string scaleType;
    std::string input;
    std::vector<double> waveTable;
    ScopedPaHandler paInit;
    char keepGoing = 'y';

    while (keepGoing == 'y')
    {
        std::cout << "Choose your mode:     1. Notes        2. Chord Progression Formula" << std::endl;
        std::cin >> mode;

        if (mode == 2)
        {
            std::cout << "Choose your scale: " << std::endl;
            std::cin >> key >> scaleType;
        }

        std::cout << "Your score: " << std::endl;

        std::cin >> input;


        if (mode == 1)
        {
            Input inputHandler(input);
            waveTable = inputHandler.wave.waveTable;
        }
        if (mode == 2)
        {
            Input inputHandler(input, key, scaleType);
            waveTable = inputHandler.wave.waveTable;
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
        std::cout << "Continue? (y/n)" << std::endl;
        std::cin >> keepGoing;
    }

    return paNoError;

error:
    fprintf(stderr, "An error occurred while using the portaudio stream\n");
    fprintf(stderr, "Error number: %d\n", paInit.result());
    fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(paInit.result()));
    return 1;
}

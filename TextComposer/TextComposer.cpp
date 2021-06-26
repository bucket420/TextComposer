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
    std::cout << "Your score: ";

    std::string input;
    std::cin >> input;

    Input inputHandler(input);
    std::vector<double> waveTable = inputHandler.wave.waveTable;
    std::cout << waveTable.size() << std::endl;
    AudioOutput output(waveTable);
    AudioOutput* outputPointer = &output;

    std::cout << outputPointer->waveTable.size() << std::endl;
    //for (int i = 0; i < 2048; i++)
    //{
    //    std::cout << outputPointer->waveTable[i] << std::endl;
    //}


    ScopedPaHandler paInit;
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

    printf("Test finished.\n");
    return paNoError;

error:
    fprintf(stderr, "An error occurred while using the portaudio stream\n");
    fprintf(stderr, "Error number: %d\n", paInit.result());
    fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(paInit.result()));
    return 1;
}

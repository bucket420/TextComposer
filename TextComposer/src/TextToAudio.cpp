#include "TextToAudio.h"

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

struct Data
{
    std::vector<double> waveTable;
    int phase = 0;
};

void TextToAudio::setWave(int mode, std::string key, std::string scaleType, std::string input)
{
    switch (mode)
    {
    case 1:
        *wave = Melody::Melody(input);
        break;
    case 2:
        *wave = ChordProgression::ChordProgression(input, key, scaleType);
        break;
    }
}

int TextToAudio::paCallback(const void* inputBuffer, void* outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData)
{
    float* out = (float*)outputBuffer;
    unsigned long i;

    (void)timeInfo; /* Prevent unused variable warnings. */
    (void)statusFlags;
    (void)inputBuffer;

    Data* data = (Data*)userData;
    double duration = framesPerBuffer / Wave::SAMPLE_RATE;
    int increment = 1;

    for (i = 0; i < framesPerBuffer; i++)
    {
        *out++ = data->waveTable[data->phase];  /* left */
        *out++ = data->waveTable[data->phase];  /* right */
        data->phase += increment;
    }

    return paContinue;

}

void TextToAudio::start()
{
    if (Pa_IsStreamActive(stream) == 1)
    {
        return;
    }
    ScopedPaHandler paInit;
    if (paInit.result() != paNoError) return;
    double duration = wave->getDuration();

    if (wave->isEmpty())
    {
        return;
    }

    Data data;
    data.waveTable = wave->getWaveTable();

    int err = Pa_OpenDefaultStream(&stream,
        0,          /* no input channels */
        2,          /* stereo output */
        paFloat32,  /* 32 bit floating point output */
        Wave::SAMPLE_RATE,
        512,        /* frames per buffer */
        paCallback,
        &data);

    if (err != paNoError)
    {
        Pa_CloseStream(stream);
        return;
    }

    err = Pa_StartStream(stream);

    if (err != paNoError)
    {
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
        return;
    }
    stopPlayback = false;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while (!stopPlayback)
    {
        if (std::chrono::steady_clock::now() - start > std::chrono::milliseconds((int)(duration * 1000)))
        {
            break;
        }
    }
    if (stream != 0)
    {
        Pa_StopStream(stream);
        Pa_CloseStream(stream);
    }

    return;
}

void TextToAudio::stop()
{
    stopPlayback = true;
}

double TextToAudio::getDuration()
{
    return wave->getDuration();
}
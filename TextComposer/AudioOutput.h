#pragma once
#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include "portaudio.h"

class AudioOutput
{
public:
	AudioOutput(std::vector<double>* waveTable);

private:
	/*const std::map<std::string, float> NOTE_TO_FREQUENCIES;
	const std::map<std::string, float> TYPE_TO_DURATION;*/
	PaStream* stream;
	int left_phase;
	int right_phase;
	char message[20];

	/* The instance callback, where we have access to every method/variable in object of class AudioOutput */
	int paCallbackMethod(const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags);

	/* This routine will be called by the PortAudio engine when audio is needed.
	** It may called at interrupt level on some machines so don't do anything
	** that could mess up the system like calling malloc() or free().
	*/
	static int paCallback(const void* inputBuffer, void* outputBuffer,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void* userData);

	void paStreamFinishedMethod();

	static void paStreamFinished(void* userData);


public:
	std::vector<double>* waveTable;

	bool open(PaDeviceIndex index);
	bool close();
	bool start();
	bool stop();
};


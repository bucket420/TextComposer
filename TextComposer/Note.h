#pragma once
#include "Wave.h"

class Note : public Wave
{
	using Wave::Wave;

public:
	void setWaveTable(std::string note, std::string timeSignatureLower, std::string BPM);

private:
	double getNoteFreq(std::string name);
	double getDuration(std::string note, std::string timeSignatureLower, std::string BPM);
};
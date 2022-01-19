#pragma once
#include "Wave.h"
#include <array>

class Chord : public Wave
{
	using Wave::Wave;

public:
	void setWaveTable(std::string chord, std::array<double, 25> scale, std::string scaleType, std::string timeSignatureLower, std::string BPM);

private:
	double getDuration(std::string chord, std::string timeSignatureLower, std::string BPM);
	static std::array<double, 25> createTwoOctaveScale(std::string key);
	std::string getRomanNumber(std::string chord);
	std::string toUpper(std::string string);
	double getNoteFreq(std::string name);
};
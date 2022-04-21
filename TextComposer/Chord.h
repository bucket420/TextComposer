#pragma once
#include "Wave.h"
#include <array>

class Chord : public Wave
{
public:
	Chord(std::string chord, std::array<double, 25> scale, std::string scaleType, std::string timeSignatureLower, std::string BPM);

private:
	std::string chord;

	static double getDuration(std::string chord, std::string timeSignatureLower, std::string BPM);
	static std::string getRomanNumber(std::string chord);
	static std::string toUpper(std::string string);
	void setWaveTable(std::array<double, 25> scale, std::string scaleType, std::string timeSignatureLower, std::string BPM);

};
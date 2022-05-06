#pragma once
#include "Signal.h"
#include <array>

class Chord : public Signal
{
public:
	Chord(std::string chord, std::array<double, 25> scale, std::string scaleType);

private:
	std::string chord;

	static std::string getRomanNumber(std::string chord);
	static std::string toUpper(std::string string);
	void setWaveTable(std::array<double, 25> scale, std::string scaleType);

};
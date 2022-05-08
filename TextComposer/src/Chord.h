#pragma once
#include "Signal.h"
#include <array>

class Chord : public Signal
{
public:
	Chord(std::string chord, std::array<double, 25> scale, std::string scaleType);

private:
	std::string chord;
	std::array<double, 25> scale;
	std::string scaleType;
	static std::string getChordSymbol(std::string chord);
	static std::string toUpper(std::string string);
	void setWaveTable();

};
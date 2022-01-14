#pragma once
#include <vector>
#include <string>
#include <array>
#include "Wave.h"

namespace Input
{
	// Common:
	double getDuration(std::string note, std::string timeSignatureLower, std::string BPM);

	// First mode:
	std::vector<int> getNoteIndexes(std::string input);
	std::vector<std::string> getNotes(std::string input);
	double getNoteFreq(std::string name);
	Wave inputToWavetableFirstMode(std::string input, std::string timeSignatureLower, std::string BPM);

	// Second mode:
	std::array<double, 25> createTwoOctaveScale(std::string key);
	Wave inputToWavetableSecondMode(std::string input, std::string key, std::string scaleType, std::string timeSignatureLower, std::string BPM);
	std::vector<int> getChordIndexes(std::string input);
	std::vector<std::string> getChords(std::string input);
	std::vector<double> chordToWavetable(std::string chord, std::array<double, 25> scale, std::string scaleType, std::string timeSignatureLower, std::string BPM);
	std::string getRomanNumber(std::string chord);
	std::string toUpper(std::string string);
};
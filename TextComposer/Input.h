#pragma once
#include <vector>
#include <string>
#include <array>
#include "Wave.h"

class Input
{
public:
	Input(std::string input);
	Input(std::string input, std::string key, std::string scaleType);
	Wave wave;

private:
	// Common:
	double getDuration(std::string note);

	// First mode:
	std::vector<int> getNoteIndexes(std::string input);
	std::vector<std::string> getNotes(std::string input);
	double getNoteFreq(std::string name);
	Wave inputToWavetableFirstMode(std::string input);

	// Second mode:
	std::array<double, 25> createTwoOctaveScale(std::string key);
	Wave inputToWavetableSecondMode(std::string input, std::string key, std::string scaleType);
	std::vector<int> getChordIndexes(std::string input);
	std::vector<std::string> getChords(std::string input);
	std::vector<double> chordToWavetable(std::string chord, std::array<double, 25> scale, std::string scaleType);
	std::string getRomanNumber(std::string chord);
	std::string toUpper(std::string string);
};
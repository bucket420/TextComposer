#pragma once
#include <vector>
#include <string>
#include "Wave.h"

class Input
{
public:
	Input(std::string* input);
	std::string* input;
	std::vector<double>* waveTable;

private:
	std::vector<int> getNoteIndexes(std::string* input);
	std::vector<std::string> getNotes(std::string* input);
	double getNoteDuration(std::string note);
	double getNoteFreq(std::string name);
	std::vector<double>* inputToWavetable(std::string* input);
	
};
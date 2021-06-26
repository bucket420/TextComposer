#pragma once
#include <vector>
#include <string>
#include "Wave.h"

class Input
{
public:
	Input(std::string input);
	Wave wave;

private:
	std::vector<int> getNoteIndexes(std::string input);
	std::vector<std::string> getNotes(std::string input);
	double getNoteDuration(std::string note);
	double getNoteFreq(std::string name);
	Wave inputToWavetable(std::string input);
	
};
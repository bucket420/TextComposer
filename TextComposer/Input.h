#pragma once
#include <vector>
#include <string>
#include "Wave.h"

class Input
{
public:
	Input(std::string* input);
	std::string* input;
	Wave* soundWave;

private:
	std::vector<int> getNoteIndexes();
	std::vector<std::string> getNotes();
	
};
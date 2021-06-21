#pragma once
#include <vector>
#include <string>
#include "Wave.h"

class Note : public Wave 
{
public:
	Note(std::string name, double duration);

private:
	double noteToFreq(std::string name);
};
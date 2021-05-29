#pragma once
#include <vector>
#include <string>
#include "Wave.h"

class Note : public Wave 
{
public:
	Note(std::string name, double duration);
	std::string* noteName;
	double* duration;

	Note sharp(Note* note);
	Note flat(Note* note);
	

private:
	double noteToFreq(std::string name);
};
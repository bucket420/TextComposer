#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include "Constants.h"
#include "Wave.h"
#include "Note.h"

Note::Note(std::string name, double duration) 
{
	*noteName = name;
	*(this->duration) = duration;
	*waveTable = createSine(noteToFreq(name), duration);
}

double Note::noteToFreq(std::string name) 
{
	char letter = name[0];
	int octaveNumber = name[1] - '0';
	const char* iterator = std::find(FIRST_OCTAVE, FIRST_OCTAVE + 7, letter);
	int index = iterator - FIRST_OCTAVE;
	return FIRST_OCTAVE_FREQ[index] * pow(2, octaveNumber);
}
#pragma once
#include <vector>
#include <string>
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

}
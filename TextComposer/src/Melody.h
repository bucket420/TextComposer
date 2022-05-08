#pragma once
#include "Note.h"

class Melody : public Signal
{
public:
	Melody(std::string melody);

private:
	std::string melody;

	std::vector<int> getNoteIndexes();
	std::vector<std::string> getNotes();
	void setWaveTable();
};
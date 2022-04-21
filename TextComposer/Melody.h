#pragma once
#include "Note.h"

class Melody : public Wave
{
public:
	Melody(std::string melody, std::string timeSignatureLower, std::string BPM);

private:
	std::string melody;
	std::vector<int> getNoteIndexes();
	std::vector<std::string> getNotes();
	void setWaveTable(std::string timeSignatureLower, std::string BPM);
};
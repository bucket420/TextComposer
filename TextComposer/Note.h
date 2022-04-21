#pragma once
#include "Wave.h"

class Note : public Wave
{
public:
	Note(std::string note, std::string timeSignatureLower, std::string BPM);

private:
	std::string note;
	double getDuration(std::string timeSignatureLower, std::string BPM);
	void setWaveTable(std::string timeSignatureLower, std::string BPM);

};
#pragma once
#include "Wave.h"

class Note : public Wave
{
public:
	Note(std::string note);

private:
	std::string note;
	void setWaveTable();

};
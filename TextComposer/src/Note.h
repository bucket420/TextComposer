#pragma once
#include "Signal.h"

class Note : public Signal
{
public:
	Note(std::string note);

private:
	std::string note;

	void setWaveTable();

};
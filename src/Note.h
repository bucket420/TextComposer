#pragma once
#include "Signal.h"

class Note : public Signal
{
public:
	/* Set this->note to note */
	Note(std::string note);

private:
	/* The representation of a note, e.g. A4--, B5.., etc */
	std::string note;

	/* Set the wavetable */
	void setWavetable();

};
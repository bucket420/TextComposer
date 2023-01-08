#pragma once
#include "Note.h"

class Melody : public Signal
{
public:
	/* Set this->melody to melody */
	Melody(std::string melody);

private:
	/* The representation of a melody, e.g. C#5-E5-C#5-F#5---A5---G#5------. */
	std::string melody;

	/* Get indexes of note symbols in the melody string */
	std::vector<int> getNoteIndexes();

	/* Extract representations of individual notes from the melody string */
	std::vector<std::string> getNotes();

	/* Set the wavetable */
	void setWavetable();
};
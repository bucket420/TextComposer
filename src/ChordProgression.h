#pragma once
#include "Chord.h"

class ChordProgression : public Signal
{
public:
	/* Set all member variables */
	ChordProgression(std::string progression, std::string key, std::string scaleType);

private:
	/* The representation of a chord progression, e.g. I----VI----vi----V---- */
	std::string progression;

	/* Key signature */
	std::string key;

	/* Major or Minor */
	std::string scaleType;

	/* Frequencies of all possible notes in 2 octaves */
	std::array<double, 25> createTwoOctaveScale(std::string key);

	/* Get indexes of chord symbols in the progression string */
	std::vector<int> getChordIndexes();

	/* Extract representations of individual chords from the progression string */
	std::vector<std::string> getChords();

	/* Set the wavetable */
	void setWavetable();
};
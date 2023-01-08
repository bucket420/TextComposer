#pragma once
#include <array>
#include "Signal.h"

class Chord : public Signal
{
public:
	Chord(std::string chord, std::array<double, 25> scale, std::string scaleType);

private:
	/* The representation of a chord, e.g. I--, vi.., etc */
	std::string chord;

	/* Key signature */
	std::array<double, 25> scale;

	/* Major or Minor */
	std::string scaleType;

	/* Chord symbol without the duration syntax, e.g. I, IVd, iii, etc. */
	std::string getChordSymbol(std::string chord);

	/* Set the wavetable */
	void setWavetable();

	/* Turn all characters in the string to uppercase letters */
	std::string toUpper(std::string string);
};
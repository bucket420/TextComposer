#pragma once
#include <algorithm>
#include <stdexcept>
#include "Chord.h"

Chord::Chord(std::string chord, std::array<double, 25> scale, std::string scaleType)
{
	this->chord = chord;
	this->scale = scale;
	this->scaleType = scaleType;
	setWavetable();
}

std::string Chord::getChordSymbol(std::string chord)
{
	char lastChar = chord[chord.size() - 1];
	while (lastChar != 'V' && lastChar != 'I' && lastChar != 'v' && lastChar != 'i')
	{
		if (chord.size() == 0) return chord;
		chord = chord.substr(0, chord.size() - 1);
		lastChar = chord[chord.size() - 1];
	}
	return chord;
}

void Chord::setWavetable()
{
	double duration = getDuration(chord);
	std::string chordSymbol = getChordSymbol(chord);
	int step = 0;
	try 
	{
		if (scaleType == "major")
		{
			step = ROMAN_NUMBERS.at(toUpper(chordSymbol))[0];
		}
		else if (scaleType == "minor")
		{
			step = ROMAN_NUMBERS.at(toUpper(chordSymbol))[1];
		}
	}
	catch (const std::out_of_range)
	{
		return;
	}

	if (chord[chordSymbol.size()] == 'b') step -= 1;
	if (chord[chordSymbol.size()] == '#') step += 1;

	this->Signal::setWavetable(scale[step], duration);
	Signal secondNote;
	Signal thirdNote;

	if (chord[chordSymbol.size()] == 'd' || (chord.size() > chordSymbol.size() + 1 && chord[chordSymbol.size() + 1] == 'd'))
	{
		secondNote = Signal(scale[step + 3], duration);
		thirdNote = Signal(scale[step + 6], duration);
	}
	else if (chord[chordSymbol.size()] == 'a' || (chord.size() > chordSymbol.size() + 1 && chord[chordSymbol.size() + 1] == 'a'))
	{
		secondNote = Signal(scale[step + 4], duration);
		thirdNote = Signal(scale[step + 8], duration);
	}
	else if (isupper(chord[0]))
	{
		secondNote = Signal(scale[step + 4], duration);
		thirdNote = Signal(scale[step + 7], duration);
	}
	else if (islower(chord[0]))
	{
		secondNote = Signal(scale[step + 3], duration);
		thirdNote = Signal(scale[step + 7], duration);
	}
	this->add(secondNote);
	this->add(thirdNote);
	this->normalize();
}

std::string Chord::toUpper(std::string string)
{
	std::transform(string.begin(), string.end(), string.begin(), std::toupper);
	return string;
}
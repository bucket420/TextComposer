#include "Chord.h"
#include <algorithm>

Chord::Chord(std::string chord, std::array<double, 25> scale, std::string scaleType)
{
	this->chord = chord;
	this->scale = scale;
	this->scaleType = scaleType;
	setWaveTable();
}

std::string Chord::toUpper(std::string string)
{
	std::transform(string.begin(), string.end(), string.begin(), std::toupper);
	return string;
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

void Chord::setWaveTable()
{
	double duration = getDuration(chord);
	std::string chordSymbol = getChordSymbol(chord);
	const std::string* iterator = std::find(ROMAN_NUMBERS, ROMAN_NUMBERS + 7, toUpper(chordSymbol));
	if (iterator == std::end(ROMAN_NUMBERS) || duration == 0 || chordSymbol.empty()) return;
	int index = iterator - ROMAN_NUMBERS;
	int step;
	if (scaleType == "major") step = MAJOR_SCALE_STEPS[index];
	if (scaleType == "minor") step = MINOR_SCALE_STEPS[index];

	if (chord[chordSymbol.size()] == 'b') step -= 1;
	if (chord[chordSymbol.size()] == '#') step += 1;

	this->Signal::setWaveTable(scale[step], duration);

	if (chord[chordSymbol.size()] == 'd' || (chord.size() > chordSymbol.size() + 1 && chord[chordSymbol.size() + 1] == 'd'))
	{
		this->add(std::unique_ptr<Signal>(new Signal(scale[step + 3], duration)).get());
		this->add(std::unique_ptr<Signal>(new Signal(scale[step + 6], duration)).get());
	}
	else if (chord[chordSymbol.size()] == 'a' || (chord.size() > chordSymbol.size() + 1 && chord[chordSymbol.size() + 1] == 'a'))
	{
		this->add(std::unique_ptr<Signal>(new Signal(scale[step + 4], duration)).get());
		this->add(std::unique_ptr<Signal>(new Signal(scale[step + 8], duration)).get());
	}
	else if (isupper(chord[0]))
	{
		this->add(std::unique_ptr<Signal>(new Signal(scale[step + 4], duration)).get());
		this->add(std::unique_ptr<Signal>(new Signal(scale[step + 7], duration)).get());
	}
	else if (islower(chord[0]))
	{
		this->add(std::unique_ptr<Signal>(new Signal(scale[step + 3], duration)).get());
		this->add(std::unique_ptr<Signal>(new Signal(scale[step + 7], duration)).get());
	}
	this->normalize();
}
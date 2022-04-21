#include "Chord.h"
#include <algorithm>

Chord::Chord(std::string chord, std::array<double, 25> scale, std::string scaleType, std::string timeSignatureLower, std::string BPM)
{
	this->chord = chord;
	setWaveTable(scale, scaleType, timeSignatureLower, BPM);
}

double Chord::getDuration(std::string note, std::string timeSignatureLower, std::string BPM)
{
	int eighthCount = std::count(note.begin(), note.end(), '-');
	int sixtyfourthCount = std::count(note.begin(), note.end(), '.');
	if (eighthCount == 0 && sixtyfourthCount == 0) return 0.0;
	return std::stod(timeSignatureLower) * 60.0 / std::stod(BPM) * ((double)sixtyfourthCount * 1.0 / 64.0 + (double)eighthCount * 0.125);
}

std::string Chord::toUpper(std::string string)
{
	std::transform(string.begin(), string.end(), string.begin(), std::toupper);
	return string;
}

std::string Chord::getRomanNumber(std::string chord)
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


void Chord::setWaveTable(std::array<double, 25> scale, std::string scaleType, std::string timeSignatureLower, std::string BPM)
{
	double duration = getDuration(chord, timeSignatureLower, BPM);
	std::string romanNumber = getRomanNumber(chord);
	const std::string* iterator = std::find(Wave::ROMAN_NUMBERS, Wave::ROMAN_NUMBERS + 7, toUpper(romanNumber));
	if (iterator == std::end(Wave::ROMAN_NUMBERS) || duration == 0 || romanNumber.empty()) return;
	int index = iterator - Wave::ROMAN_NUMBERS;
	int step;
	if (scaleType == "major") step = Wave::MAJOR_SCALE_STEPS[index];
	if (scaleType == "minor") step = Wave::MINOR_SCALE_STEPS[index];

	if (chord[romanNumber.size()] == 'b') step -= 1;
	if (chord[romanNumber.size()] == '#') step += 1;

	Wave wave(scale[step], duration);
	//Wave secondNote;
	//Wave thirdNote;
	if (chord[romanNumber.size()] == 'd' || (chord.size() > romanNumber.size() + 1 && chord[romanNumber.size() + 1] == 'd'))
	{
	/*	(&secondNote)->setWaveTable(scale[step + 3], duration);
		(&thirdNote)->setWaveTable(scale[step + 6], duration);*/
		(&wave)->add(Wave::Wave(scale[step + 3], duration));
		(&wave)->add(Wave::Wave(scale[step + 6], duration));
	}
	else if (chord[romanNumber.size()] == 'a' || (chord.size() > romanNumber.size() + 1 && chord[romanNumber.size() + 1] == 'a'))
	{
		//(&secondNote)->setWaveTable(scale[step + 4], duration);
		//(&thirdNote)->setWaveTable(scale[step + 8], duration);
		(&wave)->add(Wave::Wave(scale[step + 4], duration));
		(&wave)->add(Wave::Wave(scale[step + 8], duration));
	}
	else if (isupper(chord[0]))
	{
		//(&secondNote)->setWaveTable(scale[step + 4], duration);
		//(&thirdNote)->setWaveTable(scale[step + 7], duration);
		(&wave)->add(Wave::Wave(scale[step + 4], duration));
		(&wave)->add(Wave::Wave(scale[step + 7], duration));
	}
	else if (islower(chord[0]))
	{
		//(&secondNote)->setWaveTable(scale[step + 3], duration);
		//(&thirdNote)->setWaveTable(scale[step + 7], duration);
		(&wave)->add(Wave::Wave(scale[step + 3], duration));
		(&wave)->add(Wave::Wave(scale[step + 7], duration));
	}
	(&wave)->normalize();
	this->waveTable = (&wave)->getWaveTable();
}
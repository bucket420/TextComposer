#pragma once
#include "Input.h"
#include "Wave.h"
#include <algorithm>


using namespace Input;

std::vector<int> Input::getNoteIndexes(std::string input)
{
	std::vector<int> noteIndexes;
	for (int i = 0; i < (&input)->length(); i++)
	{
		if (isalpha(input[i]) && isupper(input[i]))
		{
			noteIndexes.push_back(i);
		}
	}
	return noteIndexes;
}

std::vector<std::string> Input::getNotes(std::string input)
{
	std::vector<int> noteIndexes = getNoteIndexes(input);
	std::vector<std::string> notes(noteIndexes.size(), "");
	if (noteIndexes.empty()) return notes;
	for (int i = 0; i < noteIndexes.size(); i++)
	{
		if (i == noteIndexes.size() - 1) 
		{
			notes[i] = input.substr(noteIndexes[i]);
			return notes;
		}
		notes[i] = input.substr(noteIndexes[i], (long long)noteIndexes[i + 1] - noteIndexes[i]);
	}
}	

double Input::getDuration(std::string note, std::string timeSignatureLower, std::string BPM) 
{
	int eighthCount = std::count(note.begin(), note.end(), '-');
	int sixtyfourthCount = std::count(note.begin(), note.end(), '.');
	if (eighthCount == 0 && sixtyfourthCount == 0) return 0.0;
	return std::stod(timeSignatureLower) * 60.0 / std::stod(BPM) * ((double) sixtyfourthCount * 1.0 / 64.0 + (double) eighthCount * 0.125);
}

double Input::getNoteFreq(std::string name)
{
	char letter = name[0];
	int octaveNumber = name[name.length() - 1] - '0';
	const char* iterator = std::find(Wave::OCTAVE, Wave::OCTAVE + 7, letter);
	int index = iterator - Wave::OCTAVE;
	double freq = 0;
	if (name.length() == 2)
	{
		freq = Wave::FIRST_OCTAVE_FREQ[index] * pow(2.0, (double)octaveNumber);
	}
	if (name[1] == '#')
	{
		freq = Wave::FIRST_OCTAVE_FREQ[index] * pow(2.0, (double)octaveNumber + 1.0/12.0);
	}
	if (name[1] == 'b')
	{
		freq = Wave::FIRST_OCTAVE_FREQ[index] * pow(2.0, (double)octaveNumber - 1.0/12.0);
	}
	return freq;
}

std::vector<double> Input::inputToWavetableFirstMode(std::string input, std::string timeSignatureLower, std::string BPM)
{
	std::vector<std::string> noteList = getNotes(input);
	if (noteList.empty()) return {};
	std::vector<std::vector<double>> waveTables = {};
	std::string name;
	double duration;
	for (int i = 0; i < noteList.size(); i++)
	{
		duration = getDuration(noteList[i], timeSignatureLower, BPM);
		if (duration == 0) return {};
		if (noteList[i][1] == '#' || noteList[i][1] == 'b')
		{
			name = noteList[i].substr(0, 3);
		} 
		else
		{
			name = noteList[i].substr(0, 2);
		}
		waveTables.push_back(Wave::createWave(getNoteFreq(name), duration));
	}
	return Wave::appendWaves(&waveTables);
}

std::array<double, 25> Input::createTwoOctaveScale(std::string key) 
{
	if (std::find(Wave::OCTAVE, Wave::OCTAVE + 7, key[0]) == std::end(Wave::OCTAVE)) return {};
	std::array<double, 25> twoOctaveScale;
	double firstNote = getNoteFreq(key + '4') * pow(2.0, -1.0 / 12.0);
	if (key.size() > 2 || ((key.size() == 2) && key[1] != '#' && key[1] != 'b') || key.size() == 0) return {};
	if (key[1] == '#')
	{
		firstNote *= pow(2.0, 1.0 / 12.0);
	}
	if (key[1] == 'b')
	{
		firstNote *= pow(2.0, -1.0 / 12.0);
	}
	for (int i = 0; i < 25; i++)
	{
		twoOctaveScale[i] = firstNote * pow(2.0, (double)i / 12.0);
	}
	return twoOctaveScale;
}

std::vector<int> Input::getChordIndexes(std::string input)
{
	std::vector<int> chordIndexes;
	for (int i = 0; i < (&input)->length(); i++)
	{
		if (isalpha(input[i]))
		{
			if (i > 0 && isalpha(input[i - 1]))
			{
				continue;
			}
			chordIndexes.push_back(i);
		}
	}
	return chordIndexes;
}


std::vector<std::string> Input::getChords(std::string input)
{
	std::vector<int> chordIndexes = getChordIndexes(input);
	std::vector<std::string> chords(chordIndexes.size(), "");
	if (chordIndexes.empty()) return chords;
	for (int i = 0; i < chordIndexes.size(); i++)
	{
		if (i == chordIndexes.size() - 1)
		{
			chords[i] = input.substr(chordIndexes[i]);
			return chords;
		}
		chords[i] = input.substr(chordIndexes[i], (long long)chordIndexes[i + 1] - chordIndexes[i]);
	}
}

std::string Input::toUpper(std::string string)
{
	std::transform(string.begin(), string.end(), string.begin(), std::toupper);
	return string;
}

std::string Input::getRomanNumber(std::string chord)
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

std::vector<double> Input::chordToWavetable(std::string chord, std::array<double, 25> scale, std::string scaleType, std::string timeSignatureLower, std::string BPM)
{
	std::vector<std::vector<double>> waveTables = {};
	double duration = getDuration(chord, timeSignatureLower, BPM);
	std::string romanNumber = getRomanNumber(chord);
	const std::string* iterator = std::find(Wave::ROMAN_NUMBERS, Wave::ROMAN_NUMBERS + 7, toUpper(romanNumber));
	if (iterator == std::end(Wave::ROMAN_NUMBERS) || duration == 0 || romanNumber.empty()) return {};
	int index = iterator - Wave::ROMAN_NUMBERS;
	int step;
	if (scaleType == "major") step = Wave::MAJOR_SCALE_STEPS[index];
	if (scaleType == "minor") step = Wave::MINOR_SCALE_STEPS[index];

	if (chord[romanNumber.size()] == 'b') step -= 1;
	if (chord[romanNumber.size()] == '#') step += 1;

	waveTables.push_back(Wave::createWave(scale[step], duration));
	if (chord[romanNumber.size()] == 'd' || (chord.size() > romanNumber.size() + 1 && chord[romanNumber.size() + 1] == 'd'))
	{
		waveTables.push_back(Wave::createWave(scale[step + 3], duration));
		waveTables.push_back(Wave::createWave(scale[step + 6], duration));
	}
	else if (chord[romanNumber.size()] == 'a' || (chord.size() > romanNumber.size() + 1 && chord[romanNumber.size() + 1] == 'a'))
	{
		waveTables.push_back(Wave::createWave(scale[step + 4], duration));
		waveTables.push_back(Wave::createWave(scale[step + 8], duration));
	}
	else if (isupper(chord[0]))
	{
		waveTables.push_back(Wave::createWave(scale[step + 4], duration));
		waveTables.push_back(Wave::createWave(scale[step + 7], duration));
	}
	else if (islower(chord[0]))
	{
		waveTables.push_back(Wave::createWave(scale[step + 3], duration));
		waveTables.push_back(Wave::createWave(scale[step + 7], duration));
	}

	return Wave::addWaves(&waveTables);
}

std::vector<double> Input::inputToWavetableSecondMode(std::string input, std::string key, std::string scaleType, std::string timeSignatureLower, std::string BPM)
{
	std::vector<std::string> chordList = getChords(input);
	std::array<double, 25> scale = createTwoOctaveScale(key);
	if (chordList.empty() || scale.empty()) return {};
	std::vector<std::vector<double>> waveTables = {};
	for (int i = 0; i < chordList.size(); i++)
	{
		waveTables.push_back(chordToWavetable(chordList[i], scale, scaleType, timeSignatureLower, BPM));
	}
	return Wave::appendWaves(&waveTables);
}


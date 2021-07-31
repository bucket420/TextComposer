#pragma once
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include <iostream>
#include "Constants.h"
#include "Input.h"
#include "Wave.h"

Input::Input(std::string input) 
{
	this->wave = inputToWavetableFirstMode(input);
}

Input::Input(std::string input, std::string key, std::string scaleType)
{
	this->wave = inputToWavetableSecondMode(input, key, scaleType);
}

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

double Input::getDuration(std::string note) 
{
	int eighthCount = std::count(note.begin(), note.end(), '-');
	int sixtyfourthCount = std::count(note.begin(), note.end(), '.');
	return 2.0 * ((double) sixtyfourthCount * 1.0 / 64.0 + (double) eighthCount * 0.125);
}

double Input::getNoteFreq(std::string name)
{
	char letter = name[0];
	int octaveNumber = name[name.length() - 1] - '0';
	const char* iterator = std::find(OCTAVE, OCTAVE + 7, letter);
	int index = iterator - OCTAVE;
	double freq = 0;
	if (name.length() == 2)
	{
		freq = FIRST_OCTAVE_FREQ[index] * pow(2.0, (double)octaveNumber);
	}
	if (name[1] == '#')
	{
		freq = FIRST_OCTAVE_FREQ[index] * pow(2.0, (double)octaveNumber + 1.0/12.0);
	}
	if (name[1] == 'b')
	{
		freq = FIRST_OCTAVE_FREQ[index] * pow(2.0, (double)octaveNumber - 1.0/12.0);
	}
	return freq;
}

Wave Input::inputToWavetableFirstMode(std::string input)
{
	std::vector<std::string> noteList = getNotes(input);
	std::vector<double> waveTable = {};
	Wave wave(waveTable);
	std::string name;
	double duration;
	for (int i = 0; i < noteList.size(); i++)
	{
		duration = getDuration(noteList[i]);
		if (noteList[i][1] == '#' || noteList[i][1] == 'b')
		{
			name = noteList[i].substr(0, 3);
		} 
		else
		{
			name = noteList[i].substr(0, 2);
		}
		wave.appendWaves(Wave::createSine(getNoteFreq(name), duration));
	}
	std::cout << wave.waveTable.size() << std::endl;
	return wave;
}

std::array<double, 25> Input::createTwoOctaveScale(std::string key) 
{
	std::array<double, 25> twoOctaveScale;
	double firstNote = getNoteFreq(key + '4') * pow(2.0, -1.0 / 12.0);
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
	std::vector<int> noteIndexes = getChordIndexes(input);
	std::vector<std::string> notes(noteIndexes.size(), "");

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
		chord = chord.substr(0, chord.size() - 1);
		lastChar = chord[chord.size() - 1];
	}
	return chord;
}

std::vector<double> Input::chordToWavetable(std::string chord, std::array<double, 25> scale, std::string scaleType)
{
	std::vector<double> waveTable = {};
	Wave wave(waveTable);
	double duration = getDuration(chord);
	std::string romanNumber = getRomanNumber(chord);
	const std::string* iterator = std::find(ROMAN_NUMBERS, ROMAN_NUMBERS + 7, toUpper(romanNumber));
	int index = iterator - ROMAN_NUMBERS;
	int step;
	if (scaleType == "major") step = MAJOR_SCALE_STEPS[index];
	if (scaleType == "minor") step = MINOR_SCALE_STEPS[index];

	if (chord[romanNumber.size()] == 'b') step -= 1;
	if (chord[romanNumber.size()] == '#') step += 1;

	wave.appendWaves(Wave::createSine(scale[step], duration));
	if (chord[romanNumber.size()] == 'd' || (chord.size() > romanNumber.size() + 1 && chord[romanNumber.size() + 1] == 'd'))
	{
		wave.addWaves(Wave::createSine(scale[step + 3], duration));
		wave.addWaves(Wave::createSine(scale[step + 6], duration));
	}
	else if (chord[romanNumber.size()] == 'a' || (chord.size() > romanNumber.size() + 1 && chord[romanNumber.size() + 1] == 'a'))
	{
		wave.addWaves(Wave::createSine(scale[step + 4], duration));
		wave.addWaves(Wave::createSine(scale[step + 8], duration));
	}
	else if (isupper(chord[0]))
	{
		wave.addWaves(Wave::createSine(scale[step + 4], duration));
		wave.addWaves(Wave::createSine(scale[step + 7], duration));
		std::cout << scale[step] << ' ' << scale[step + 4] << ' ' << scale[step + 7] << std::endl;
	}
	else if (islower(chord[0]))
	{
		wave.addWaves(Wave::createSine(scale[step + 3], duration));
		wave.addWaves(Wave::createSine(scale[step + 7], duration));
		std::cout << scale[step] << ' ' << scale[step + 3] << ' ' << scale[step + 7] << std::endl;
	}
	for (int i = 0; i < wave.waveTable.size(); i++)
	{
		wave.waveTable[i] /= 3.0;
	}
	return wave.waveTable;
}

Wave Input::inputToWavetableSecondMode(std::string input, std::string key, std::string scaleType)
{
	std::vector<std::string> chordList = getChords(input);
	std::array<double, 25> scale = createTwoOctaveScale(key);
	std::vector<double> waveTable = {};
	Wave wave(waveTable);
	double duration;
	for (int i = 0; i < chordList.size(); i++)
	{
		wave.appendWaves(chordToWavetable(chordList[i], scale, scaleType));
	}
	return wave;
}


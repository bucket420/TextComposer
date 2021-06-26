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
	this->wave = inputToWavetable(input);
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
	std::cout << "Got note indexes successfully" << std::endl;
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
			std::cout << "Got notes successfully" << std::endl;
			return notes;
		}
		notes[i] = input.substr(noteIndexes[i], (long long)noteIndexes[i + 1] - noteIndexes[i]);
	}
}	

double Input::getNoteDuration(std::string note) 
{
	int halfCount = std::count(note.begin(), note.end(), '-');
	int eighthCount = std::count(note.begin(), note.end(), '.');
	return halfCount * 0.5 + eighthCount * 0.125;
}

double Input::getNoteFreq(std::string name)
{
	char letter = name[0];
	int octaveNumber = name[name.length() - 1] - '0';
	const char* iterator = std::find(FIRST_OCTAVE, FIRST_OCTAVE + 7, letter);
	int index = iterator - FIRST_OCTAVE;
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

Wave Input::inputToWavetable(std::string input)
{
	std::vector<std::string> noteList = getNotes(input);
	std::vector<double> waveTable = {};
	Wave wave(waveTable);
	std::string name;
	double duration;
	for (int i = 0; i < noteList.size(); i++)
	{
		duration = getNoteDuration(noteList[i]);
		if (noteList[i][1] == '#' || noteList[i][1] == 'b')
		{
			name = noteList[i].substr(0, 3);
		} 
		else
		{
			name = noteList[i].substr(0, 2);
		}
		std::cout << "Name: " << name << std::endl;
		std::cout << "Duration: " << duration << std::endl;
		std::cout << "Frequency: " << getNoteFreq(name) << std::endl;
		wave.appendWaves(Wave::createSine(getNoteFreq(name), duration));
	}
	std::cout << wave.waveTable.size() << std::endl;
	return wave;
}
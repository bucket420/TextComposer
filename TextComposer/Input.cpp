#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include "Constants.h"
#include "Input.h"
#include "Wave.h"

Input::Input(std::string* input) 
{
	this->input = input;
}

std::vector<int> Input::getNoteIndexes(std::string* input)
{
	std::vector<int> noteIndexes;
	for (int i = 0; i < input->length(); i++)
	{
		if (isalpha((*input)[i]) && isupper((*input)[i]))
		{
			noteIndexes.push_back(i);
		}
	}
	return noteIndexes;
}

std::vector<std::string> Input::getNotes(std::string* input)
{
	std::vector<int> noteIndexes = getNoteIndexes(input);
	std::vector<std::string> notes(noteIndexes.size(), "");

	for (int i = 0; i < noteIndexes.size(); i++)
	{
		if (i == noteIndexes.size() - 1) 
		{
			notes[i] = (*input).substr(noteIndexes[i]);
			return notes;
		}
		notes[i] = (*input).substr(noteIndexes[i], (long long)noteIndexes[i + 1] - noteIndexes[i]);
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
	double freq = FIRST_OCTAVE_FREQ[index] * pow(2, octaveNumber);
	if (name.length() == 2) return freq;
	if (name[1] == '#') return freq * pow(2, 1 / 12);
	if (name[1] == 'b') return freq * pow(2, -1 / 12);
}

std::vector<double>* Input::inputToWavetable(std::string* input)
{
	std::vector<std::string> noteList = getNotes(input);
	Wave* wave;
	for (int i = 0; i < noteList.size(); i++)
	{
		std::string name;
		double duration = getNoteDuration(noteList[i]);
		if (noteList[i][1] == '#' || noteList[i][1] == 'b')
		{
			name = noteList[i].substr(0, 3);
		} 
		else
		{
			name = noteList[i].substr(0, 2);
		}
		wave->appendWaves(Wave::createSine(getNoteFreq(name), duration));
	}
	return wave->waveTable;
}
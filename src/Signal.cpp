#pragma once
#include <algorithm>
#include <math.h>
#include <memory>
#include <stdexcept>
#include <vector>
#include "Signal.h"

#define M_PI  (3.14159265)

double Signal::BPM = 120.0;
double Signal::timeSignatureLower = 4.0;

const std::vector<double> Signal::LUT = createGuitarLUT(2048);
const std::unordered_map<char, double> Signal::FIRST_OCTAVE_FREQ = {
	{'C', 16.35},
	{'D', 18.35},
	{'E', 20.60},
	{'F', 21.83},
	{'G', 24.50},
	{'A', 27.50},
	{'B', 30.87}
};
const std::unordered_map<std::string, std::array<int, 2>> Signal::ROMAN_NUMBERS = {
	{"I", {1, 1}},
	{"II", {3, 3}},
	{"III", {5, 4}},
	{"IV", {6, 6}},
	{"V", {8, 8}},
	{"VI", {10, 9}},
	{"VII", {12, 11}}
};

Signal::Signal()
{
	*waveTable = {};
}

Signal::Signal(double freq, double duration)
{
	setWavetable(freq, duration);
}

void Signal::add(Signal& signal)
{
	if (signal.isEmpty())
	{
		return;
	}
	if (this->waveTable->size() < signal.waveTable->size()) this->waveTable->resize(signal.waveTable->size(), 0.0);
	for (int i = 0; i < this->waveTable->size(); i++)
	{
		(*this->waveTable)[i] += (*signal.waveTable)[i];
	}
}

void Signal::append(Signal& signal)
{
	if (signal.isEmpty())
	{
		return;
	}
	for (int i = 0; i < signal.waveTable->size(); i++)
	{
		this->waveTable->push_back((*signal.waveTable)[i]);
	}
}

std::vector<double> Signal::createGuitarLUT(int size)
{
	std::vector<double> guitarLUT;
	guitarLUT.assign(size, 0.0);
	for (int i = 0; i < size; i++)
	{
		guitarLUT[i] = 0.065 * (double)sin((double)i * M_PI * 2.0 / (double)size)
			+ 0.031 * (double)sin((double)i * M_PI * 4.0 / (double)size)
			+ 0.0175 * (double)sin((double)i * M_PI * 6.0 / (double)size)
			+ 0.006 * (double)sin((double)i * M_PI * 8.0 / (double)size)
			+ 0.00084 * (double)sin((double)i * M_PI * 12.0 / (double)size)
			+ 0.003 * (double)sin((double)i * M_PI * 14.0 / (double)size)
			+ 0.00076 * (double)sin((double)i * M_PI * 16.0 / (double)size);
	}
	double max = *max_element(guitarLUT.begin(), guitarLUT.end());
	for (int i = 0; i < size; i++)
	{
		guitarLUT[i] /= max;
	}
	return guitarLUT;
}

std::vector<double> Signal::createSineLUT(int size)
{
	std::vector<double> sineLUT;
	sineLUT.assign(size, 0.0);
	for (int i = 0; i < size; i++)
	{
		sineLUT[i] = (double)sin((double)i * M_PI * 2.0 / (double)size);
	}
	return sineLUT;
}

double Signal::get()
{
	return (*waveTable)[phase];
}

double Signal::getDuration()
{
	return (double)waveTable->size() / (double)SAMPLE_RATE;
}

double Signal::getDuration(std::string input)
{
	int eighthCount = std::count(input.begin(), input.end(), '-');
	int sixtyfourthCount = std::count(input.begin(), input.end(), '.');
	if (eighthCount == 0 && sixtyfourthCount == 0) return 0.0;
	return timeSignatureLower * 60.0 / BPM * ((double)sixtyfourthCount * 1.0 / 64.0 + (double)eighthCount * 0.125);
}

double Signal::getNoteFreq(std::string name)
{
	char letter = name[0];
	int octaveNumber = name[name.length() - 1] - '0';
	int first_freq;
	try
	{
		first_freq = FIRST_OCTAVE_FREQ.at(letter);
	}
	catch (const std::exception&)
	{
		return 0.0;
	}
	double freq = 0;
	if (name.length() == 2)
	{
		freq = first_freq * pow(2.0, (double)octaveNumber);
	}
	else if (name[1] == '#')
	{
		freq = first_freq * pow(2.0, (double)octaveNumber + 1.0 / 12.0);
	}
	else if (name[1] == 'b')
	{
		freq = first_freq * pow(2.0, (double)octaveNumber - 1.0 / 12.0);
	}
	return freq;
}

double Signal::getPhase()
{
	return phase;
}

std::vector<double> Signal::getWavetable()
{
	return *waveTable;
}

void Signal::incrementPhase()
{
	phase++;
}

bool Signal::isEmpty()
{
	return waveTable->empty();
}

void Signal::normalize()
{
	if (isEmpty())
	{
		return;
	}
	double max = *(std::max_element(waveTable->begin(), waveTable->end()));
	for (int i = 0; i < waveTable->size(); i++)
	{
		(*waveTable)[i] /= max;
	}
}

void Signal::setTimeSignatureLowerAndBPM(std::string timeSignatureLower, std::string BPM)
{
	Signal::timeSignatureLower = std::stod(timeSignatureLower);
	Signal::BPM = std::stod(BPM);
}

void Signal::setWavetable(double freq, double duration)
{
	if (freq == 0) return;
	double phase = 0.0;
	int tableSize = duration * SAMPLE_RATE;
	double increment = LUT.size() * freq / (double)SAMPLE_RATE;
	*waveTable = std::vector<double>(tableSize, 0.0);
	for (int i = 0; i < tableSize; i++)
	{
		(*waveTable)[i] = LUT[(int)phase] * pow(2.71828182845904523536, -(double)i * 2 / 44100.0);
		phase += increment;
		if (phase >= LUT.size()) phase -= (double) LUT.size();
	}
}
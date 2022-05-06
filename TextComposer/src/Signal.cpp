#pragma once
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include "Signal.h"

#define M_PI  (3.14159265)

const double Signal::FIRST_OCTAVE_FREQ[7] = { 16.35, 18.35, 20.60, 21.83, 24.50, 27.50, 30.87 };
const char Signal::OCTAVE[7] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };
const std::string Signal::ROMAN_NUMBERS[7] = { "I", "II", "III", "IV", "V", "VI", "VII" };
const int Signal::MAJOR_SCALE_STEPS[7] = { 1, 3, 5, 6, 8, 10, 12 };
const int Signal::MINOR_SCALE_STEPS[7] = { 1, 3, 4, 6, 8, 9, 11 };
const std::vector<double> Signal::LUT = createGuitarLUT(2048);
double Signal::timeSignatureLower = 4.0;
double Signal::BPM = 120.0;

Signal::Signal()
{
	*waveTable = {};
}

Signal::Signal(double freq, double duration)
{
	*waveTable = createWaveTable(freq, duration);
}

double Signal::get(int index)
{
	return (*waveTable)[index];
}

std::vector<double> Signal::getWaveTable()
{
	return *waveTable;
}

double Signal::getDuration()
{
	return (double)waveTable->size() / (double)SAMPLE_RATE;
}

void Signal::setWaveTable(double freq, double duration)
{
	*waveTable = createWaveTable(freq, duration);
}

std::vector<double> Signal::createWaveTable(double freq, double duration)
{
	if (freq == 0) return {};
	double phase = 0.0;
	int tableSize = duration * SAMPLE_RATE;
	std::vector<double> table(tableSize, 0.0);
	double increment = (&LUT)->size() * freq / (double)SAMPLE_RATE;
	for (int i = 0; i < tableSize; i++)
	{
		table[i] = LUT[(int)phase] * pow(2.71828182845904523536, -(double)i * 2 / 44100.0);
		phase += increment;
		if (phase >= (&LUT)->size()) phase -= (double)((&LUT)->size());
	}
	return table;
}

void Signal::append(std::unique_ptr<Signal> signal)
{
	if (signal->isEmpty())
	{
		return;
	}
	for (int i = 0; i < signal->waveTable->size(); i++)
	{
		this->waveTable->push_back((*signal->waveTable)[i]);
	}
}

void Signal::add(std::unique_ptr<Signal> signal)
{
	if (signal->isEmpty())
	{
		return;
	}
	if (this->waveTable->size() < signal->waveTable->size()) this->waveTable->resize(signal->waveTable->size(), 0.0);
	for (int i = 0; i < this->waveTable->size(); i++)
	{
		(*this->waveTable)[i] += (*signal->waveTable)[i];
	}
}

std::vector<double> Signal::createSineLUT(int size)
{
	std::vector<double> sineLUT;
	(&sineLUT)->assign(size, 0.0);
	for (int i = 0; i < size; i++)
	{
		sineLUT[i] = (double)sin((double)i * M_PI * 2.0 / (double)size);
	}
	return sineLUT;
}

std::vector<double> Signal::createGuitarLUT(int size)
{
	std::vector<double> guitarLUT;
	(&guitarLUT)->assign(size, 0.0);
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
	double max = *max_element((&guitarLUT)->begin(), (&guitarLUT)->end());
	for (int i = 0; i < size; i++)
	{
		guitarLUT[i] /= max;
	}
	return guitarLUT;
}

double Signal::getNoteFreq(std::string name)
{
	char letter = name[0];
	int octaveNumber = name[name.length() - 1] - '0';
	const char* iterator = std::find(Signal::OCTAVE, Signal::OCTAVE + 7, letter);
	int index = iterator - Signal::OCTAVE;
	double freq = 0;
	if (name.length() == 2)
	{
		freq = Signal::FIRST_OCTAVE_FREQ[index] * pow(2.0, (double)octaveNumber);
	}
	if (name[1] == '#')
	{
		freq = Signal::FIRST_OCTAVE_FREQ[index] * pow(2.0, (double)octaveNumber + 1.0 / 12.0);
	}
	if (name[1] == 'b')
	{
		freq = Signal::FIRST_OCTAVE_FREQ[index] * pow(2.0, (double)octaveNumber - 1.0 / 12.0);
	}
	return freq;
}

double Signal::getDuration(std::string input)
{
	int eighthCount = std::count(input.begin(), input.end(), '-');
	int sixtyfourthCount = std::count(input.begin(), input.end(), '.');
	if (eighthCount == 0 && sixtyfourthCount == 0) return 0.0;
	return timeSignatureLower * 60.0 / BPM * ((double)sixtyfourthCount * 1.0 / 64.0 + (double)eighthCount * 0.125);
}

void Signal::setTimeSignatureLowerAndBPM(std::string timeSignatureLower, std::string BPM)
{
	Signal::timeSignatureLower = std::stod(timeSignatureLower);
	Signal::BPM = std::stod(BPM);
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
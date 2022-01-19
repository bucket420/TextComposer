#pragma once
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Wave.h"

#define M_PI  (3.14159265)

const double Wave::FIRST_OCTAVE_FREQ[7] = { 16.35, 18.35, 20.60, 21.83, 24.50, 27.50, 30.87 };
const char Wave::OCTAVE[7] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };
const std::string Wave::ROMAN_NUMBERS[7] = { "I", "II", "III", "IV", "V", "VI", "VII" };
const int Wave::MAJOR_SCALE_STEPS[7] = { 1, 3, 5, 6, 8, 10, 12 };
const int Wave::MINOR_SCALE_STEPS[7] = { 1, 3, 4, 6, 8, 9, 11 };
const std::vector<double> Wave::LUT = createGuitarLUT(2048);

Wave::Wave()
{
	waveTable = {};
}

Wave::Wave(double freq, double duration)
{
	waveTable = createWaveTable(freq, duration);
}

Wave::Wave(std::vector<double>* waveTable)
{
	(this->waveTable) = *waveTable;
}

std::vector<double>* Wave::getWaveTable()
{
	return &waveTable;
}

double Wave::getDuration()
{
	return (double)(&waveTable)->size() / (double)SAMPLE_RATE;
}

void Wave::setWaveTable(double freq, double duration)
{
	waveTable = createWaveTable(freq, duration);
}

void Wave::setWaveTable(std::vector<double> waveTable)
{
	this->waveTable = waveTable;
}

std::vector<double> Wave::createWaveTable(double freq, double duration)
{
	if (freq == 0) return {};
	double phase = 0.0;
	int tableSize = duration * SAMPLE_RATE;
	std::vector<double> wave(tableSize, 0.0);
	double increment = (&LUT)->size() * freq / (double)SAMPLE_RATE;
	for (int i = 0; i < tableSize; i++)
	{
		wave[i] = LUT[(int)phase] * pow(2.71828182845904523536, -(double)i * 2 / 44100.0);
		phase += increment;
		if (phase >= (&LUT)->size()) phase -= (double)((&LUT)->size());
	}
	return wave;
}

void Wave::append(Wave* wave)
{
	if (!wave)
	{
		return;
	}
	for (int i = 0; i < (&wave->waveTable)->size(); i++)
	{
		(&this->waveTable)->push_back((wave->waveTable)[i]);
	}
}

void Wave::add(Wave* wave)
{
	if (!wave)
	{
		return;
	}
	if ((&this->waveTable)->size() < (&wave->waveTable)->size()) (&this->waveTable)->resize(wave->waveTable.size(), 0.0);
	for (int i = 0; i < this->waveTable.size(); i++)
	{
		(this->waveTable)[i] += (wave->waveTable)[i];
	}
}

std::vector<double> Wave::appendWaveTables(std::vector<std::vector<double>>* tables)
{
	if (!tables)
	{
		return {};
	}
	std::vector<double> waveTable{};
	for (std::vector<double> table : *tables)
	{
		for (int i = 0; i < table.size(); i++)
		{
			(&waveTable)->push_back(table[i]);
		}
	}
	return waveTable;
}

std::vector<double> Wave::addWaveTables(std::vector<std::vector<double>>* tables)
{
	if (!tables)
	{
		return {};
	}
	std::vector<double> waveTable{};
	for (int i = 0; i < tables->size(); i++)
	{
		if ((&waveTable)->size() < (*tables)[i].size()) (&waveTable)->resize((*tables)[i].size(), 0.0);
		for (int j = 0; j < (&waveTable)->size(); j++)
		{
			waveTable[j] += (*tables)[i][j];
			if (i == tables->size() - 1) waveTable[j] /= (double)(tables->size());
		}
	}
	return waveTable;
}

std::vector<double> Wave::createSineLUT(int size)
{
	std::vector<double> sineLUT;
	(&sineLUT)->assign(size, 0.0);
	for (int i = 0; i < size; i++)
	{
		sineLUT[i] = (double)sin((double)i * M_PI * 2.0 / (double)size);
	}
	return sineLUT;
}

std::vector<double> Wave::createGuitarLUT(int size)
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

void Wave::normalize()
{
	double max = *(std::max_element(waveTable.begin(), waveTable.end()));
	for (int i = 0; i < waveTable.size(); i++)
	{
		waveTable[i] /= max;
	}
}
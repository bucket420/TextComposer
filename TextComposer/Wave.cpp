#pragma once
#include <math.h>
#include <algorithm>
#include "Wave.h"

#define M_PI  (3.14159265)

std::vector<double> Wave::createWave(double freq, double duration)
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

std::vector<double> Wave::appendWaves(std::vector<std::vector<double>>* tables)
{
	//waveTable->insert(this->waveTable->end(), table2.begin(), table2.end());
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

std::vector<double> Wave::addWaves(std::vector<std::vector<double>> *tables)
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
	sineLUT.assign(size, 0.0);
	for (int i = 0; i < size; i++)
	{
		sineLUT[i] = (double)sin((double)i * M_PI * 2.0 / (double)size);
	}
	return sineLUT;
}

std::vector<double> Wave::createGuitarLUT(int size)
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

std::vector<double> Wave::LUT = createGuitarLUT(2048);
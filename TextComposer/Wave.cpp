#pragma once
#include <math.h>
#include <vector>
#include <iostream>
#include "Wave.h"
#include "Constants.h"

using namespace Wave;

std::vector<double> Wave::createWave(double freq, double duration)
{
	double phase = 0.0;
	int tableSize = duration * SAMPLE_RATE;
	std::vector<double> wave(tableSize, 0.0);
	double increment = (&LUT)->size() * freq / (double)SAMPLE_RATE;
	for (int i = 0; i < tableSize; i++)
	{
		wave[i] = LUT[(int)phase];
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

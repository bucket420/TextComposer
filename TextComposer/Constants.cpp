#pragma once
#include <vector>
#include <algorithm>
#include "Constants.h"

#define M_PI  (3.14159265)

std::vector<double> createSineLUT(int size)
{
	std::vector<double> sineLUT;
	sineLUT.assign(size, 0.0);
	for (int i = 0; i < size; i++)
	{
		sineLUT[i] = (double)sin((double)i * M_PI * 2.0 / (double)size);
	}
	return sineLUT;
}

std::vector<double> createGuitarLUT(int size)
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

std::vector<double> LUT = createGuitarLUT(2048);
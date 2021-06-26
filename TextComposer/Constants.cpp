#pragma once
#include <vector>
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

std::vector<double> LUT = createSineLUT(2048);
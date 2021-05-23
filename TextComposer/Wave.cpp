#include <math.h>
#include <vector>
#include "Wave.h"

#define M_PI  (3.14159265)

Wave::Wave()
{
	waveTable->assign(0, 0.0);
}

std::vector<double>* Wave::createSineLUT(int size)
{
	std::vector<double>* sineLUT;
	sineLUT->assign(size, 0.0);
	for (int i = 0; i < size; i++)
	{
		(*sineLUT)[i] = (float)sin((double)i * M_PI * 2.0 / (double)size);
	}
	return sineLUT;
}

const std::vector<double>* Wave::LUT = Wave::createSineLUT(2048);

std::vector<double> Wave::createSine(double freq, double duration)
{
	int phase = 0;
	int tableSize = duration * SAMPLE_RATE;
	std::vector<double> sine(tableSize, 0.0);
	int increment = LUT->size() * freq / SAMPLE_RATE;
	for (int i = 0; i < tableSize; i++)
	{
		sine[i] = (*LUT)[phase];
		phase += increment;
		if (phase >= LUT->size()) phase -= LUT->size();
	}
	return sine;
}

void Wave::appendWaves(std::vector<double> table2)
{
	waveTable->insert(this->waveTable->end(), table2.begin(), table2.end());
	tableSize = waveTable->size();
}

void Wave::addWaves(std::vector<double> table2)
{
	if (waveTable->size() < table2.size()) waveTable->resize(table2.size(), 0.0);
	for (int i = 0; i < waveTable->size(); i++)
	{
		(*waveTable)[i] += table2[i];
	}
	tableSize = waveTable->size();
}

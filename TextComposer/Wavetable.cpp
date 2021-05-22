#include <math.h>
#include <vector>
#include "Wavetable.h"

#define M_PI  (3.14159265)

// Create a LUT
Wavetable::Wavetable()
{
	waveTable->assign(0, 0.0);
}

std::vector<double> Wavetable::createSineLUT(int size)
{
	std::vector<double> sineLUT(size, 0.0);
	for (int i = 0; i < size; i++)
	{
		sineLUT[i] = (float)sin((double)i * M_PI * 2.0 / (double)size);
	}
}

std::vector<double> Wavetable::createSine(std::vector<double> LUT, double freq, double duration, int sample_rate)
{
	int phase = 0;
	int tableSize = duration * sample_rate;
	std::vector<double> sine(tableSize, 0.0);
	int increment = LUT.size() * freq / sample_rate;
	for (int i = 0; i < tableSize; i++)
	{
		sine[i] = LUT[phase];
		phase += increment;
		if (phase >= LUT.size()) phase -= LUT.size();
	}
	return sine;
}

void Wavetable::appendWaves(std::vector<double> table2)
{
	waveTable->insert(this->waveTable->end(), table2.begin(), table2.end());
	tableSize = waveTable->size();
}

void Wavetable::addWaves(std::vector<double> table2)
{
	if (waveTable->size() < table2.size()) waveTable->resize(table2.size(), 0.0);
	for (int i = 0; i < waveTable->size(); i++)
	{
		(*waveTable)[i] += table2[i];
	}
	tableSize = waveTable->size();
}

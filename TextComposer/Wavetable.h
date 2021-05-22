#pragma once
#include <map>
#include <string>
#include <vector>

class Wavetable
{
public:
	std::vector<double>* waveTable;
	int tableSize;

	static std::vector<double> createSine(std::vector<double> LUT, double freq, double duration, int sample_rate);
	static std::vector<double> createSineLUT(int size);

	void addWaves(std::vector<double> table2);
	void appendWaves(std::vector<double> table2);
};
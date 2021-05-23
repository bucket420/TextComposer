#pragma once
#include <map>
#include <string>
#include <vector>

class Wave
{
public:
	std::vector<double>* waveTable;
	int tableSize;
	static const int SAMPLE_RATE = 44100;
	
	static std::vector<double>* createSineLUT(int size);
	static const std::vector<double>* LUT;

	static std::vector<double> createSine(double freq, double duration);

	void addWaves(std::vector<double> table2);
	void appendWaves(std::vector<double> table2);
};
#pragma once
#include <map>
#include <string>
#include <vector>

class Wave
{
public:
	std::vector<double> waveTable;
	int tableSize;

	Wave();
	Wave(std::vector<double> waveTable);

	static std::vector<double> createSine(double freq, double duration);

	void addWaves(std::vector<double> table2);
	void appendWaves(std::vector<double> table2);
};
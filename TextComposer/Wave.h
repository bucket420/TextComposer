#pragma once
#include <map>
#include <string>
#include <vector>

namespace Wave
{
	std::vector<double> createWave(double freq, double duration);
	std::vector<double> addWaves(std::vector<std::vector<double>> *tables);
	std::vector<double> appendWaves(std::vector<std::vector<double>> *tables);
};
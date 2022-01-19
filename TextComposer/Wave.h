#pragma once
#include <string>
#include <vector>

namespace Wave
{
	// Constants
	const int SAMPLE_RATE = 44100;
	const double FIRST_OCTAVE_FREQ[7] = { 16.35, 18.35, 20.60, 21.83, 24.50, 27.50, 30.87 };
	const char OCTAVE[7] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };
	const std::string ROMAN_NUMBERS[7] = { "I", "II", "III", "IV", "V", "VI", "VII" };
	const int MAJOR_SCALE_STEPS[7] = { 1, 3, 5, 6, 8, 10, 12 };
	const int MINOR_SCALE_STEPS[7] = { 1, 3, 4, 6, 8, 9, 11 };
	extern std::vector<double> LUT;

	// Funtions
	std::vector<double> createWave(double freq, double duration);
	std::vector<double> addWaves(std::vector<std::vector<double>> *tables);
	std::vector<double> appendWaves(std::vector<std::vector<double>> *tables);
	std::vector<double> createGuitarLUT(int size);
	std::vector<double> createSineLUT(int size);
};
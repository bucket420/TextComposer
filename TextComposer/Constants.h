#pragma once
#include <vector>

// Variables
const std::vector<double>* LUT;
const int SAMPLE_RATE = 44100;
const double FIRST_OCTAVE_FREQ[7] = { 16.35, 18.35, 20.60, 21.83, 24.50, 27.50, 30.87 };
const char FIRST_OCTAVE[7] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };

//Functions
std::vector<double>* createSineLUT(int size);
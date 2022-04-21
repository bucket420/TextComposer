#pragma once
#include <map>
#include <string>
#include <vector>

class Wave
{
public:
	const static int SAMPLE_RATE = 44100;
	const static double FIRST_OCTAVE_FREQ[7];
	const static char OCTAVE[7];
	const static std::string ROMAN_NUMBERS[7];
	const static int MAJOR_SCALE_STEPS[7];
	const static int MINOR_SCALE_STEPS[7];
	const static std::vector<double> LUT;

	Wave();
	Wave(double freq, double duration);
	Wave(std::vector<double>* waveTable);
	
	void add(Wave wave);
	void append(Wave wave);
	void normalize();
	void setWaveTable(double freq, double duration);
	void setWaveTable(std::vector<double> waveTable);
	std::vector<double> getWaveTable();
	double getDuration();

	static std::vector<double> addWaveTables(std::vector<std::vector<double>>* tables);
	static std::vector<double> appendWaveTables(std::vector<std::vector<double>>* tables);
	static std::vector<double> createWaveTable(double freq, double duration);
	static std::vector<double> createGuitarLUT(int size);
	static std::vector<double> createSineLUT(int size);
	static double getNoteFreq(std::string name);

protected:
	std::vector<double> waveTable = {};
};
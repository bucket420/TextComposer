#pragma once
#include <map>
#include <string>
#include <vector>

class Wave
{
public:
	const static int SAMPLE_RATE = 44100;
	const static int MAJOR_SCALE_STEPS[7];
	const static int MINOR_SCALE_STEPS[7];
	const static char OCTAVE[7];
	const static double FIRST_OCTAVE_FREQ[7];
	const static std::string ROMAN_NUMBERS[7];
	const static std::vector<double> LUT;

	static double timeSignatureLower;
	static double BPM;

	Wave();
	Wave(double freq, double duration);
	
	void add(Wave wave);
	void append(Wave wave);
	void normalize();
	void setWaveTable(double freq, double duration);
	bool isEmpty();
	double getDuration();
	std::vector<double> getWaveTable();

	static std::vector<double> createWaveTable(double freq, double duration);
	static std::vector<double> createGuitarLUT(int size);
	static std::vector<double> createSineLUT(int size);
	static double getNoteFreq(std::string name);
	static double getDuration(std::string input);
	static void setTimeSignatureLowerAndBPM(std::string timeSignatureLower, std::string BPM);

protected:
	std::vector<double> waveTable = {};
};
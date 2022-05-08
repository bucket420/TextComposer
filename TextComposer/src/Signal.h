#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>

class Signal
{
public:
	static double BPM;
	static double timeSignatureLower;

	const static double FIRST_OCTAVE_FREQ[7];
	const static std::vector<double> LUT;
	const static int MAJOR_SCALE_STEPS[7];
	const static int MINOR_SCALE_STEPS[7];
	const static char OCTAVE[7];
	const static std::string ROMAN_NUMBERS[7];
	const static int SAMPLE_RATE = 44100;

	Signal();
	Signal(double freq, double duration);
	
	void add(Signal* signal);
	void append(Signal* signal);
	double get();
	double getDuration();
	double getPhase();
	std::vector<double> getWaveTable();
	void incrementPhase();
	bool isEmpty();
	void normalize();
	void setWaveTable(double freq, double duration);

	static std::vector<double> createGuitarLUT(int size);
	static std::vector<double> createSineLUT(int size);
	static std::vector<double> createWaveTable(double freq, double duration);
	static double getDuration(std::string input);
	static double getNoteFreq(std::string name);
	static void setTimeSignatureLowerAndBPM(std::string timeSignatureLower, std::string BPM);

protected:
	std::unique_ptr<std::vector<double>> waveTable = std::unique_ptr<std::vector<double>>(new std::vector<double>);
	int phase = 0;
};
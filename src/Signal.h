#pragma once
#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Signal
{
public:
	/* Beats per minute */
	static double BPM;

	/* The lower part of time signature */
	static double timeSignatureLower;

	/* The Lookup Table used to generate signals */
	const static std::vector<double> LUT;

	/* Mapping the musical alphabet to frequencies in the first octave*/
	const static std::unordered_map<char, double> FIRST_OCTAVE_FREQ;

	/* Mapping Roman numbers representing chords to positions of their root notes in the 12-tone (chromatic) scale*/
	const static std::unordered_map<std::string, std::array<int, 2>> ROMAN_NUMBERS;

	/* Sample rate */
	const static int SAMPLE_RATE = 44100;

	/* Default constructor, the wavetable is set to an empty vector */
	Signal();

	/* The wavetable is set to a specific frequency and duration */
	Signal(double freq, double duration);

	/* Get the data point at current phase */
	double get();

	/* Get the duration of the signal */
	double getDuration();

	/* Get the phase of the signal */
	double getPhase();

	/* Get the wavetable of the signal */
	std::vector<double> getWavetable();

	/* Increment the phase of the signal */
	void incrementPhase();

	/* Return true if the wavetable is empty */
	bool isEmpty();

	/* Set the lower part of time signature and beats per minute */
	static void setTimeSignatureLowerAndBPM(std::string timeSignatureLower, std::string BPM);

	/* Set the wavetable to a specific frequency and duration */
	void setWavetable(double freq, double duration);

protected:
	/* The wavetable of the signal */
	std::unique_ptr<std::vector<double>> waveTable = std::unique_ptr<std::vector<double>>(new std::vector<double>);

	/* The phase of the signal (an index of a value in the wavetable) */
	int phase = 0;

	/* Add a signal to this signal */
	void add(Signal& signal);

	/* Append a signal to this signal */
	void append(Signal& signal);

	/* Normalize the signal so that the highest amplitude is 1 */
	void normalize();

	/* Create a Lookup Table for the signal that guitar produces */
	static std::vector<double> createGuitarLUT(int size);

	/* Create a Lookup Table for the signal that guitar produces */
	static std::vector<double> createSineLUT(int size);

	/* Get the intended duration from an input */
	static double getDuration(std::string input);

	/* Get the frequency of a note */
	static double getNoteFreq(std::string name);
};
#pragma once
#include <memory>
#include <string>
#include <vector>

class Signal
{
public:
	/* Beats per minute */
	static double BPM;

	/* The lower part of time signature */
	static double timeSignatureLower;

	/* Frequency of every note in the first octave */
	const static double FIRST_OCTAVE_FREQ[7];

	/* The Lookup Table used to generate signals */
	const static std::vector<double> LUT;

	/* The position of each note in the major scale (1 means the key, 3 means 2 half-steps from the key, etc. */
	const static int MAJOR_SCALE_STEPS[7];

	/* The position of each note in the minor scale (1 means the key, 3 means 2 half-steps from the key, etc.) */
	const static int MINOR_SCALE_STEPS[7];

	/* The musical alphabet */
	const static char OCTAVE[7];

	/* Roman numbers from 1 to 7 */
	const static std::string ROMAN_NUMBERS[7];

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
	void add(Signal* signal);

	/* Append a signal to this signal */
	void append(Signal* signal);

	/* Normalize the signal so that the highest amplitude is 1 */
	void normalize();

	/* Create a Lookup Table for the signal that guitar produces */
	static std::vector<double> createGuitarLUT(int size);

	/* Create a Lookup Table for the signal that guitar produces */
	static std::vector<double> createSineLUT(int size);

	/* Create a Lookup Table a sine wave */
	static std::vector<double> createWavetable(double freq, double duration);

	/* Get the intended duration from an input */
	static double getDuration(std::string input);

	/* Get the frequency of a note */
	static double getNoteFreq(std::string name);
};
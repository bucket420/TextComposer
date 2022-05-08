#pragma once
#include "Chord.h"

class ChordProgression : public Signal
{
public:
	ChordProgression(std::string progression, std::string key, std::string scaleType);

private:
	std::string progression;
	std::string key;
	std::string scaleType;

	std::array<double, 25> createTwoOctaveScale(std::string key);
	std::vector<int> getChordIndexes();
	std::vector<std::string> getChords();
	void setWaveTable();
};
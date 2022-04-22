#pragma once
#include "Chord.h"

class ChordProgression : public Wave
{
public:
	ChordProgression(std::string progression, std::string key, std::string scaleType);

private:
	std::string progression;
	std::string key;
	std::string scaleType;

	std::vector<int> getChordIndexes();
	std::vector<std::string> getChords();
	std::array<double, 25> createTwoOctaveScale(std::string key);
	void setWaveTable();
};
#include "ChordProgression.h"
#include <memory>

ChordProgression::ChordProgression(std::string progression, std::string key, std::string scaleType)
{
	this->progression = progression;
	this->key = key;
	this->scaleType = scaleType;
	setWaveTable();
}

std::vector<int> ChordProgression::getChordIndexes()
{
	std::vector<int> chordIndexes;
	for (int i = 0; i < progression.length(); i++)
	{
		if (isalpha(progression[i]))
		{
			if (i > 0 && isalpha(progression[i - 1]))
			{
				continue;
			}
			chordIndexes.push_back(i);
		}
	}
	return chordIndexes;
}


std::vector<std::string> ChordProgression::getChords()
{
	std::vector<int> chordIndexes = getChordIndexes();
	std::vector<std::string> chords(chordIndexes.size(), "");
	if (chordIndexes.empty()) return chords;
	for (int i = 0; i < chordIndexes.size(); i++)
	{
		if (i == chordIndexes.size() - 1)
		{
			chords[i] = progression.substr(chordIndexes[i]);
			return chords;
		}
		chords[i] = progression.substr(chordIndexes[i], (long long)chordIndexes[i + 1] - chordIndexes[i]);
	}
}

std::array<double, 25> ChordProgression::createTwoOctaveScale(std::string key)
{
	if (std::find(OCTAVE, OCTAVE + 7, key[0]) == std::end(OCTAVE)) return {};
	std::array<double, 25> twoOctaveScale;
	double firstNote = getNoteFreq(key + '4') * pow(2.0, -1.0 / 12.0);
	if (key.size() > 2 || ((key.size() == 2) && key[1] != '#' && key[1] != 'b') || key.size() == 0) return {};
	if (key[1] == '#')
	{
		firstNote *= pow(2.0, 1.0 / 12.0);
	}
	if (key[1] == 'b')
	{
		firstNote *= pow(2.0, -1.0 / 12.0);
	}
	for (int i = 0; i < 25; i++)
	{
		twoOctaveScale[i] = firstNote * pow(2.0, (double)i / 12.0);
	}
	return twoOctaveScale;
}

void ChordProgression::setWaveTable()
{
	std::vector<std::string> chordList = getChords();
	std::array<double, 25> scale = createTwoOctaveScale(key);
	if (key.empty())
	{
		return;
	}
	for (int i = 0; i < chordList.size(); i++)
	{
		this->append(std::unique_ptr<Signal>(new Chord(chordList[i], scale, scaleType)));
	}

}


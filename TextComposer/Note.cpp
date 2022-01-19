#include "Note.h"

double Note::getNoteFreq(std::string name)
{
	char letter = name[0];
	int octaveNumber = name[name.length() - 1] - '0';
	const char* iterator = std::find(Wave::OCTAVE, Wave::OCTAVE + 7, letter);
	int index = iterator - Wave::OCTAVE;
	double freq = 0;
	if (name.length() == 2)
	{
		freq = Wave::FIRST_OCTAVE_FREQ[index] * pow(2.0, (double)octaveNumber);
	}
	if (name[1] == '#')
	{
		freq = Wave::FIRST_OCTAVE_FREQ[index] * pow(2.0, (double)octaveNumber + 1.0 / 12.0);
	}
	if (name[1] == 'b')
	{
		freq = Wave::FIRST_OCTAVE_FREQ[index] * pow(2.0, (double)octaveNumber - 1.0 / 12.0);
	}
	return freq;
}

double Note::getDuration(std::string note, std::string timeSignatureLower, std::string BPM)
{
	int eighthCount = std::count(note.begin(), note.end(), '-');
	int sixtyfourthCount = std::count(note.begin(), note.end(), '.');
	if (eighthCount == 0 && sixtyfourthCount == 0) return 0.0;
	return std::stod(timeSignatureLower) * 60.0 / std::stod(BPM) * ((double)sixtyfourthCount * 1.0 / 64.0 + (double)eighthCount * 0.125);
}

void Note::setWaveTable(std::string note, std::string timeSignatureLower, std::string BPM)
{
	std::string name;
	double duration = getDuration(note, timeSignatureLower, BPM);
	if (duration == 0) return;
	if (note[1] == '#' || note[1] == 'b')
	{
		name = note.substr(0, 3);
	}
	else
	{
		name = note.substr(0, 2);
	}
	this->waveTable = createWaveTable(getNoteFreq(name), duration);	
}
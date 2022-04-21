#include "Note.h"

Note::Note(std::string note, std::string timeSignatureLower, std::string BPM)
{
	this->note = note;
	setWaveTable(timeSignatureLower, BPM);
}


double Note::getDuration(std::string timeSignatureLower, std::string BPM)
{
	int eighthCount = std::count(note.begin(), note.end(), '-');
	int sixtyfourthCount = std::count(note.begin(), note.end(), '.');
	if (eighthCount == 0 && sixtyfourthCount == 0) return 0.0;
	return std::stod(timeSignatureLower) * 60.0 / std::stod(BPM) * ((double)sixtyfourthCount * 1.0 / 64.0 + (double)eighthCount * 0.125);
}

void Note::setWaveTable(std::string timeSignatureLower, std::string BPM)
{
	std::string name;
	double duration = getDuration(timeSignatureLower, BPM);
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
#include "Note.h"

Note::Note(std::string note)
{
	this->note = note;
	setWavetable();
}

void Note::setWavetable()
{
	std::string name;
	double duration = getDuration(note);
	if (duration == 0) return;
	if (note[1] == '#' || note[1] == 'b')
	{
		name = note.substr(0, 3);
	}
	else
	{
		name = note.substr(0, 2);
	}
	this->Signal::setWavetable(getNoteFreq(name), duration);
}
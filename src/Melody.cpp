#include "Melody.h"


Melody::Melody(std::string melody)
{
	this->melody = melody;
	setWavetable();
}

std::vector<int> Melody::getNoteIndexes()
{
	std::vector<int> noteIndexes;
	for (int i = 0; i < melody.length(); i++)
	{
		if (isalpha(melody[i]) && isupper(melody[i]))
		{
			noteIndexes.push_back(i);
		}
	}
	return noteIndexes;
}

std::vector<std::string> Melody::getNotes()
{
	std::vector<int> noteIndexes = getNoteIndexes();
	std::vector<std::string> notes(noteIndexes.size(), "");
	if (noteIndexes.empty()) return notes;
	for (int i = 0; i < noteIndexes.size(); i++)
	{
		if (i == noteIndexes.size() - 1)
		{
			notes[i] = melody.substr(noteIndexes[i]);
			return notes;
		}
		notes[i] = melody.substr(noteIndexes[i], (long long)noteIndexes[i + 1] - noteIndexes[i]);
	}
}

void Melody::setWavetable()
{
	std::vector<std::string> noteList = getNotes();
	if (noteList.empty()) return;
	for (int i = 0; i < noteList.size(); i++)
	{
		Note note = Note(noteList[i]);
		this->append(note);
	}
}
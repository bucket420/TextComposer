#include <vector>
#include "Input.h"


Input::Input(std::string input) 
{
	this->input = input;
}

std::vector<int> Input::getNoteIndexes()
{
	std::vector<int> noteIndexes;
	for (int i = 0; i < input.length(); i++)
	{
		if (isalpha(input[i]) && isupper(input[i]))
		{
			noteIndexes.push_back(i);
		}
	}
	return noteIndexes;
}

std::vector<std::string> Input::getNotes()
{
	std::vector<int> noteIndexes = this->getNoteIndexes();
	std::vector<std::string> notes(noteIndexes.size(), "");

	for (int i = 0; i < noteIndexes.size(); i++)
	{

	}
}
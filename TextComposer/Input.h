#pragma once
#include <vector>
#include <string>

class Input
{
public:
	Input(std::string input);
	std::string input;

private:
	std::vector<int> getNoteIndexes();
	std::vector<std::string> getNotes();
	
};
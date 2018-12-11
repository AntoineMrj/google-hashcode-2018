#pragma once

#include "pch.h"

class Arbitror
{
private:
	City city;
	FileLoader* fileLoader;
	std::string projectFile;
	std::string solutionFile;
	int score;
public:
	Arbitror();
	Arbitror(std::string projectFile, std::string solutionFile);

	void evaluate();
	int getScore();

	~Arbitror();
};



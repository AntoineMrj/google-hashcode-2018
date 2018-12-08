#pragma once

#include "FileLoader.h"

class Arbitror
{
private:
	City city;
	int score;
public:

	Arbitror(std::string projectFile, std::string solutionFile);

	void evaluate();
	bool checkPosition();
	void computeScore();

	~Arbitror();
};



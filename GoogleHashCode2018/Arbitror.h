#pragma once

#include "FileLoader.h"

class Arbitror
{
private:
	Project project;
	Project solution;
	int score;
public:

	Arbitror(std::string projectFile, std::string solutionFile);

	void evaluate();
	bool checkPosition();
	void computeScore();

	~Arbitror();
};



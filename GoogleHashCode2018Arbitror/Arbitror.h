#pragma once

#include <chrono>
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

	Arbitror(std::string projectFile, std::string solutionFile);

	double computeTime();
	void evaluate();

	~Arbitror();
};



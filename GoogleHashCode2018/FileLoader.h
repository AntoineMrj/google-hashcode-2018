#pragma once
#include <fstream>
#include <string>
#include "Project.h"
#include "City.h"
#include "Residential.h"
#include "Utility.h"
#include <vector>
#include <iostream>


class FileLoader
{
public:
	FileLoader();
	~FileLoader();

	void loadProject(std::string projectFile);
	City loadSolution(std::string projectFile, std::string solutionFile);
};


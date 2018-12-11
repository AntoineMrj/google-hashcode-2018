#pragma once
#include <fstream>
#include <string>
#include "Project.h"
#include "City.h"
#include <vector>
#include <iostream>


class FileLoader
{
public:

	static void loadProject(std::string projectFile);
	static void loadSolution(std::string projectFile, std::string solutionFile);
};


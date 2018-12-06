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

	Project loadProject(std::string source);
	Project loadSolution(std::string source);
};


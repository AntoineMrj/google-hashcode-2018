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

	void loadProject(std::string source);
	City loadSolution(std::string source,std::string solution);
};


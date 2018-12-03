#pragma once
#include <fstream>
#include <string>
#include "Project.h"
#include "City.h"
#include <vector>
#include <iostream>

using namespace std;

class FileLoader
{
public:
	FileLoader();
	~FileLoader();

	Project loadProject(string source);
};


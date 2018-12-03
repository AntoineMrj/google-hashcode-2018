#pragma once
#include <fstream>
#include <string>
#include "Project.h"
#include <vector>

using namespace std;

class FileLoader
{
public:
	FileLoader();
	~FileLoader();

	Project loadProject(string source);
};


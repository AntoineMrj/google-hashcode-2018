#pragma once
#include <fstream>
#include <string>
#include "Project.h"

using namespace std;

class FileLoader
{
public:
	FileLoader();
	~FileLoader();

	Project loadProject(string source);
};


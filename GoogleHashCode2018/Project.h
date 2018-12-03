#pragma once
#include "City.h"
#include "Building.h"
#include "Utility.h"
#include "Residential.h"
#include <vector>

using namespace std;

class Project
{
public:
	City city;
	vector<Building*> buildings; // liste des projects buildings disponibles
	vector<int> residentials; // liste des residences faisant referance a l index dans building
	vector<int> utilities;
	Project();
	Project(City city_); // liste des utilities faisant reference a l index dans building

	void setCity(unsigned int width,unsigned int height);
	void addUtility(Building* b);
	void addResidential(Building *r);
};
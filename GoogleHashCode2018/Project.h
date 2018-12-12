#pragma once
#include "City.h"
#include <vector>
#include <set>

using namespace std;
//Il faudrait rendre la classe static pour faire le lien entre les Places
//Il n'y aura que 1 projet par session je pense
//Sinon il va falloir lier une city à un project
class Project
{
public:
	static Project globalProject;
	City* city;
	vector<Building*> buildings; // liste des projects buildings disponibles
	vector<int> residentials; // liste des residences faisant referance a l index dans building
	vector<int> utilities;
	Project();
	Project(City* city_); // liste des utilities faisant reference a l index dans building

	void setCity(unsigned int width,unsigned int height);
	void addUtility(Building* b);
	void addResidential(Building *r);
	void setMaxWalkingDistance(int MaxWD);
	std::vector<Coord> basic_influenceArea;
	int maxWalkingDistance;
	std::vector<unsigned int> UtilitiesReferences;
};
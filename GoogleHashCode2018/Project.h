#pragma once
#include "City.h"
#include <vector>
#include <set>
#include <string>

using namespace std;
//Il faudrait rendre la classe static pour faire le lien entre les Places
//Il n'y aura que 1 projet par session je pense
//Sinon il va falloir lier une city à un project
class Project
{
private:
	std::string projectFile;
	std::string solutionFile;
public:
	static Project globalProject;
	City* city;
	vector<Building*> buildings; // liste des projects buildings disponibles
	vector<int> residentials; // liste des residences faisant referance a l index dans building
	vector<int> utilities;
	Project();
	Project(City* city_); // liste des utilities faisant reference a l index dans building

	void setProjectFile(std::string projectFile);
	void setSolutionFile(std::string solutionFile);
	std::string getProjectFile();
	std::string getSolutionFile();
	void setCity(unsigned int width,unsigned int height);
	void addUtility(Building* b);
	void addResidential(Building *r);
	void setMaxWalkingDistance(int MaxWD);
	//Building getProjectById(unsigned int PId); //TO DO
	std::vector<Coord> basic_influenceArea;
	int maxWalkingDistance;
	std::vector<unsigned int> UtilitiesReferences;
};
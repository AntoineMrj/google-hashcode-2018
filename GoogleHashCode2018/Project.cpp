#include "Project.h"

Project::Project() {

}

Project::Project(City city_, vector<Building> buildings_, vector<int> residentials_, vector<int> utilities_)
{
	this->city = city_;
	this->buildings = buildings_;
	this->residentials = residentials_;
	this->utilities = utilities_;
}

void Project::addBuilding(Utility u)
{
	this->buildings.push_back(u);
	this->utilities.push_back(buildings.size() - 1);
}

void Project::addBuilding(Residential r)
{
	this->buildings.push_back(r);
	this->residentials.push_back(buildings.size() - 1);
}

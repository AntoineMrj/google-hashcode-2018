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
}

void Project::addBuilding(Residential u)
{
}

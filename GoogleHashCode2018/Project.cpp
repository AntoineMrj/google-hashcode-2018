#include "Project.h"
Project Project::globalProject;
Project::Project() {
	this->buildings = vector<Building *>();
	this->residentials = vector<int>();
	this->utilities = vector<int>();
}

Project::Project(City city_)
{
	this->city = city_;
	this->buildings = vector<Building*>();
	this->residentials =vector<int>();
	this->utilities = vector<int>();
}

void Project::addUtility(Building *u)
{
	this->buildings.push_back(u);
	this->utilities.push_back(buildings.size() - 1);
}

void Project::addResidential(Building *r)
{
	this->buildings.push_back(r);
	this->residentials.push_back(buildings.size() - 1);
}

void Project::setCity(unsigned int width, unsigned int height)
{
	city = City(height,width);
}
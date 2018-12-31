#include "Project.h"
using namespace std;
Project Project::globalProject;

Project::Project() {
	this->buildings = vector<Building *>();
	this->residentials = vector<Building*>();
	this->utilities = map<unsigned int,vector<Building*> >();
	minWidth=10000;
	maxWidth=0;
	minHeight=100000;
	maxHeight=0;
}

Project::Project(City* city_)
{
	this->city = city_;
	this->buildings = vector<Building*>();
	this->residentials = vector<Building *>();
	this->utilities = map<unsigned int, vector<Building *>>();
	minWidth = 10000;
	maxWidth = 0;
	minHeight = 100000;
	maxHeight = 0;
}

void Project::setProjectFile(std::string projectFile)
{
	this->projectFile = projectFile;
}

void Project::setSolutionFile(std::string solutionFile)
{
	this->solutionFile = solutionFile;
}

std::string Project::getProjectFile()
{
	return this->projectFile;
}

std::string Project::getSolutionFile()
{
	return this->solutionFile;
}

void Project::addUtility(Building *u)
{
	if (u->getColumnNum() > maxWidth)
		maxWidth = u->getColumnNum();
	if (u->getColumnNum() < minWidth)
		minWidth = u->getColumnNum();
	if (u->getRowNum() > maxHeight)
		maxHeight = u->getRowNum();
	if (u->getRowNum() < minHeight)
		minHeight = u->getRowNum();
	this->buildings.push_back(u);
	if(utilities.find(u->getExtra())==utilities.end())
	{
		utilities[u->getExtra()] = std::vector<Building*>();

	}
		utilities[u->getExtra()].push_back(u);
}

void Project::addResidential(Building *r)
{
	if(r->getColumnNum()>maxWidth)
		maxWidth=r->getColumnNum();
	if (r->getColumnNum() < minWidth)
		minWidth = r->getColumnNum();
	if (r->getRowNum() > maxHeight)
		maxHeight = r->getRowNum();
	if (r->getRowNum() < minHeight)
		minHeight = r->getRowNum();
	this->buildings.push_back(r);
	this->residentials.push_back(r);
}

void Project::setCity(unsigned int width, unsigned int height)
{
	city = new City(height,width);
}
void Project::prepare()
{
	sort(residentials.begin(),residentials.end(),[](Building* a,Building* b)->bool
	{
		return a->getDensity()<b->getDensity();
	});
	for(auto it:utilities)
	{
		sort(it.second.begin(), it.second.end(), [](Building *a,Building *b) -> bool {
			return a->getRatio() < b->getRatio();
		});
	}
}
/**
 * @brief
 * Set the maximal walking distance of this city.
 * Define at the same time all coordinates relative to a case that can be accesible.
 * @param MaxWD 
 */
void Project::setMaxWalkingDistance(int MaxWD)
{
	int width = 0;
	for(int row=-MaxWD;row<=MaxWD;row++)
	{
		for(int col=-width;col<=width;col++)
		{
			if(!(row==0&&col==0))
			{
				this->basic_influenceArea.push_back({row,col});
			}
		}
		if(row<0)
			width++;
		else
			width--;
	}
	this->maxWalkingDistance = MaxWD;
}

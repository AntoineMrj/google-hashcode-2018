#include "Project.h"
Project Project::globalProject;
Project::Project() {
	this->buildings = vector<Building *>();
	this->residentials = vector<int>();
	this->utilities = vector<int>();
}

Project::Project(City* city_)
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
	if(std::find(UtilitiesReferences.begin(),UtilitiesReferences.end(),u->getExtra())!=UtilitiesReferences.end())
	{
		UtilitiesReferences.push_back(u->getExtra());
	}
}

void Project::addResidential(Building *r)
{
	this->buildings.push_back(r);
	this->residentials.push_back(buildings.size() - 1);
}

void Project::setCity(unsigned int width, unsigned int height)
{
	city = new City(height,width);
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

/*Building Project::getProjectById(unsigned int PId)
{
 //TO DO
	return Building();
}*/

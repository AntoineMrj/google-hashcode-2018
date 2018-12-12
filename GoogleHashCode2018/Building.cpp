#include "Building.h"
#include "City.h"
#include "Project.h"

Building::Building(unsigned int projectNum_, unsigned int rowNum_, unsigned int columnNum_,unsigned int ex,Building_type t)
{
	this->projectNum = projectNum_;
	this->rowNum = rowNum_;
	this->columnNum = columnNum_;
	this->type = t;
	this->extra = ex;
	this->occupiedCells = new int*[rowNum_];
	for(unsigned int i = 0;i<this->rowNum;i++)
		this->occupiedCells[i] = new int[columnNum_];
}

Building::Building(const Building &b)
{
	projectNum = b.projectNum;
	rowNum = b.rowNum;
	columnNum = b.columnNum;
	this->occupiedCells = new int *[this->rowNum];
	for (unsigned int i = 0; i< this->rowNum;i++)
		this->occupiedCells[i] = new int[this->columnNum];
	assignArray(b.occupiedCells);
	type = b.type;
	extra = b.extra;
}

Building& Building::operator=(Building const& buildingB)
{
	projectNum = buildingB.projectNum;
	rowNum = buildingB.rowNum;
	columnNum = buildingB.columnNum;
	occupiedCells = buildingB.occupiedCells;
	this->occupiedCells = new int *[this->rowNum];
	for (unsigned int i = 0; i< this->rowNum;i++)
		this->occupiedCells[i] = new int[this->columnNum];
	assignArray(buildingB.occupiedCells);
	type = buildingB.type;
	extra = buildingB.extra;
	return *this;
}
/**
 * @brief
 * Assign a 2D int array to the oocupied cells of this building.
 * The size of the array must correspond with the one of the building.
 * @param array 
 */
void Building::assignArray(int **array)
{
	for(unsigned int i = 0;i<rowNum;i++)
	{
		for(unsigned int j = 0;j<columnNum;i++)
			occupiedCells[i][j]=array[i][j];
	}
	shape = this->getShape();
	this->buildInfluenceArea();
}
/**
 * @brief
 * Assign a value to a cell of the occupiedCells Array
 * @param row
 * @param column 
 * @param value 
 */
void Building::setCell(unsigned int row, unsigned int column, int value)
{
	occupiedCells[row][column]=value;
}
/**
 * @brief
 * Set the project num of the building.
 * @param projectNum_ 
 */
void Building::setProjectNum(unsigned int projectNum_)
{
	this->projectNum = projectNum_;
}
/**
 * @brief
 * Return the value of a cell of this building.
 * @param row 
 * @param column 
 * @return int 
 */
int Building::getCell(unsigned int row, unsigned int column)
{
	return this->occupiedCells[row][column];
}
/**
 * @brief
 * Compute the shape and the influence area of the building
 * This allow to gain time in cmputation when placing building on a city.
 */
void Building::computeShape()
{
	shape = this->getShape();
	this->buildInfluenceArea();
}
/**
 * @brief
 * Algorithm determining the shape of a building
 * @return vector<Coord> 
 */
vector<Coord> Building::getShape()
{
	Coord coord;
	std::vector<Coord> Top;
	std::vector<Coord> Bottom;
	std::vector<Coord> Left;
	std::vector<Coord> Right;

	vector<Coord> res; //tableau resultat

	bool first=true;

	bool begin_middle=true;

	bool end=false;

	for(int i=0;i<rowNum;i++)
	{
		if(i>=(int(rowNum)-1))
		{
			first = false;
			end=true;
		}
		for(int j=0;j<columnNum;j++)
		{
			if(first&&occupiedCells[i][j])
			{
				Top.push_back({i,j});
			}
			if(!first&&!end)
			{
				if (begin_middle && occupiedCells[i][j])
				{
					Left.push_back({i,j});
					begin_middle=false;
				}
				else if (occupiedCells[i][j])
				{
					coord={i,j};
				}
			}
			if(end&&occupiedCells[i][j])
			{
				Bottom.push_back({i,j});
			}
		}
		if(!first&&!end)
		{
			Right.push_back(coord);
			begin_middle=true;
		}
		first=false;
	}
	std::reverse(Left.begin(),Left.end());
	std::reverse(Bottom.begin(),Bottom.end());
	Top.insert(Top.end(),Right.begin(),Right.end());
	Top.insert(Top.end(),Bottom.begin(),Bottom.end());
	Top.insert(Top.end(),Left.begin(),Left.end() );
	return Top;
}

bool Building::cellInRes(unsigned int row, unsigned int column, vector<Coord> result) 
{
	for (unsigned int i = 0; i < result.size(); i++) {
		if (unsigned(result[i].column) == column && unsigned(result[i].row) == row) {
			return true;
		}
	}
	return false;
}
/**
 * @brief
 * Determine all Coordinates relative to the top left corner of the building
 * that will affect the other building on a city
 */
void Building::buildInfluenceArea()
{
	Project& p = Project::globalProject;
	for(auto C : shape)
	{
		for(const Coord& Influ:Project::globalProject.basic_influenceArea)
		{
			Coord temp = {C.row+Influ.row,C.column+Influ.column};
			if (std::find(influenceArea.begin(), influenceArea.end(), temp) == influenceArea.end())
			{
				if(temp.row >=0 && temp.row<int(rowNum)
					&& temp.column>=0 && temp.column<int(columnNum))
					{
						if(std::find(shape.begin(),shape.end(),temp)==shape.end()
							&& occupiedCells[temp.row][temp.column]==0)
							{
								influenceArea.push_back(temp);
							}
					}
				else
					{
							influenceArea.push_back(temp);
					}
			}
		}
	}
}
std::vector<Coord> Building::getInfluenceArea()
{
	return influenceArea;
}

Building_type Building::getType()
{
	return type;
}
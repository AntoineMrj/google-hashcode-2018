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

void Building::setCell(unsigned int row, unsigned int column, int value)
{
	occupiedCells[row][column]=value;
}

void Building::setProjectNum(unsigned int projectNum_)
{
	this->projectNum = projectNum_;
}

int Building::getCell(unsigned int row, unsigned int column)
{
	return this->occupiedCells[row][column];
}

vector<Coord> Building::getShape()
{
	Coord coord;
	Coord coords; // coord start
	coords.row = 0;
	coords.column = 0;

	if (occupiedCells[0][0] == 0) {
		for (unsigned int i = 1; i < this->columnNum; i++) {
			if (occupiedCells[0][i] == 1) {
				coords.column = i;
				break;
			}
		}
	}

	coord.row = coords.row;
	coord.column = coords.column;

	vector<Coord> res; //tableau resultat
	res.push_back(coord);

	unsigned int z = 0;

	do
	{
		if (occupiedCells[coord.row-1][coord.column] == 1 && !cellInRes(coord.row -1, coord.column, res)) {
			coord.row -= 1;
		}
		else if (occupiedCells[coord.row][coord.column + 1] == 1 && !cellInRes(coord.row, coord.column+1, res)) {
			coord.column += 1;
		}
		else if (occupiedCells[coord.row + 1][coord.column] == 1 && !cellInRes(coord.row+1, coord.column, res)) {
			coord.row += 1;
		}
		else if (occupiedCells[coord.row][coord.column - 1] == 1 && !cellInRes(coord.row, coord.column-1, res)) {
			coord.column -= 1;
		}
		else { // no move available then go back
			z--;
			coord = res[z];
		}

		if (!cellInRes(coord.row, coord.column, res)) { // cell not in res then add
			res.push_back(coord);
			z = res.size()-1;
		}

	} while (coord.row != coords.row && coord.column != coords.column);

	return res;
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
void Building::buildInfluenceArea()
{
	for(auto C : shape)
	{
		for(auto Influ:Project::globalProject.basic_influenceArea)
		{
			Coord temp = {C.row+Influ.row,C.column+Influ.column};
			if(influenceArea.find(temp)==influenceArea.end())
			{
				if(temp.row >=0 && temp.row<int(rowNum)
					&& temp.column>=0 && temp.column<int(columnNum))
					{
						if(std::find(shape.begin(),shape.end(),temp)==shape.end()
							&& occupiedCells[temp.row][temp.column]==0)
							{
								influenceArea.insert(temp);
							}
					}
				else
					influenceArea.insert(temp);
			}
		}
	}
}
std::set<Coord> Building::getInfluenceArea()
{
	return influenceArea;
}

Building_type Building::getType()
{
	return type;
}
#include "Building.h"
#include "City.h"


Building::Building(unsigned int projectNum_, unsigned int rowNum_, unsigned int columnNum_)
{
	this->projectNum = projectNum_;
	this->rowNum = rowNum_;
	this->columnNum = columnNum_;
	this->occupiedCells = new unsigned int*[columnNum];
	for(unsigned int i = 0;i++<this->rowNum;)
		this->occupiedCells[i] = new unsigned int[this->columnNum];
}

Building::Building(const Building &b)
{
	projectNum = b.projectNum;
	rowNum = b.rowNum;
	columnNum = b.columnNum;
	this->occupiedCells = new unsigned int *[columnNum];
	for (unsigned int i = 0; i++ < this->rowNum;)
		this->occupiedCells[i] = new unsigned int[this->columnNum];
	assignArray(b.occupiedCells);
}

Building& Building::operator=(Building const& buildingB)
{
	projectNum = buildingB.projectNum;
	rowNum = buildingB.rowNum;
	columnNum = buildingB.columnNum;
	occupiedCells = buildingB.occupiedCells;
	for (unsigned int i = 0; i++ < this->rowNum;)
		this->occupiedCells[i] = new unsigned int[this->columnNum];
	assignArray(buildingB.occupiedCells);
	return *this;
}

unsigned int Building::assignArray(unsigned int **array)
{
	for(unsigned int i = 0;i++<columnNum;)
	{
		for(unsigned int j = 0;j++<rowNum;)
			occupiedCells[i][j]=array[i][j];
	}
}

void Building::setCell(unsigned int column, unsigned int row, unsigned int value)
{
	occupiedCells[column][row] = value;
}
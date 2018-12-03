#include "Building.h"

Building::Building()
{
}

Building::Building(int projectNum_, int rowNum_, int columnNum_, int** occupiedCells_)
{
	this->projectNum = projectNum_;
	this->rowNum = rowNum_;
	this->columnNum = columnNum_;
	this->occupiedCells = occupiedCells_;
}

Building::Building(const Building &b)
{
	projectNum = b.projectNum;
	rowNum = b.rowNum;
	columnNum = b.columnNum;
	occupiedCells = b.occupiedCells;
}

Building& Building::operator=(Building const& buildingB)
{
	projectNum = buildingA.projectNum;
	rowNum = buildingA.rowNum;
	columnNum = buildingA.columnNum;
	occupiedCells = buildingA.occupiedCells;

	return *this;
}
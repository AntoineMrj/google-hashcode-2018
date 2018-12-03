#include "Building.h"

Building::Building()
{
}

Building::Building(int projectNum_, int rowNum_, int columnNum_, vector<vector<int[]>> occupiedCells_)
{
	this->projectNum = projectNum_;
	this->rowNum = rowNum_;
	this->columnNum = columnNum_;
	this->occupiedCells = occupiedCells_;
}
#include <vector>
#pragma once

using namespace std;

class Building
{
private:
	int projectNum;
	int rowNum;
	int columnNum;
	int** occupiedCells;

public:
	Building();
	Building(const Building &b);
	Building& Building::operator=(Building const& buildingB);
	Building(int projectNum_, int rowNum_, int columnNum_, int** occupiedCells_);

	int getProjectNum() { return this->projectNum; }
	int getRowNum() { return this->rowNum; }
	int getcolumnNum() { return this->columnNum; }
	int** getOccupiedCell() { return this->occupiedCells; }
};
#include <vector>
#pragma once

using namespace std;

class Building
{
private:
	int projectNum;
	int rowNum;
	int columnNum;
	vector<vector<int[]>> occupiedCells;

public:
	Building();

	Building(int projectNum_, int rowNum_, int columnNum_, vector<vector<int[]>> occupiedCells_);
	int getProjectNum() { return this->projectNum; }
	int getRowNum() { return this->rowNum; }
	int getcolumnNum() { return this->columnNum; }
	vector<vector<int[]>> getOccupiedCell() { return this->occupiedCells; }
};
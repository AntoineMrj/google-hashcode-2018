#pragma once
#include <vector>
class Coord;

using namespace std;

class Building
{

public:
	Building(const Building &b);
	Building& operator=(Building const& buildingB);
	Building(unsigned int projectNum_, unsigned int rowNum_, unsigned int columnNum_);

	void setCell(unsigned int column,unsigned int row,unsigned int value);
	void setProjectNum(unsigned int projectNum_);
	unsigned int** getOccupiedCell() { return this->occupiedCells; }
	unsigned int getCell(unsigned int column,unsigned int row);
	unsigned int getProjectNum() { return this->projectNum; }
	unsigned int getRowNum() { return this->rowNum; }
	unsigned int getcolumnNum() { return this->columnNum; }

	unsigned int assignArray(unsigned int** array);

  protected:
	unsigned int projectNum;
	unsigned int rowNum;
	unsigned int columnNum;
	unsigned int** occupiedCells;
	std::vector<Coord> shape;
	std::vector<Coord> influenceZone;
};
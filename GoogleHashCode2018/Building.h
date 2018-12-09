#pragma once
#include <vector>
#include <functional>
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
	int** getOccupiedCell() { return this->occupiedCells; }
	int getCell(unsigned int column,unsigned int row);
	unsigned int getProjectNum() { return this->projectNum; }
	unsigned int getRowNum() { return this->rowNum; }
	unsigned int getcolumnNum() { return this->columnNum; }

	unsigned int assignArray(int** array);
	vector<Coord> getShape();
	bool cellInRes(unsigned int r, unsigned int c, vector<Coord> res);
	virtual void placeInCity(City& C);
  protected:
	unsigned int projectNum;
	unsigned int rowNum;
	unsigned int columnNum;
	int** occupiedCells;
	std::vector<Coord> shape;
	std::vector<Coord> influenceZone;
};
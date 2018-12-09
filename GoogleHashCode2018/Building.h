#pragma once
#include <vector>
#include <functional>
#include <set>
#include "Project.h"
class Coord;

using namespace std;

class Building
{
public:
	Building(const Building &b);
	Building& operator=(Building const& buildingB);
	Building(unsigned int projectNum_, unsigned int rowNum_, unsigned int columnNum_);

	void setCell(unsigned int row, unsigned int column, unsigned int value);
	void setProjectNum(unsigned int projectNum_);
	int** getOccupiedCell() { return this->occupiedCells; }
	int getCell(unsigned int row, unsigned int column);
	unsigned int getProjectNum() { return this->projectNum; }
	unsigned int getRowNum() { return this->rowNum; }
	unsigned int getColumnNum() { return this->columnNum; }

	unsigned int assignArray(int** array);
	vector<Coord> getShape();
	bool cellInRes(unsigned int row, unsigned int column, vector<Coord> result);
	virtual void placeInCity(City& C);
	void buildInfluenceArea();
	std::set<Coord> getInfluenceArea();
 protected:
	unsigned int projectNum;
	unsigned int rowNum;
	unsigned int columnNum;
	int** occupiedCells;
	std::vector<Coord> shape;
	std::set<Coord> influenceArea;
};
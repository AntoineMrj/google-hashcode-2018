#pragma once
#include <vector>
#include <functional>
#include <iostream>
#include <set>
#include <algorithm>
class Coord;

using namespace std;
enum Building_type{
	Residential,
	Utility
};
class Building
{
public:
	Building(const Building &b);
	Building& operator=(Building const& buildingB);
	Building(unsigned int projectNum_, unsigned int rowNum_, unsigned int columnNum_,unsigned int extra,Building_type t);
	void assignArray(int** array);
	void buildInfluenceArea();

	int** getOccupiedCell() { return this->occupiedCells; }
	int getCell(unsigned int row, unsigned int column);
	unsigned int getProjectNum() const{ return this->projectNum; }
	unsigned int getRowNum() const { return this->rowNum; }
	unsigned int getColumnNum() const { return this->columnNum; }
	unsigned int getExtra() const { return this->extra; }
	vector<Coord> getShape();
	std::vector<Coord> getInfluenceArea();

	void setCell(unsigned int row, unsigned int column, int value);
	void setProjectNum(unsigned int projectNum_);
	bool cellInRes(unsigned int row, unsigned int column, vector<Coord> result);
	void computeShape();
	float getRatio() const;
	float getDensity() const;
	unsigned int getNbCells() const;
	Building_type getType() const;
	std::vector<Coord> getLeftBoundaries() const;
	void print() const;
	const std::vector<Coord>& getCases() const;

  protected:
	unsigned int projectNum;
	unsigned int rowNum;
	unsigned int columnNum;
	unsigned int extra;//Capacité pour residence et type pour utility.
	Building_type type;
	int** occupiedCells;
	std::vector<Coord> shape;
	std::vector<Coord> influenceArea;
	std::vector<Coord> leftBoundaries;
	std::vector<Coord> cases;
	float ratio;//area of a building divided by all his cases
	float density;//Density of a residentail building
	unsigned int nbCells;
};
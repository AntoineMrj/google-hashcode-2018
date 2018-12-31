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
	~Building();
	Building& operator=(Building const& buildingB);
	Building(unsigned int projectNum_, unsigned int rowNum_, unsigned int columnNum_,unsigned int extra,Building_type t);
	void assignArray(int** array);
	void buildInfluenceArea();

	int getCell(unsigned int row, unsigned int column);
	unsigned int getProjectNum() const{ return this->projectNum; }
	unsigned int getRowNum() const { return this->rowNum; }
	unsigned int getColumnNum() const { return this->columnNum; }
	unsigned int getExtra() const { return this->extra; }
	vector<Coord> getShape();
	const std::vector<Coord>& getInfluenceArea() const;
	float getRatio() ;
	float getDensity() ;
	unsigned int getNbCells() const;
	Building_type getType() const;
	const std::vector<Coord>& getCases() const;

	void setCell(unsigned int row, unsigned int column, int value);
	void setProjectNum(unsigned int projectNum_);
	bool cellInRes(unsigned int row, unsigned int column, vector<Coord> result);
	void computeShape();
	void print() const;

  protected:
	unsigned int projectNum;
	unsigned int rowNum;
	unsigned int columnNum;
	unsigned int extra;//Capacité pour residence et type pour utility.
	Building_type type;
	int** occupiedCells;
	std::vector<Coord> shape;
	std::vector<Coord> influenceArea;
	std::vector<Coord> cases;//List of all occupied cells of a building
	float ratio=-1;//area of a building divided by all his cases
	float density=-1;//Density of a residentail building
	unsigned int nbCells;

};
#pragma once

#include <vector>
#include <cmath>
#include "Building.h"
//Pré déclaration des classes pour la double inclusion

using namespace std;

/*
	Structure correspondant à une coordonée sur la map
*/
struct Coord
{
	//Constructeurs
	Coord()
	{
	}

	Coord(int row,int column)
	{
		this->row = row;
		this->column = column;
	}
	bool operator==(const Coord B)
	{
		return row==B.row && column==B.column;
	}
	int row;
	int column;
	int coordManhattanDistance(const Coord& coord);//Calcul la distance de manhattan entre 2 coords
};
bool operator<(const Coord A,const Coord B);
/*
	Structure correspondant à un building placé sur la map
*/
struct PlacedBuilding
{
	//Constructeurs
	PlacedBuilding()
	{
	}

	PlacedBuilding(Building* buildingNum)
	{
		this->buildingNum = buildingNum;
	}

	Building* buildingNum;
	Coord position;
	int manhattanDistance(const PlacedBuilding& placedBuilding);//Calcul la distance de manhatan
};

class City {
public:
	City();
	City(unsigned int h,unsigned int w);
	bool placeBuilding(Building* building,unsigned int row,unsigned int col);

	void setMapCell(int row, int col, int value);
	int getMapCell(int row, int col);
private:
	unsigned int width;
	unsigned int height;
	int** map;
	//Placed building, index sur les bâtiments posés
	vector<PlacedBuilding> placedBuildingRegister;
	vector<PlacedBuilding*> registeredUtilities;
	vector<PlacedBuilding*> registeredResidentials;
};
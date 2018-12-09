#pragma once
#include <vector>

//Pré déclaration des classes pour la double inclusion
class Project;
class Building;
class Residential;
class Utility;

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

	Coord(unsigned int x, unsigned int y)
	{
		this->row = x;
		this->column = y;
	}

	unsigned int row;
	unsigned int column;
	Coord coordManhattanDistance(const Coord& coord);//Calcul la distance de manhattan entre 2 coords
};

/*
	Structure correspondant à un building placé sur la map
*/
struct PlacedBuilding
{
	//Constructeurs
	PlacedBuilding()
	{
	}

	PlacedBuilding(unsigned int buildingNum)
	{
		this->buildingNum = buildingNum;
	}

	unsigned int buildingNum;
	Coord position;
	Coord manhattanDistance(const PlacedBuilding& placedBuilding);//Calcul la distance de manhatan
	Utility* getSourceAsUtility();//Retourne le batiment lié en tant que utility
	Residential* getSourceAsResidential();//Pareil mais différent
};

class City {
public:
	City();
	City(unsigned int h,unsigned int w);
	bool placeBuilding(Building building, int x, int y);
	void setMapCell(int x, int y, int value);
	int getMapCell(int x, int y);
private:
	unsigned int width;
	unsigned int height;
	unsigned int** map;
	//Placed building, index sur les bâtiments posés
	vector<PlacedBuilding> placedBuildingRegister;
	vector<unsigned int> registeredUtilities;
	vector<unsigned int> registeredResidentials;

};
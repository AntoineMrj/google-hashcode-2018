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

	Coord(int row, int column)
	{
		this->row = row;
		this->column = column;
	}

	int row;
	int column;
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

	PlacedBuilding(Building* buildingNum)
	{
		this->buildingNum = buildingNum;
	}

	Building* buildingNum;
	Coord position;
	Coord manhattanDistance(const PlacedBuilding& placedBuilding);//Calcul la distance de manhatan
	Utility* getSourceAsUtility();//Retourne le batiment lié en tant que utility
	Residential* getSourceAsResidential();//Pareil mais différent
};

class City {
public:
	City();
	City(unsigned int h,unsigned int w);
	void operator()(Residential* R);
	void operator()(Utility* U);
	bool placeBuilding(Building* building, int row, int col);
	void placeBuildingType(Residential* R);
	void placeBuildingType(Utility *U);

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
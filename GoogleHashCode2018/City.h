#pragma once

#include <vector>
#include <cmath>
#include "Building.h"
#include <map>
#include <fstream>
//Pré déclaration des classes pour la double inclusion
class Placer;
using namespace std;

/*
	Structure correspondant à une coordonée sur la map
*/
//Forward declaration
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
	int row;
	int column;
	int coordManhattanDistance(const Coord& coord);//Calcul la distance de manhattan entre 2 coords
};
Coord operator+(const Coord& A,const Coord& B);
bool operator==(const Coord& A,const Coord& B);
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

	PlacedBuilding(Building* buildingNum);
	PlacedBuilding(const PlacedBuilding& P);
	PlacedBuilding(PlacedBuilding& P,Coord C={0,0});
	//Uniquement utilisable par un residential
	int use(unsigned int utilityType);
	std::map<unsigned int,bool> connectedUtility;
	Building* source;
	Coord position;
	int accumulatedScore;
	int manhattanDistance(const PlacedBuilding& placedBuilding);//Calcul la distance de manhatan
};

class City {
public:
	friend class Placer;
	City();
	City(unsigned int h,unsigned int w);
	City(City& c);
	virtual City& operator=(City& c);
	City(unsigned int h,unsigned w,City& c,unsigned int row,unsigned int col);
	~City();
	bool placeMap(City& c,unsigned int row,unsigned int col);
	double placeBuilding(Building* building,unsigned int row,unsigned int col,bool test=false);
	void setMapCell(int row, int col, int value);
	int getMapCell(int row, int col);
	int computeScore(PlacedBuilding& A,PlacedBuilding& B);
	int getScore();
	int getRemainingCell();
	void setScore(int score);
	void PrintMap();
	void toSolution(string outfileName);
	unsigned int getCityWidth() { return width; }
	unsigned int getCityHeight() { return height; }
	set<Coord> getRemainingCellsList();
	std::vector<std::set<Coord>> getConnexComposant();
private:
	unsigned int width;
	unsigned int height;
	int** map;
	int score;
	bool connexInit = false;
	//Placed building, index sur les bâtiments posés
	std::map<int, std::set<Coord>> ConnexComposant;
	int **connexMap;
	vector<PlacedBuilding> placedBuildingRegister;
	vector<PlacedBuilding*> registeredUtilities;
	vector<PlacedBuilding*> registeredResidentials;
	set<Coord> RemainingCellsList;
};
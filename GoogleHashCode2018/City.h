#pragma once
#include <vector>

//Pré déclaration des classes pour la double inclusion
class Project;
class Building;
class Residential;
class Utility;

using namespace std;

struct Coord
{
	//CREER LE CONSTRUCTUER

	unsigned int row;
	unsigned int column;
	Coord coordManhattanDistance(const Coord& C);//Calcul la distance de manhattan entre 2 coords
};

struct PlacedBuilding
{
	//CREER LE CONSTRUCTUER
	unsigned int source;
	Coord position;
	Coord manhattanDistance(const PlacedBuilding& P);//Calcul la distance de manhatan
	Utility* getSourceAsUtility();//Retourne le batiment lié en tant que utility
	Residential* getSourceAsResidential();//Pareil mais différent
	//Passer par le projet static

};

class City {
public:
	City();
	City(unsigned int h,unsigned int w);
	//Renvoit vrai si c'était possible
	//Renvoit faux sinon
	bool placedBuilding(PlacedBuilding P);//Place un batiment sur la carte et l'ajoute au registe
	void setMapCell(int x, int y, int value);
	int getMapCell(int x, int y);
private:
	unsigned int width;
	unsigned int height;
	unsigned int** map;
	vector<PlacedBuilding> placedBuildingRegister;
	//Placed building
	//Index sur les bâtiments posés.
	vector<unsigned int> registeredUtilities;
	vector<unsigned int> registeredResidentials;

};
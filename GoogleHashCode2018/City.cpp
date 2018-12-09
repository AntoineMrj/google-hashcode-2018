#include"City.h"
#include "Project.h"

City::City() {
}

City::City(unsigned int w, unsigned int h)
{
	int width = w;
	int height = h;
	map = new unsigned int *[w]; // Type de la varibale map � modifier
	for (int a = 0; a < w; a++) {
	map[a] = new unsigned int[h];
	}
	for (unsigned int i = 0; i < h; i++) {
		for (unsigned int j = 0; j < h; j++)
		{
			map[i][j] = 0;
		}
	}
}

/*
	Place un building sur la carte
	@return true si placement du building possible, sinon faux
*/
bool City::placeBuilding(Building building, int x, int y) {
	if (this->getMapCell(x, y) == -1)
	{
		// On check les cellules que prend le building
		for (int row = 0; row < building.getRowNum(); row++)
		{
			for (int col = 0; col < building.getcolumnNum(); col++)
			{
				if (building.getCell(col, row) == 1)
				{
					// On met le numéro du building sur les cases qu'il prend sur la map
					this->setMapCell(x + row, y + col, building.getProjectNum());
				}
			}
		}
		PlacedBuilding placedBuilding = PlacedBuilding(building.getProjectNum());
		placedBuilding.position = Coord(x, y);
		placedBuildingRegister.push_back(placedBuilding);
		return true;
	}
	else
	{
		return false;
	}
}

/*
	Modifie la valeur de la case de la map passée en paramètre
*/
void City::setMapCell(int x, int y, int value)
{
	this->map[x][y] = value;
}

/*
	Retourne la valeur de la case de la map passée en paramètre
*/
int City::getMapCell(int x, int y)
{
	return this->map[x][y];
}

Coord PlacedBuilding::manhattanDistance(const PlacedBuilding & P)
{
	//TODO
	return Coord();
}

Utility * PlacedBuilding::getSourceAsUtility()
{
	//TODO
	return nullptr;
}

Residential * PlacedBuilding::getSourceAsResidential()
{
	//TODO
	return nullptr;
}

Coord Coord::coordManhattanDistance(const Coord & C)
{
	//TODO
	return Coord();
}

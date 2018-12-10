#include"City.h"
#include "Project.h"

City::City() {
}

City::City(unsigned int w, unsigned int h)
{
	this->width = w;
	this->height = h;
	map = new int *[w]; // Type de la varibale map à modifier
	for (unsigned int a = 0; a < w; a++) {
	map[a] = new int[h];
	}
	for (unsigned int i = 0; i < h; i++) {
		for (unsigned int j = 0; j < h; j++)
		{
			map[i][j] = -1;
		}
	}
}

/*
	Place a building on the map
	@return true if it's possible, otherwise false
*/
bool City::placeBuilding(Building* building,unsigned int row,unsigned int col) {
	int num = this->placedBuildingRegister.size();
	unsigned int row_temp;
	unsigned int col_temp;
	bool stop = false;
	// On check les cellules que prend le building
	for (row_temp = row; row < row + building->getRowNum() && !stop; row++)
	{
		for (col_temp = col; col_temp < col_temp + building->getColumnNum() && !stop; col_temp++)
		{
			if (building->getCell(row_temp - row, col_temp - col) == 1)
			{
				//Cas du chevauchement
				if(this->getMapCell(row, col) != -1)
				{
					stop = true;
					break;
				}
				// On met le numéro du building sur les cases qu'il prend sur la map
				this->setMapCell(row_temp, col_temp, num);
			}
		}
		if(stop)
			break;
	}
	if(!stop)
	{
		PlacedBuilding placedBuilding = PlacedBuilding(building);
		placedBuilding.position = Coord(row, col);
		placedBuildingRegister.push_back(placedBuilding);
		switch(building->getType())
		{
			case Building_type::Residential:
				registeredResidentials.push_back(&placedBuildingRegister.back());
				break;
			case Building_type::Utility :
				registeredUtilities.push_back(&placedBuildingRegister.back());
				break;
		}
		return true;
	}
	else
	{
		// Annulation du placement
		unsigned int row_recover = row_temp--;
		unsigned int col_recover = col_temp--;
		for (; row_recover > row; row_recover--)
		{
			for (; col_recover > col; col_recover--)
			{
				if(this->getMapCell(row_recover, col_recover) == num)
					this->setMapCell(row_recover, col_recover, -1);
			}
			col_recover = col + building->getColumnNum();
		}
		return false;
	}
}


/*
	Modify the value of the map's cell in parameter
*/
void City::setMapCell(int x, int y, int value)
{
	this->map[x][y] = value;
}

/*
	Return the value of the map's cell in parameter
*/
int City::getMapCell(int x, int y)
{
	return this->map[x][y];
}

int PlacedBuilding::manhattanDistance(const PlacedBuilding & placedBuilding)
{
	//TODO
	return 0;
}


/*
	Return Manhattan distance between 2 Coord objects
*/
int Coord::coordManhattanDistance(const Coord & coord)
{
	return abs(int(coord.row) - int(this->row)) + abs(int(coord.column) - int(this->column));
}

bool operator<(const Coord A, const Coord B)
{
	if (A.column < B.column)
	{
		return true;
	}
	else if (A.column > B.column)
	{
		return false;
	}
	else
	{
		if (A.row < B.column)
			return true;
		else
			return false;
	}
}
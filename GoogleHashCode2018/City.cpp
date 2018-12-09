#include"City.h"
#include "Project.h"

City::City() {
}

City::City(unsigned int w, unsigned int h)
{
	this->width = w;
	this->height = h;
	map = new int *[w]; // Type de la varibale map � modifier
	for (int a = 0; a < w; a++) {
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
	Place un building sur la carte
	@return true si placement du building possible, sinon faux
*/
bool City::placeBuilding(Building* building, int col, int row) {
		int num = this->placedBuildingRegister.size();
		int row_temp;
		int col_temp;
		bool stop = false;
		// On check les cellules que prend le building
		for (row_temp=row;row < row+building->getRowNum() && !stop; row++)
		{
			for (col_temp=col; col_temp < col_temp+building->getcolumnNum() && !stop; col_temp++)
			{
				if (building->getCell(col_temp-col, row_temp-row) == 1)
				{
					//Cas du chevauchement
					if(this->getMapCell(col,row)!=-1)
					{
						stop=true;
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
			placedBuilding.position = Coord(col, row);
			placedBuildingRegister.push_back(placedBuilding);
			building->placeInCity(*this);
			return true;
		}
		else
		{
			// Annulation du placement
			int row_recover=row_temp--;
			int col_recover=col_temp--;
			for (; row_recover > row; row_recover--)
			{
				for (; col_recover > col; col_recover--)
				{
					if(this->getMapCell(row_recover,col_recover)==num)
						this->setMapCell(row_recover, col_recover, -1);
				}
				col_recover=col+building->getcolumnNum();
			}
			return false;
		}

}
void City::placeBuildingType(Residential *R)
{
	registeredResidentials.push_back(&placedBuildingRegister.back());
}
void City::placeBuildingType(Utility *U)
{
	registeredUtilities.push_back(&placedBuildingRegister.back());
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

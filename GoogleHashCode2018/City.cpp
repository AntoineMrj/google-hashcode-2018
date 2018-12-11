#include"City.h"
#include "Project.h"




PlacedBuilding::PlacedBuilding(Building*buildingNum)
{
	this->source = buildingNum;
	accumulatedScore = 0;
	if (buildingNum->getType() == Residential)
	{
		connectedUtility = new std::map<unsigned int, bool>();
		for (unsigned int i : Project::globalProject.UtilitiesReferences)
		{
			(*connectedUtility)[i] = false;
		}
	}
}
int PlacedBuilding::use(unsigned int utilityType)
{
	if ((*connectedUtility)[utilityType] == false)
	{
		(*connectedUtility)[utilityType] = true;
		accumulatedScore += source->getExtra();
		return source->getExtra();
	}
	return 0;
}



City::City() {
}

City::City(unsigned int w, unsigned int h)
{
	this->width = w;
	this->height = h;
	map = new int *[h]; // Type de la varibale map à modifier
	for (unsigned int a = 0; a < h; a++) {
	map[a] = new int[w];
	}
	for (unsigned int i = 0; i < h; i++) {
		for (unsigned int j = 0; j < w; j++)
		{
			map[i][j] = -1;
		}
	}
	score = 0;
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
	for (row_temp = row; row_temp < row + building->getRowNum() && !stop; row_temp++)
	{
		for (col_temp = col; col_temp < col + building->getColumnNum() && !stop; col_temp++)
		{
			if(row_temp>=height||col_temp>=width)
			{
				stop=true;
				break;
			}
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
		//Calcul du score généré par le placement
		for (auto coord : placedBuilding.source->getInfluenceArea())
		{
			Coord temp_coord = {coord.row+int(row),coord.column+int(col)};
			if(temp_coord.row>=0&&temp_coord.row<int(height)&&temp_coord.column>=0&&temp_coord.column<int(width))
			{
				score += computeScore(placedBuildingRegister.back(), placedBuildingRegister[getMapCell(temp_coord.row, temp_coord.column)]);
			}
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

int City::computeScore(PlacedBuilding &A,PlacedBuilding &B)
{
	switch(A.source->getType())
	{
		case Utility:
			switch(B.source->getType())
			{
				case Residential:
					return B.use(A.source->getExtra());
				break;
				default:
					return 0;
				break;
			}
		break;
		case Residential:
			switch (B.source->getType())
			{
			case Utility:
				return A.use(B.source->getExtra());
				break;
			default:
				return 0;
				break;
			}
			break;
	}
	return 0;
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

int City::getScore()
{
	return score;
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
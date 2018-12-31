#include"City.h"
#include "Project.h"

PlacedBuilding::PlacedBuilding(const PlacedBuilding &P)
{
	position = P.position;
	if(P.source->getType()==Residential)
	{
		connectedUtility = new std::map<unsigned int, bool>();
		for (auto pair : *(P.connectedUtility))
		{
			(*connectedUtility)[pair.first] = (pair.second);
		}
	}
	source = P.source;
	accumulatedScore = P.accumulatedScore;
}
	PlacedBuilding::PlacedBuilding(Building *buildingNum)
{
	this->source = buildingNum;
	accumulatedScore = 0;
	if (buildingNum->getType() == Residential)
	{
		connectedUtility = new std::map<unsigned int, bool>();
		for (auto i : Project::globalProject.utilities)
		{
			(*connectedUtility)[i.first] = false;
		}
	}
}
PlacedBuilding::PlacedBuilding(PlacedBuilding &P, Coord C)
{
	position = P.position + C;
	if (P.source->getType() == Residential)
	{
		connectedUtility = new std::map<unsigned int, bool>();
		for (auto pair : *(P.connectedUtility))
		{
			(*connectedUtility)[pair.first] = (pair.second);
		}
	}
	source = P.source;
	accumulatedScore = P.accumulatedScore;
}
/**
 * @brief
 * Test if a utility type is already use by a residential
 * In this case we return a score equal to the extra of the residential
 * 	and set this utility type as use for this placed building
 * Else we return 0
 * @param utilityType
 * @return int Score generated by the use of this utility type
 */
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
	for (unsigned int i = 0; i < getCityHeight(); i++)
	{
		for (unsigned int j = 0; j < getCityWidth(); j++)
		{
			RemainingCellsList.insert({i, j});
		}
	}
	score = 0;
}
/**
 * @brief Construct a new City:: City object
 * Copy constructor
 * @param c 
 */
City::City(City& c)
{
	width=c.width;
	height=c.height;
	map=new int*[height];
	for(unsigned int a=0;a<height;a++)
		map[a]=new int[width];
	RemainingCellsList = c.RemainingCellsList;
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			map[i][j] = c.map[i][j];
		}
	}
	for (PlacedBuilding P : c.placedBuildingRegister)
	{
		placedBuildingRegister.push_back(P);
		switch (P.source->getType())
		{
		case Residential:
			registeredResidentials.push_back(&placedBuildingRegister.back());
			break;
		case Utility:
			registeredUtilities.push_back(&placedBuildingRegister.back());
			break;
		}
	}
	score = c.score;
}
/**
 * @brief
 * Assignation operator
 * @param c 
 * @return City&
 */
City& City::operator=(City& c)
{
	width = c.width;
	height = c.height;
	map = new int *[height];
	for (unsigned int a = 0; a < height; a++)
		map[a] = new int[width];
	RemainingCellsList = c.RemainingCellsList;
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			map[i][j] = c.map[i][j];
		}
	}
	for(PlacedBuilding P:c.placedBuildingRegister)
	{
		placedBuildingRegister.push_back(P);
		switch(P.source->getType())
		{
			case Residential:
				registeredResidentials.push_back(&placedBuildingRegister.back());
			break;
			case Utility:
				registeredUtilities.push_back(&placedBuildingRegister.back());
				break;
		}
	}
	score = c.score;
	return *this;
}
/**
 * @brief Construct a new City object from an other
 *
 * @param h
 * @param w
 * @param c 
 * @param row
 * @param col 
 */
City::City(unsigned int h, unsigned w, City& c, unsigned int row, unsigned int col)
{
	this->width = w;
	this->height = h;
	map = new int *[h]; // Type de la varibale map à modifier
	for (unsigned int a = 0; a < h; a++)
	{
		map[a] = new int[w];
	}
	placeMap(c,row,col);
}
/**
 * @brief
 * Insert a city in an other bigger
 * @param c
 * @param row 
 * @param col
 * @return true
 * @return false
 */
bool City::placeMap(City &c, unsigned int row, unsigned int col)
{
	for (PlacedBuilding P : c.placedBuildingRegister)
	{
		if(!placeBuilding(P.source,P.position.row+row,P.position.column+col))
			return false;
	}
}
	/*
	Place a building on the map
	The try argument determine if it's just a test of placement instead of a placing.
	@return the coverage ration of the building
	if it's 0, this mean an error occured,
	else the closest it is from 1, the more the placement is optimized.
*/
double City::placeBuilding(Building *building, unsigned int row, unsigned int col, bool test)
{
	int num = this->placedBuildingRegister.size();
	unsigned int row_temp;
	unsigned int col_temp;
	//Unité de mesure du placement
	double coverage = 0;
	int maxCoverage = building->getColumnNum() * building->getRowNum();
	bool stop = false;
	// On check les cellules que prend le building
	if(building->getColumnNum()+col<=width && building->getRowNum()+row<=height)
	{
		for(auto &c : building->getCases())
		{
			if (this->getMapCell(c.row+row, c.column+col) != -1)
			{
				return 0;
				//Cas du chevauchement
			}
		}
	}
	else
	{
		return 0;
	}
	for (auto &c : building->getCases())
	{
			if(connexInit)
			{
				ConnexComposant[connexMap[c.row + row][c.column + col]].erase({c.row + row, c.column + col});
			}
			RemainingCellsList.erase({c.row+row,c.column+col});
			this->setMapCell(c.row+row, c.column+col, num);
			coverage++; //Cas du chevauchement
	}
	PlacedBuilding placedBuilding(building);
	placedBuilding.position = Coord(row, col);
	placedBuildingRegister.push_back(placedBuilding);
	switch (building->getType())
	{
	case Building_type::Residential:
		registeredResidentials.push_back(&placedBuildingRegister.back());
		break;
	case Building_type::Utility:
		registeredUtilities.push_back(&placedBuildingRegister.back());
		break;
	}
	//Calcul du score généré par le placement
	for (const Coord &coord : placedBuilding.source->getInfluenceArea())
	{
		Coord temp_coord = {coord.row + int(row), coord.column + int(col)};
		if (temp_coord.row >= 0 && temp_coord.row < int(height) && temp_coord.column >= 0 && temp_coord.column < int(width) && getMapCell(temp_coord.row, temp_coord.column) > -1 && &placedBuildingRegister[getMapCell(temp_coord.row, temp_coord.column)] != &placedBuildingRegister.back())
		{
			score += computeScore(placedBuildingRegister.back(), placedBuildingRegister[getMapCell(temp_coord.row, temp_coord.column)]);
		}
	}
	return coverage / maxCoverage;
}
/**
 * @brief
 *	return the list of remaining cells as a list of Coord.
 * @return set<Coord>
 */
set<Coord> City::getRemainingCellsList()
{
	return RemainingCellsList;
}
/**
 * @brief
 * Get and create if necessary de connex composant liste
 * Which is all cells that are in an area in which we can place a building
 * @return std::vector<std::set<Coord>> 
 */
std::vector<std::set<Coord>> City::getConnexComposant()
{
	if(!connexInit)
	{
	std::map<int, std::set<Coord>> ConnexComposant;
	int counter = 0;
	connexMap = new int*[height];
	for(int i = 0;i<height;i++)
	{
		connexMap[i] = new int[width];
		std::fill(connexMap[i],connexMap[i]+width,-1);
	}
	for(auto C : RemainingCellsList)
	{
		bool alreadyPlaced = false;
		int value = -1;
		for(int row=-1;row<=1;row++)
		{
			for(int col=-1;col<=1;col++)
			{
				if(row+int(C.row)>=0 && row+int(C.row)<height && col+int(C.column)>=0 && col+int(C.column)<width && col!=row)
				{

						int CasesVal = connexMap[row + C.row][col + C.column] ;
						if (!alreadyPlaced && CasesVal >= 0)
						{
							alreadyPlaced = true;
							value = CasesVal;
							connexMap[C.row][C.column] = CasesVal;
							ConnexComposant[value].insert({C.row,C.column});
						}
						else if (alreadyPlaced && CasesVal != value &&CasesVal>=0)
						{
							for (auto B : ConnexComposant[CasesVal])
							{
								connexMap[B.row][B.column] = value;
								ConnexComposant[value].insert(B);
								ConnexComposant[CasesVal].erase(B);
							}
							ConnexComposant.erase(CasesVal);
						}

				}
			}
		}
		if(!alreadyPlaced)
		{

			connexMap[C.row][C.column] = counter;
			ConnexComposant[counter] = std::set<Coord>();
			ConnexComposant[counter].insert(C);
			counter++;
		}
	}
	connexInit = true;
	}
	std::vector<std::set<Coord>> outVec;
	for(auto C:ConnexComposant)
	{
		if(C.second.size() >= Project::globalProject.minHeight *Project::globalProject.minWidth)
		{
			outVec.push_back(C.second);
		}
	}
	return	outVec;
}
/**
 * @brief
 * Return the number of remaining cells.
 * @return int 
 */
int City::getRemainingCell()
{
	return RemainingCellsList.size();
		}
		/**
 * @brief
 * Compute the score generated by a freshly placed building A with an other buildbing B accesible by A.
 * @param A Freshly placed building
 * @param B Building already on the map
 * @return int Score generated by the interaction between these 2 buildings.
 */
		int City::computeScore(PlacedBuilding & A, PlacedBuilding & B)
		{
			switch (A.source->getType())
			{
			case Utility:
				switch (B.source->getType())
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
/**
 * @brief
 * Print the city map in the console
 */
void City::PrintMap()
{
	for(int r = 0;r<height;r++)
	{
		for(int c=0;c<width;c++)
		{
			if(map[r][c]>=0)
				std::cout  << "#";
			else
				std::cout << ".";
		}
		std::cout << std::endl;
	}
}


/*
	Save the city into a file
*/
 void City::toSolution(string outfileName)
 {
	 std::ofstream outfile(outfileName);
	 outfile << placedBuildingRegister.size() << std::endl;
	 for (int i = 0; i < placedBuildingRegister.size(); i++)
	 {
		 outfile << placedBuildingRegister.at(i).source->getProjectNum() << " " << placedBuildingRegister.at(i).position.row << " " << placedBuildingRegister.at(i).position.column << std::endl;
	 }
	 outfile.close();
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
/**
 * @brief
 * Return the current socre of the city.
 * @return int 
 */
int City::getScore()
{
	return score;
}
/**
 * @brief
 * Set the score of the city
 * @param score Score to set
 */
void City::setScore(int score)
{
	this->score = score;
}
/*
	Return Manhattan distance between 2 Coord objects
*/
int Coord::coordManhattanDistance(const Coord & coord)
{
	return abs(int(coord.row) - int(this->row)) + abs(int(coord.column) - int(this->column));
}


Coord operator+(const Coord& A,const Coord& B)
{
	return {A.row+B.row,A.column+B.column};
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
		if (A.row < B.row)
			return true;
		else
			return false;
	}
}
bool operator==(const Coord &A, const Coord &B)
{
	return A.row == B.row && A.column == B.column;
}
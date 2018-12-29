#include "Placer.h"


Placer::Placer(City* source)
{
	src = source;
	for(int i = 0;i<source->getCityHeight();i++)
	{
		ColRegister.push_back(source->getCityWidth());
	}
	lastCoord=0;
	registerFrequency=1000;
	actualPlacement=0;
	lastMaxRowPlacement=0;
	lastMinRowPlacement=10001;
	for(int i = 0;i<source->getCityHeight();i++)
		shuffleCoord.push_back(i);
	for (int i = 0; i < source->getCityWidth(); i++)
		shuffleCoordCol.push_back(i);
		shuffle();
}

bool Placer::tetrisPlacement(Building *b)
{
	for (int row = src->height - b->getRowNum(); row >= 0; row--)
	{
		if(ColRegister[row]>-1)
		{
			for (int col = ColRegister[row]- b->getColumnNum(); col >= 0; col--)
			{
				if (src->placeBuilding(b, row, col))
				{
					actualPlacement++;
					if(lastMaxRowPlacement<row+b->getRowNum())
						lastMaxRowPlacement=row;
					if(lastMinRowPlacement>row)
						lastMinRowPlacement=row;
					if(actualPlacement>=registerFrequency)
					{
						actualPlacement=0;
						buildRegister();
					}
					return true;
				}
			}
		}
	}
	return false;
}
void Placer::buildRegister()
{
	for (int i = 0; i < src->getCityHeight(); i++)
	{
		bool hasStarted = false;
		int previous = ColRegister[i];
		int begin = src->getCityWidth()-1;
		int end = src->getCityWidth() - 1;
		for (int j = lastMaxRowPlacement; j >= lastMinRowPlacement; j--)
		{
			if(!hasStarted && src->getMapCell(i,j)<0)
			{
				hasStarted  =true;
				begin = j;
			}
			if(hasStarted && src->getMapCell(i,j)>=0)
			{
				if(begin-j-1>Project::globalProject.minWidth)
				{
					hasStarted = false;
					ColRegister[i] = begin;
					break;
				}
				else
				{
					hasStarted = false;
				}
			}
		}
		if(hasStarted)
		{
			if (begin > Project::globalProject.minWidth)
				ColRegister[i] = begin;
			else
				ColRegister[i] = -1;
		}
	}
	lastMaxRowPlacement = 0;
	lastMinRowPlacement = 10001;
}
bool Placer::tetrisPlacementTOP(Building *b)
{
	for (int row = 0; row <= src->height - b->getRowNum(); row++)
	{
		for (int col = ColRegister[row] - b->getColumnNum(); col >= 0; col--)
		{
			if (src->placeBuilding(b, row, col))
			{
				actualPlacement++;
				if (lastMaxRowPlacement < row + b->getRowNum())
					lastMaxRowPlacement = row;
				if (lastMinRowPlacement > row)
					lastMinRowPlacement = row;
				if (actualPlacement >= registerFrequency)
				{
					actualPlacement = 0;
					buildRegister();
				}
				return true;
			}
		}
	}
	return false;
}

bool Placer::tetrisAleat(Building* b)
{
	for(int row : shuffleCoord)
	{
		for(int col : shuffleCoordCol)
		{
		//	std::cout << "\nB";
		//	std::cout << row << "," << col << std::endl;
			if (src->placeBuilding(b, row, col))
			{
		//		std::cout << "FOUND" << std::endl;
				actualPlacement++;
				if (actualPlacement >= registerFrequency)
				{
		//			std::cout << "SHUFFLE" << std::endl;
					actualPlacement = 0;
					shuffle();
				}

				return true;

			}
		//	std::cout << "\nA\n";
		}
	}
	return false;
}
bool Placer::lastPlacement(Building*b)
{
	if(CoordRegister.size()==0)
		reload();
	int end = CoordRegister.size();
	for(auto C : src->getRemainingCellsList())
	{
		//Coord C = CoordRegister[i];
		if (src->placeBuilding(b, C.row, C.column))
		{
			actualPlacement++;
			if (actualPlacement >= registerFrequency)
			{
				//			std::cout << "SHUFFLE" << std::endl;
				actualPlacement = 0;
				//reload();
			}
			return true;
		}
	}
	return false;
}
void Placer::reload()
{
	CoordRegister.clear();
	lastCoord = 0;
	for(auto C : src->getRemainingCellsList())
		CoordRegister.push_back(C);
	std::random_shuffle(CoordRegister.begin(), CoordRegister.end());
}
void Placer::shuffle()
{
	std::random_shuffle(shuffleCoord.begin(), shuffleCoord.end());
	std::random_shuffle(shuffleCoordCol.begin(), shuffleCoordCol.end());
}
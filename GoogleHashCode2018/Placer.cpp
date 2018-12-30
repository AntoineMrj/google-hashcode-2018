#include "Placer.h"


Placer::Placer(City* source)
{
	src = source;
	for(int i = 0;i<source->getCityHeight();i++)
	{
		ColRegister.push_back(source->getCityWidth());
	}
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
/**
 * @brief
 * Placement from the bottom right corner
 * @param b 
 * @return true 
 * @return false 
 */
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
/**
 * @brief
 *Construct the lines register
 */
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
/**
 * @brief
 * Placement from the top right corner
 * @param b 
 * @return true 
 * @return false 
 */
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
/**
 * @brief
 * Place on a random coordinante.
 * @param b 
 * @return true 
 * @return false 
 */
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
/**
 * @brief
 * Placement using only the connex composant.
 * @param b 
 * @return true 
 * @return false 
 */
bool Placer::ConvexPlacement(Building *b)
{
	for (auto CList: src->getConnexComposant())
	{
		for(auto C : CList)
		{
			if (src->placeBuilding(b, C.row, C.column))
			{
				return true;
			}
		}
	}

	return false;
}
/**
 * @brief
 * Shffule the coordinates array.
 */
void Placer::shuffle()
{
	std::random_shuffle(shuffleCoord.begin(), shuffleCoord.end());
	std::random_shuffle(shuffleCoordCol.begin(), shuffleCoordCol.end());
}
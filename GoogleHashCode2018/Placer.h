#pragma once
#include "City.h"
#include "Project.h"
#include <algorithm>
#include <random>
#include <unordered_set>
/**
 * @brief
 * Class used to place building in a tetris way.
 */
class Placer
{
  public:
	Placer(City *source);
	bool tetrisPlacement(Building *b);
	bool tetrisPlacementTOP(Building *b);
	bool tetrisAleat(Building *b);
	bool ConvexPlacement(Building* b);
	void buildRegister();
	void shuffle();

  private:
	City *src;//City in which we want to place building
	int registerFrequency;//Frequency to update the line register.
	int actualPlacement;//Number of placement since the last buildRegister
	int lastMaxRowPlacement;//Maximum coordinate of the last placement
	int lastMinRowPlacement;//Miniminum coordinate of the last placement

	std::vector<int> shuffleCoord;//Shuffled coordinates arrays
	std::vector<int> shuffleCoordCol;
	std::vector<int> ColRegister;
};
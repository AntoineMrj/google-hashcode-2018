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
		Placer(City* source);
		bool tetrisPlacement(Building *b);
		bool tetrisPlacementTOP(Building *b);
		bool tetrisAleat(Building *b);
		bool lastPlacement(Building*b);
		void buildRegister();
		void shuffle();
		void reload();
	  private:
		City* src;
		int registerFrequency;
		int actualPlacement;
		int lastMaxRowPlacement;
		int lastMinRowPlacement;
		int lastCoord;
		std::vector<int> shuffleCoord;
		std::vector<int> shuffleCoordCol;

		std::vector<int> ColRegister;
		std::default_random_engine rng = std::default_random_engine();
		std::vector<Coord> CoordRegister;
};
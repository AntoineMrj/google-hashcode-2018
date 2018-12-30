#pragma once
#include "Chooser.h"
#include "Placer.h"
#include <vector>
#include <functional>
#include <tuple>
class Solver
{
public:
	static void Solve(City* city);//Method use to fill a city with building
	~Solver();
};


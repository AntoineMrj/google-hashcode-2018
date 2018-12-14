#include "Solver.h"
#include <stdlib.h>

Solver::Solver(Project project)
{
	/*
	unsigned int x, y;
	unsigned int x_tmp, y_tmp;
	PlacedBuilding B_tmp, A;
	int score_max = -1;
	int score_tot = 0;
	int score = 0;
	size_t c = 0;

	for (Building *B : project.buildings)
	{
		while (c != 10) // on essaie 10 position différentes
		{
			x_tmp = rand() % (project.city->getCityHeight()-1) + 0;
			y_tmp = rand() % (project.city->getCityWidth()-1) + 0;
			
			project.city->placeBuilding(B, x_tmp, y_tmp, true);
			B_tmp = B;

			if ((score = project.city->computeScore(B_tmp, A)) > score_max) {
				x = x_tmp;
				y = y_tmp;
				score_max = score;
			}
			c++;
		}
		project.city->placeBuilding(B, x, y, false);
		score_tot += score_max;
		project.city->setScore(score_tot);
		A = B;
	}*/
	std::cout << project.city->placeBuilding(project.buildings.at(0), 0, 0) << std::endl;
	std::cout << project.city->placeBuilding(project.buildings.at(0), 0, 2) << std::endl;
	std::cout << project.city->placeBuilding(project.buildings.at(2), 0, 4) << std::endl;
	std::cout << project.city->placeBuilding(project.buildings.at(2), 2, 4) << std::endl;
	std::cout << project.city->placeBuilding(project.buildings.at(1), 3, 0) << std::endl;
}


Solver::~Solver()
{
}

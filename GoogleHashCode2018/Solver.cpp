#include "Solver.h"
#include <stdlib.h>
#include <time.h>

Solver::Solver(Project project)
{
	unsigned int x, y;
	unsigned int x_tmp, y_tmp;
	PlacedBuilding B_tmp, A;
	int score_max_building = -1;
	int score_tot = 0;
	int score = 0;
	size_t c = 0;
	bool first = true;

	srand(time(NULL));

	for (Building *B : project.buildings)
	{
		if (first) {
			project.city->placeBuilding(B, 0, 0, false);
			first = false;
		}
		else {
			B_tmp = B;
			while (c != 10) // on essaie 10 positions différentes
			{
				x_tmp = rand() % project.city->getCityHeight();
				y_tmp = rand() % project.city->getCityWidth();

				project.city->placeBuilding(B, x_tmp, y_tmp, true);
				score = project.city->computeScore(B_tmp, A);

				if (score > score_max_building) {
					x = x_tmp;
					y = y_tmp;
					score_max_building = score;
				}
				c++;
			}
			project.city->placeBuilding(B, x, y, false);
			score_tot += score_max_building;
			project.city->setScore(score_tot);
			score_max_building = -1;
			c = 0;
		}
		A = B;
	}
}


Solver::~Solver()
{
}

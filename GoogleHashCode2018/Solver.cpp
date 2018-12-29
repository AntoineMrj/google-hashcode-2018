#include "Solver.h"

void Solver::Solve(City* city)
{
	Chooser c(0.7,0.5,0.5,0.5,&Project::globalProject);
	Placer p(city);
	Building* b;
	//threshold for each placement type
	//Placement from the top
	int seuil = (city->getCityHeight() * city->getCityWidth())*0.5;
	//Random placement
	int seuilMIN = seuil*0.5;
	//Placement with last cells
	int seuilShuffle = seuilMIN*0.8;
	//Count of placement
	int actualPlacement=0;
	//Threslhold for reinitialising the chooser
	int reinitSeuil = 1;
	while ((b = c.get()) != nullptr && city->getRemainingCell()>seuilShuffle)
	{
		//Placement from the right bottom
		if(city->getRemainingCell()>seuil)
		{
		if(p.tetrisPlacement(b))
		{
			actualPlacement++;
			if (actualPlacement > reinitSeuil)
			{
				c.refill();
				c.initialize();
				actualPlacement = 0;
			}
			else
			{
				c.refill();
			}
		}
		}
		//Placement from the right top corner
		else if(city->getRemainingCell()>seuilMIN)
		{

			if (p.tetrisPlacementTOP(b))
			{
				actualPlacement++;
				if(actualPlacement>reinitSeuil)
				{
					c.refill();
					c.initialize();
					actualPlacement=0;
				}
				else
				{
				c.refill();
				}
			}
		}
		//Random placement
		else if (city->getRemainingCell() > seuilShuffle)
		{
			if (p.tetrisAleat(b))
			{

				actualPlacement++;
				if (actualPlacement > reinitSeuil)
				{
					c.refill();
					c.initialize();
					actualPlacement = 0;
				}
				else
				{
					c.refill();
				}
			}
		}
	}
	c.refill();
	c.initialize();
	while ((b = c.getEnd()) != nullptr)
	{
			//Placement in function of the last remaining cells.
			if (p.lastPlacement(b))
			{
				actualPlacement++;
				if (actualPlacement > reinitSeuil)
				{
					c.refillEnd();
					c.initialize();
					actualPlacement = 0;
				}
				else
				{
					c.refillEnd();
				}
			}

	}
}


Solver::~Solver()
{
}

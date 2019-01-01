#include "Solver.h"
using namespace std;
void Solver::Solve(City* city)
{
	/**
	 * Solver using a combination of a chooser and a placer to optimize placement on city
	 * Work in a raisonable time for small cities.
	 *
	 * The chooser is use to sort and find building using random generated list.
	 * The placer is use in 5 ways to optimize calculus time.
	 *
	 */
	/**
	 * Type : probabilty to choose a type
	 * 		High : more probability to choose a residential
	 * 		Low : more probabilitu to choose an utility
	 * U : probability of choosing an utility
	 * 		High : more probabilityu to choose a small utility
	 * 		Low : more probability to choose a big utility
	 * UT : probability of choosing a type of utility
	 * 		High : more probability of choosing most represented utility
	 * 		Low : more probability of choosing a less represented utility
	 * R : probability of choosing an residential
	 * 		High : more probabilityu to choose a small residential
	 * 		Low : more probability to choose a big residential
	 */
	double Type = 0.3;
	double U = 0.8;
	double UT = 0.95;
	double R = 0.3;
	Chooser c(Type,U,UT,R,&Project::globalProject);
	Placer p(city);
	Building* b;
	//threshold for each placement type
	//Placement from the top
	/**int seuil = (city->getCityHeight() * city->getCityWidth())*0.5;
	//Random placement
	int seuilMIN = seuil*0.7;
	//Placement with last cells
	int seuilShuffle = seuilMIN*0.1;
	int seuilEnd = seuilShuffle*0.8;**/
	//Count of placement
	int actualPlacement=0;
	//Threslhold for reinitialising the chooser
	int reinitSeuil = 10;
	//DEFINING PLACEMENT FUNCTION
	auto bottomRightPlacement = [](Building* b,Placer* p)->bool{
		return p->tetrisPlacement(b);
	};
	auto topRightPlacement = [](Building *b, Placer *p) -> bool {
		return p->tetrisPlacementTOP(b);
	};
	auto aleatPlacement = [](Building *b, Placer *p) -> bool {
		return p->tetrisAleat(b);
	};
	auto convexPlacement = [](Building* b,Placer* p) -> bool {
		return p->tetrisPlacementTOP(b);
	};
	//DEFINING CHOOSER GET METHOD
	auto baseGet = [](Chooser* c)->Building*
	{
		return c->get();
	};
	auto endGet = [](Chooser* c) -> Building * {
		return c->getEnd();
	};
	//DEFINING TYPE OF A COMPUTING STEP
	using placementGetPair = tuple<function<bool(Building *, Placer *)>,
			 function<Building *(Chooser*)>,double,string>;

	vector<placementGetPair> placements;
	unsigned int lastPlacement = 0;
	double seuil = (city->getCityHeight() * city->getCityWidth());
	//FILLING PLACEMENTS STEPS
	/**
	 * Tuple explaination :
	 * 		Placement method
	 * 		Chooser method
	 *		Threshold to the next step, if the current number of remaining cells
	 *		 	if inferior to the Threshold defined by the next step
				go to the next step
	 */
	placementGetPair actualP;
	placements.push_back({bottomRightPlacement,baseGet,1,"BOTTOM RIGHT,BASEGET"});
	placements.push_back({topRightPlacement,baseGet,0.5,"TOP RIGHT, BASEGET"});
	placements.push_back({aleatPlacement,baseGet,0.7,"RANDOM, BASEGET"});
	placements.push_back({convexPlacement,baseGet,0.2,"CONNEX, BASEGET"});
	placements.push_back({convexPlacement,endGet,0.8,"CONNEX, ENDGET"});
	auto nextSeuil = [&seuil,&city,&placements, &lastPlacement, &actualP]()
	-> bool {
		if (city->getRemainingCell() <= seuil)
		{
			if (lastPlacement + 1 >= placements.size())
			{
				return true;
			}
			actualP = placements[lastPlacement++];
			cout<<endl <<city->getRemainingCell()<<" REMAINING CELLS | "
				<<"PASSING TO : "<< get<3>(actualP)<<endl;
			seuil = get<2>(placements[lastPlacement]) * seuil;
		}
		return true;
	};
	nextSeuil();
	while( (b=(get<1>(actualP)(&c)))!=nullptr)
	{
		if(get<0>(actualP)(b,&p))
		{
			actualPlacement++;
			if (actualPlacement > reinitSeuil)
			{
				c.initialize();
				actualPlacement = 0;
			}
			else
			{
				c.refill();
			}
		}
		if(!nextSeuil())
			break;
	}
}


Solver::~Solver()
{
}

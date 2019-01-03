#include "Solver.h"
using namespace std;

void Solver::Solve(City* city)
{
	/**
	 * @brief
	 * Solving parameter
	 * Number of cities must be a multiple of the number of thread.
	 *
	 */
	unsigned int nbCities = 100; //Number of sub cities to compute
	unsigned int subcitySize = 100;//Sub cities size
	unsigned int nbThread =5;//Number of thread

	auto start = chrono::steady_clock::now();
	unsigned int nbCityPerThread = nbCities/nbThread;
	vector<vector<City*>> subProc(nbThread);
	vector<City*> plane;
	mutex printMutex;
	unsigned int remainingCities = nbCities;
	for(auto& p:subProc)
	{
		p = vector<City*>(nbCityPerThread);
		for (auto &pt : p)
			pt = new City(subcitySize, subcitySize);
	}
	unsigned int subcitiesNumber = (city->getCityHeight() * city->getCityWidth()) / (subcitySize*subcitySize);
	//COMPUTE SUBCITIES
	cout << "COMPUTING SUB CITIES" << endl;
	vector<thread*> subSolver(nbThread);
	Chooser::initChooser();
	for(int i =0;i<subSolver.size();i++)
	{
		vector<City*>& v = subProc[i];
		subSolver[i] = new thread([&v,&i,&printMutex,&remainingCities]()
		{
			for(auto& c:v)
			{
				SolveSubcity(c);
				printMutex.lock();
				remainingCities--;
				cout << "REMAINING CITIES : " << remainingCities << endl;
				printMutex.unlock();
			}
		});
	}
	for(auto& t:subSolver)
		t->join();
	for(auto& v:subProc)
	{
		for(auto& c:v)
		{
			plane.push_back(c);
		}
	}
	cout << "MAX SCORE FOR A SUB CITY : "<<
	(*max_element(plane.begin(),plane.end(),[](const City* a,const City* b)
	{
		return a->getScore() < b->getScore();
	}))->getScore()
	<< endl;
	cout << "MIN SCORE FOR A SUB CITY : " << (*min_element(plane.begin(), plane.end(), [](const City *a, const City *b) {
												 return a->getScore() < b->getScore();
											 }))
												 ->getScore()
		 << endl;
	sort(plane.begin(),plane.end(), [](const City *a, const City *b) {
		return a->getScore() > b->getScore();
											 });
	std::vector<City*> best;
	for(int i =0;i<15;i++)
		best.push_back(plane[i]);
	random_shuffle(best.begin(),best.end());
	//ASSEMBLE
	cout << endl << "ASSEMBLING SUB CITIES" << endl;
	int counter = 0;
	for(size_t i = 0; i < city->getCityWidth()-subcitySize+1; i += subcitySize)
	{

		for (size_t j = 0; j < city->getCityHeight()-subcitySize+1; j += subcitySize)
		{
			city->placeMap(*best.at(counter), i, j);
			counter++;
			if(counter>=best.size())
			{
				random_shuffle(best.begin(), best.end());
				counter = 0;
			}
		}
	}
	cout << "CLEANING MEMORY" << endl;
	for(auto&p:plane)
		delete p;
	auto end = chrono::steady_clock::now();
	chrono::duration<double> execTime = end - start;
	cout << "END OF SOLVING ALGORITHM" << endl;
	cout << "ELAPSED TIME : " << execTime.count() << endl;
}


void Solver::SolveSubcity(City* city)
{
	/**
	 * Solver uses a combination of a chooser and a placer to optimize placement on city
	 * Work in a raisonable time for small cities.
	 *
	 * The chooser is used to sort and find building using random generated list.
	 * The placer is used in 5 ways to optimize calculus time.
	 *
	 */
	 /**
	  * Type : probabilty to choose a type
	  * 		High : more probability to choose a residential
	  * 		Low : more probabilitu to choose an utility
	  * U : probability of choosing an utility
	  * 		High : more probability to choose a small utility
	  * 		Low : more probability to choose a big utility
	  * UT : probability of choosing a type of utility
	  * 		High : more probability of choosing most represented utility
	  * 		Low : more probability of choosing a less represented utility
	  * R : probability of choosing a residential
	  * 		High : more probabilityu to choose a small residential
	  * 		Low : more probability to choose a big residential
	  */
	double Type = 0.5;
	double U = 0.2;
	double UT = 0.9;
	double R = 0.8;
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
	int actualPlacement = 0;
	//Threslhold for reinitialising the chooser
	int reinitSeuil = 10;
	//DEFINING PLACEMENT FUNCTION
	auto bottomRightPlacement = [](Building* b, Placer* p)->bool {
		return p->tetrisPlacement(b);
	};
	auto topRightPlacement = [](Building *b, Placer *p) -> bool {
		return p->tetrisPlacementTOP(b);
	};
	auto aleatPlacement = [](Building *b, Placer *p) -> bool {
		return p->tetrisAleat(b);
	};
	auto convexPlacement = [](Building* b, Placer* p) -> bool {
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
		function<Building *(Chooser*)>, double, string>;

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
	placements.push_back({ bottomRightPlacement,baseGet,1,"BOTTOM RIGHT,BASEGET" });
	placements.push_back({ topRightPlacement,baseGet,0.8,"TOP RIGHT, BASEGET" });
	placements.push_back({ aleatPlacement,baseGet,0.7,"RANDOM, BASEGET" });
	placements.push_back({ convexPlacement,baseGet,0.7,"CONNEX, BASEGET" });
	placements.push_back({ convexPlacement,endGet,0.8,"CONNEX, ENDGET" });
	auto nextSeuil = [&seuil, &city, &placements, &lastPlacement, &actualP]()
		-> bool {
		if (city->getRemainingCell() <= seuil)
		{
			if (lastPlacement >= placements.size())
			{
				return true;
			}
			actualP = placements[lastPlacement++];
			//cout << endl << city->getRemainingCell() << " REMAINING CELLS | "
			//	<< "PASSING TO : " << get<3>(actualP).c_str() << endl;
			seuil = get<2>(placements[lastPlacement]) * seuil;
		}
		return true;
	};
	nextSeuil();
	while ((b = (get<1>(actualP)(&c))) != nullptr)
	{
		if (get<0>(actualP)(b, &p))
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
		if (!nextSeuil())
			break;
	}
	cout << "SUB MAP SCORE : " << city->getScore() << endl;
}


Solver::~Solver()
{
}

#pragma once
#include "Project.h"
#include <time.h>
#include <deque>
/**
 * @brief
 * Class use to generate list of building.
 */
class Chooser
{
	public:
		Chooser();
		Chooser(double type_,double utilities_,
			double utilitiesType_,double residential_,Project* p);
		void initialize();
		void refill();
		Building* get();
		Building* getEnd();
	private:
		static bool dice(double proba);//Generate a random number and test if it's inferior to the proba
		static bool isRandInit;
		Project* projectRef;
		double type;
		double utilities;
		double utilitiesType;
		double residential;
		bool lastGet=false;
		std::deque<Building*> pile;
		std::deque<Building*> save;
		std::vector<Building*> residentialList;
		std::vector<std::pair<unsigned int, std::vector<Building *>> > utilitiesSorted;
		std::map<unsigned int,unsigned int> utilitiesRegister;
		std::map<unsigned int,std::vector<Building*>> utilitiesLists;


};

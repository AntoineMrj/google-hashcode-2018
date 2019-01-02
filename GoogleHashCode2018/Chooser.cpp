#include "Chooser.h"

bool Chooser::isRandInit = false;
Chooser::Chooser()
{
	if(!isRandInit)
	{
		srand(time(NULL));
		isRandInit = true;
	}
	type =0;
	utilities = 0;
	utilitiesType = 0;
	residential = 0;
}

Chooser::Chooser(double type_, double utilities_,
				 double utilitiesType_, double residential_, Project *p)
{
	projectRef=p;
	if (!isRandInit)
	{
		srand(time(NULL));
		isRandInit = true;
	}
	for(auto it:projectRef->utilities)
		utilitiesRegister[it.first] = 0;
	type = type_;
	utilities = utilities_;
	utilitiesType = utilitiesType_;
	residential = residential_;
	initialize();
}
bool Chooser::dice(double proba)
{
	double r = (double(rand() % 100 + 1) / 100);
	return r < proba;
}
/**
 * @brief
 * Generates the list of the chooser
 */
void Chooser::initialize()
{
	while(pile.size()>0)
		pile.pop_back();
	//Getting building list from project reference
	residentialList = projectRef->residentials;
	utilitiesLists = projectRef->utilities;
	//Sorting lists
	std::copy(utilitiesLists.begin(),utilitiesLists.end(),
		std::back_inserter(utilitiesSorted));
		//Utilities are sorted in function of their frequencies in the city.
	std::sort(utilitiesSorted.begin(), utilitiesSorted.end(),
			  [this](const std::pair<unsigned int, std::vector<Building *>> &p1, const std::pair<unsigned int, std::vector<Building *>> &p2) {
				  return this->utilitiesRegister[p1.first] < this->utilitiesRegister[p2.first];
			  });
	double type_temp=type;
	while (residentialList.size() > 0 || utilitiesSorted.size() > 0)
	{
		if (dice(type_temp)) //RESIDENTIAL
		{
			int a =0;
			for(auto r=residentialList.begin();r!=residentialList.end();++r)
			{
				if (a++==residentialList.size()-1 || dice(utilitiesType))
				{
					pile.push_back(*r);
					residentialList.erase(r);
					break;
				}
			}
			if(residentialList.size()==0)
			{
				type_temp =-1;
			}
		}
		else//UTILITIES
		{

			std::vector<Building*>* uList = nullptr;
			int a = 0;
			//FINDING THE UTILITIES TYPE
			std::vector<std::pair<unsigned int, std::vector<Building *> > >::iterator itRef;
			for (auto uType = utilitiesSorted.begin(); uType != utilitiesSorted.end(); ++uType)
			{
				if ((a++ == utilitiesSorted.size()-1) || dice(utilitiesType))
				{
					uList = &(*uType).second;
					itRef = uType;
					break;
				}
			}
			a=0;
			//CHOOSING AN UTILITY IN THE PREVIOUS LIST
			for (auto r = uList->begin(); r != uList->end(); ++r)
			{
				if (a++==uList->size()-1|| dice(utilities))
				{
					pile.push_back(*r);
					uList->erase(r);
					if(uList->size()==0)
						{
							utilitiesSorted.erase(itRef);
						}
					break;
				}
			}
			if(utilitiesSorted.size()==0)
			{
				type_temp=1.1;
			}
		}
	}

}
/**
 * @brief
 * Fill the list of the chooser with its previous gived building.
 */
void Chooser::refill()
{
	if(!lastGet)
	{
		if(save.front()->getType()==Building_type::Utility)
		{
			utilitiesRegister[save.front()->getExtra()]++;
		}
		while(save.size()>0)
		{
			pile.push_back(save.front());
			save.pop_front();
		}
	}
	else
	{
		if (save.front()->getType() == Building_type::Utility)
		{
			utilitiesRegister[save.front()->getExtra()]++;
		}
		while (save.size() > 0)
		{
			pile.push_front(save.front());
			save.pop_front();
		}
	}
}
/**
 * @brief
 * Get a building from the top of the stack
 * @return Building*
 */
Building* Chooser::get()
{
	if(pile.size()>0)
	{
		lastGet = false;
		Building* temp = pile.front();
		pile.pop_front();
		save.push_front(temp);
		return temp;
	}
	return nullptr;
}
/**
 * @brief
 * Get a building from the back of the stack
 * @return Building* 
 */
Building *Chooser::getEnd()
{
	if (pile.size() > 0)
	{
		lastGet = true;
		Building *temp = pile.back();
		pile.pop_back();
		save.push_front(temp);
		return temp;
	}
	return nullptr;
}
#pragma once
#include "Building.h"

class Residential : public Building
{
private:
	int capacity;

public:
  Residential(unsigned int projectNum_, unsigned int rowNum_, unsigned int columnNum_,int capacity_);
  int getCapacity() { return this->capacity; }
  virtual void placeInCity(City &C)
  {
    C.placeBuildingType(this);
  }
};

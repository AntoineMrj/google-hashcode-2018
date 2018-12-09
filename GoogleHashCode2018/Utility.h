#include "Building.h"
#pragma once

class Utility : public Building
{
private:
	int type;

public:
  Utility(unsigned int projectNum_, unsigned int rowNum_, unsigned int columnNum_,int type_);
  int getType() { return this->type; }
  virtual void placeInCity(City &C)
  {
    C.placeBuildingType(this);
  }
};
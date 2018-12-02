#pragma once
#include "Building.h"

class Residential : public Building
{
private:
	int capacity;

public:
	Residential(int capacity_);
	int getCapacity() { return this->capacity; }
};

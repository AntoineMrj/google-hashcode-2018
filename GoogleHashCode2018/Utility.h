#include "Building.h"
#pragma once

class Utility : public Building
{
private:
	int type;

public:
	Utility(int type_);
	int getType() { return this->type; }
};
#include "Residential.h"

Residential::Residential(unsigned int projectNum_, unsigned int rowNum_, unsigned int columnNum_,int capacity_) : Building(projectNum_,rowNum_,columnNum_)
{
	this->capacity = capacity_;
}
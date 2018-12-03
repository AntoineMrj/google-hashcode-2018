#include "Utility.h"

Utility::Utility(unsigned int projectNum_, unsigned int rowNum_, unsigned int columnNum_,int type_) : Building(projectNum_,rowNum_,columnNum_)
{
	this->type = type_;
}
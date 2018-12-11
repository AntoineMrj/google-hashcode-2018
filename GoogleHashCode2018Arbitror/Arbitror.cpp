#include "Arbitror.h"

using namespace std;

Arbitror::Arbitror()
{
}

Arbitror::Arbitror(string projectFile, string solutionFile)
{
	this->projectFile = projectFile;
	this->solutionFile = solutionFile;
	this->score = 0;
	this->fileLoader = new FileLoader;
	this->evaluate();
}

/*
	Method that evaluates the score of the solution for each building placed
*/
void Arbitror::evaluate()
{
	//TODO
}

int Arbitror::getScore()
{
	return this->score;
}

Arbitror::~Arbitror()
{
}

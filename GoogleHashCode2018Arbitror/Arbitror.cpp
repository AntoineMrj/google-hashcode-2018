#include "pch.h"
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
	this->evaluate();
}

/*
	Method that evaluates the score of the solution for each building placed
*/
void Arbitror::evaluate()
{
	FileLoader::loadSolution(this->projectFile, this->solutionFile);
	this->city = Project::globalProject.city;
	this->score = city->getScore();
}

/*
	Method that returns the score of the solution
*/
int Arbitror::getScore()
{
	return this->score;
}

Arbitror::~Arbitror()
{
}

#include "Arbitror.h"

using namespace std;

Arbitror::Arbitror(string projectFile, string solutionFile)
{
	this->score = 0;
	// Création des objets correspondants à un projet et à une solution de celui-ci
	FileLoader* fileLoader = new FileLoader;
	this->city = fileLoader->loadSolution(projectFile, solutionFile);
}

void Arbitror::evaluate()
{

}

bool Arbitror::checkPosition()
{
	return false;
}

void Arbitror::computeScore()
{

}

Arbitror::~Arbitror()
{
}

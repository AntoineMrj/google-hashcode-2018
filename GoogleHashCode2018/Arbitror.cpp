#include "Arbitror.h"

using namespace std;

Arbitror::Arbitror(string projectFile, string solutionFile)
{
	this->score = 0;
	// Cr�ation des objets correspondants � un projet et � une solution de celui-ci
	FileLoader* fileLoader = new FileLoader;
	this->project = fileLoader->loadProject(projectFile);
	this->solution = fileLoader->loadProject(solutionFile);
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

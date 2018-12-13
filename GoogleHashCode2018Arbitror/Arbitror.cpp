#include "Arbitror.h"

using namespace std;

/**
 * Default constructor
 */
Arbitror::Arbitror()
{
}

/**
 * Constructor that set the score to 0 and evaluate a solution
 *
 * @param projectFile
 * @param solutionFile
 */
Arbitror::Arbitror(string projectFile, string solutionFile)
{
	this->projectFile = projectFile;
	this->solutionFile = solutionFile;
	this->score = 0;
	this->evaluate();
}

/**
 * Method that evaluates the score of the solution for each building placed
 */
void Arbitror::evaluate()
{
	FileLoader::loadSolution(this->projectFile, this->solutionFile);
	this->score = Project::globalProject.city->getScore();
}

/**
 * Method that returns the score of the solution
 */
int Arbitror::getScore()
{
	return this->score;
}

/**
 * Destructor of the class
 */
Arbitror::~Arbitror()
{
}

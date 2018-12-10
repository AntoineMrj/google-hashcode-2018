#include "Arbitror.h"

using namespace std;

Arbitror::Arbitror(string projectFile, string solutionFile)
{
	this->projectFile = projectFile;
	this->solutionFile = solutionFile;
	this->score = 0;
	this->fileLoader = new FileLoader;
	this->computeTime();
}

/*
	Method that calculates the execution time of the solution's score computation
*/
double Arbitror::computeTime()
{
	auto start = chrono::steady_clock::now();

	//Creation of objects corresponding to a project and a solution of it
	this->city = fileLoader->loadSolution(projectFile, solutionFile);
	//Computation of the solution's score
	this->evaluate();

	auto end = chrono::steady_clock::now();

	// Execution time
	chrono::duration<double> executionTime = end - start;
	return executionTime.count();
}

/*
	Method that evaluates the score of the solution for each building placed
*/
void Arbitror::evaluate()
{
	//TODO
}

Arbitror::~Arbitror()
{
}

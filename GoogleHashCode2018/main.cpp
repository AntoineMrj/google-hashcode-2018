#include <iostream>
#include "FileLoader.h"
#include <algorithm>
#include "Solver.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <unistd.h>
using namespace std;

/**
 * Main function
 *
 * @param argc
 * @param argv
 */
int main(int argc, char* argv[])
{
	// We check if the number of arguments is correct
	if (argc < 3)
	{
		cerr << "Error : Too few arguments." << endl;
		cout << "Usage: " << argv[0] << " [projectFile] [outputFile]" << endl;
	}
	else if (argc > 3)
	{
		cerr << "Error : Too many arguments." << endl;
		cout << "Usage: " << argv[0] << " [projectFile] [outputFile]" << endl;
	}
	else
	{
		string projectPath(argv[1]);
		string solutionPath(argv[2]);

		cout << "PRECALCULATING STUFFS..." << endl;
		// Loading the project
		FileLoader::loadProject(projectPath);

		Project& project = Project::globalProject;
		project.setProjectFile(projectPath);
		project.setSolutionFile(solutionPath);

		/*
		// Placing the buildings
		project.city->placeBuilding(project.buildings.at(0), 0, 0);
		cout << project.buildings.size() << endl;*/
		bool hasEnded=false;
		mutex locker;
		auto start = chrono::steady_clock::now();
		thread solvingThread([&project,&locker,&hasEnded](){
			Solver::Solve(project.city);
			locker.lock();
			hasEnded = true;
			locker.unlock();
		});
		thread printer([&project, &locker, &hasEnded,&start]()
		{
			while(true)
			{
				locker.lock();
				if(hasEnded)
					break;
				locker.unlock();
				auto end = chrono::steady_clock::now();
				chrono::duration<double> executionTime = end - start;
				cout << "\r"
					 << "Elapsed Time : " << setw(10) << executionTime.count() << " |"
					 << "Remaining Cells : " << setw(10)  <<project.city->getRemainingCell();
				usleep(500);
			}
		});

			solvingThread.join();
			printer.join();
		// Writing the solution in the solution file
		std::cout <<"\n------------------------------------"<<std::endl;
		//project.city->PrintMap();
		project.city->toSolution(solutionPath);
		cout << "\nSCORE : " << project.city->getScore()<<endl;
		cout << "REMAINING CELLS : " << double(project.city->getRemainingCell())/(project.city->getCityHeight()*project.city->getCityWidth())*100<<"%" <<endl;
	}

	return EXIT_SUCCESS;
}
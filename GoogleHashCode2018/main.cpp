#include <iostream>
#include "FileLoader.h"
#include <algorithm>
int main(int argc, char* argv[])
{
	
	if(argc<3)
	{
		std::cerr << "Erreur : Too fee arguments." << std::endl;
		std::cout << "This program require 2 files path as input, first one for the project path, the second one for the output path." << std::endl;
	}
	else if(argc>3)
	{
		std::cerr << "Erreur : Too much arguments." << std::endl;
		std::cout << "This program require 2 files path as input, first one for the project path, the second one for the output path." << std::endl;
	}
	else
	{
		/**
		 *Load the project passed in arguments.
		 */
		std::string projectPath(argv[1]);
		FileLoader::loadProject(argv[1]);

		Project::globalProject.city->placeBuilding(Project::globalProject.buildings.at(0), 0, 0);
		std::cout << Project::globalProject.buildings.size() << std::endl;
		Project::globalProject.city->toSolution("solution.txt");
	}

	return EXIT_SUCCESS;
}
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
		//std::string projectPath(argv[1]);
		//std::string solutionOuput(argv[2]);
		//FileLoader::loadProject(argv[1]);
		FileLoader::loadSolution("GoogleHashCode2018/input/a_example.in", "GoogleHashCode2018/input/a.out");
	}

	return EXIT_SUCCESS;
}
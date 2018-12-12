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
		std::string projectPath(argv[1]);
		std::string solutionOuput(argv[2]);
		FileLoader::loadProject(argv[1]);

		std::ofstream outfile(solutionOuput); //creation du fichier solution
		outfile.close();
	}

	return EXIT_SUCCESS;
}
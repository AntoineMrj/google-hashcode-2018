#include <iostream>
#include "FileLoader.h"
#include <algorithm>

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
		
		// Loading the project
		FileLoader::loadProject(projectPath);

		Project project = Project::globalProject;
		project.setProjectFile(projectPath);
		project.setSolutionFile(solutionPath);

		// Placing the buildings
		project.city->placeBuilding(project.buildings.at(0), 0, 0);
		std::cout << project.buildings.size() << std::endl;

		// Writing the solution in the solution file
		project.city->toSolution(solutionPath);

	}

	return EXIT_SUCCESS;
}
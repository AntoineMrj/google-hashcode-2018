#include "FileLoader.h"

using namespace std;

/*
	Chargement du fichier de projet pour créer le projet, la carte et 
	tous les buildings disponibles
*/
void FileLoader::loadProject(string projectFile)
{
	Project& project = Project::globalProject;
	City city;
	Building *building;

	ifstream openFile(projectFile);
	int height, width, maxWalkingDistance, nbOfBuildingProjects, rowNum, columnNum, capacity;
	char currentChar;
	string currentLine, projectType;
	vector<int> residential, utilities;

	//si le fichier existe
	if (openFile)
	{
		//lecture de la première ligne
		openFile >> height >> width >> maxWalkingDistance >> nbOfBuildingProjects;
		project.setCity(height, width);
		project.setMaxWalkingDistance(maxWalkingDistance);
		//Lecture des buildings
		for(int i = 0; i < nbOfBuildingProjects; i++) {
			openFile >> projectType >> rowNum >> columnNum >> capacity;

			if (projectType == "R"){
				building = new Building(i, rowNum, columnNum, capacity, Residential);
				project.addResidential(building);
			}
			else {
				building = new Building(i, rowNum, columnNum, capacity,Utility);
				project.addUtility(building);
			}

			//Construction de la liste de cellules occupées
			for (int j = 0; j < rowNum; j++) {
				for (int k = 0; k < columnNum; k++)
				{
					openFile >> currentChar;
					if (currentChar == '.')
						building->setCell(j,k,0);
					else
						building->setCell(j,k, 1);
				}
			}
			building->computeShape();
		}
	}
	else
		cout << "The project file doesn't exist" << endl;
}

/*
	Chargement du fichier de solution pour placer les buildings choisis sur la
	map de la classe city
*/
void FileLoader::loadSolution(std::string projectFile, std::string solutionFile)
{
	Project& project = Project::globalProject;
	loadProject(projectFile);

	Building *building;
	City* city=project.city;

	int buildingsToPlace, buildingNum, row, col;

	ifstream openFile(solutionFile);

	if (openFile)
	{
		if (!(openFile.peek() == ifstream::traits_type::eof()))
		{
			// lecture première ligne
			openFile >> buildingsToPlace;

			for (int i = 0; i < buildingsToPlace; i++)
			{
				openFile >> buildingNum >> row >> col;

				building = project.buildings[buildingNum];
				// SI le building ne peut pas être placé, la solution est invalide
				if (!city->placeBuilding(building, row, col))
				{
					cout << "Invalid solution: at least 2 buildings are on top of each other" << endl;
					city->setScore(0);
					break;
				}
			}
		}
		else
			cout << "The solution file is empty" << endl;
	}
	else
		cout << "The solution file doesn't exist" << endl;
}

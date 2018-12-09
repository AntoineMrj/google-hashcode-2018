#include "FileLoader.h"

using namespace std;

FileLoader::FileLoader()
{
}

FileLoader::~FileLoader()
{
}

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

	int** occupiedCells;

	//si le fichier existe
	if (openFile)
	{
		//lecture de la première ligne
		openFile >> height >> width >> maxWalkingDistance >> nbOfBuildingProjects;
		project.setCity(width, height);

		//Lecture des buildings
		for(int i = 0; i < nbOfBuildingProjects; i++) {
			openFile >> projectType >> rowNum >> columnNum >> capacity;

			if (projectType == "R"){
				building = new Residential(i, rowNum, columnNum, capacity);
				project.addResidential(building);
			}
			else {
				building = new Utility(i, rowNum, columnNum, capacity);
				project.addUtility(building);
			}

			//Construction de la liste de cellules occupées
			int **occupiedCells = new int*[rowNum];
			for (int j = 0; j < rowNum; j++) {
				occupiedCells[j] = new int[columnNum];
				for (int k = 0; k < columnNum; j++)
				{
					openFile >> currentChar;
					if (currentChar == '.')
						building->setCell(k,j,0);
					else
						building->setCell(k, j, 1);
				}
			}
		}
	}
	else
		cout << "Le fichier de projet n'existe pas" << endl;

}

/*
	Chargement du fichier de solution pour placer les buildings choisis sur la
	map de la classe city
*/
City FileLoader::loadSolution(std::string projectFile, std::string solutionFile)
{
	Project& project = Project::globalProject;
	this->loadProject(projectFile);

	Building *building;
	City city;

	int buildingsToPlace, buildingNum, x, y;

	ifstream openFile(solutionFile);

	if (openFile)
	{
		// lecture première ligne
		openFile >> buildingsToPlace;

		for (int i = 0; i < buildingsToPlace; i++)
		{
			openFile >> buildingNum >> x >> y;

			building = project.buildings[buildingNum];
			// SI le building ne peut pas être placé, la solution est invalide
			if (!city.placeBuilding(*building, x, y))
			{
				cout << "Solution invalide: au moins 2 bâtiments se chevauchent" << endl;
				exit(0);
			}
		}
	}
	else
		cout << "Le fichier de solution n'existe pas" << endl;

	return city;
}

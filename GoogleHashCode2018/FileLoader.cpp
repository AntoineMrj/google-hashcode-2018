#include "FileLoader.h"

using namespace std;

FileLoader::FileLoader()
{
}


FileLoader::~FileLoader()
{
}

Project FileLoader::loadProject(string source)
{
	Project project;
	City city;
	Building *building;

	ifstream openFile(source);
	int height, width, maxWalkingDistance, nbOfBuildingProjects, rowNum, columnNum, capacity;
	char currentChar;
	string currentLine, projectType;
	vector<int> residential, utilities;

	int** occupiedCells;

	if (openFile) //si le fichier existe
	{
		openFile >> height >> width >> maxWalkingDistance >> nbOfBuildingProjects; //lecture de la première ligne
		project.setCity(width, height);

		for(int i = 0; i < nbOfBuildingProjects; i++) { //Lecture des buildings
			openFile >> projectType >> rowNum >> columnNum >> capacity;

			if (projectType == "R"){
				building = new Residential(i, rowNum, columnNum, capacity);
				project.addResidential(building);
			}
			else {
				building = new Utility(i, rowNum, columnNum, capacity);
				project.addUtility(building);
			}

			int **occupiedCells = new int*[rowNum]; //Construction de la liste de cellules occupées
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
		cout << "Le fichier n'existe pas" << endl;

	return project;
}

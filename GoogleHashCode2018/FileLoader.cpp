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

	ifstream openFile(source);
	int height, width, maxWalkingDistance, nbOfBuildingProjects, rowNum, columnNum, capacity;
	char currentChar;
	string currentLine, projectType;
	vector<int> residential, utilities;

	int** occupiedCells;

	if (openFile) //si le fichier existe
	{
		openFile >> height >> width >> maxWalkingDistance >> nbOfBuildingProjects; //lecture de la première ligne

		int **map = new int*[height]; //Construction de la map de taille height/width remplie de 0
		for (int i = 0; i < height; i++) {
			map[i] = new int[width];
			for (unsigned int j = 0; j < 5; j++)
			{
				map[i][j] = 0;
			}
		}
		city.setMap(width, height, map);

		for(int i = 0; i < nbOfBuildingProjects; i++) { //Lecture des buildings
			openFile >> projectType >> rowNum >> columnNum >> capacity;

			int **occupiedCells = new int*[rowNum]; //Construction de la liste de cellules occupées
			for (int j = 0; j < rowNum; j++) {
				occupiedCells[j] = new int[columnNum];
				for (int k = 0; k < columnNum; j++)
				{
					openFile >> currentChar;
					if (currentChar == '.')
						occupiedCells[j][k] = 0;
					else
						occupiedCells[j][k] = 1;
				}
			}

			if (projectType == "R") {//création du building en fonction de son type et remplissage des index
				Residential b(i, rowNum, columnNum, occupiedCells, capacity);
				residential.push_back(i);
			}
			else {
				Utility b(i, rowNum, columnNum, occupiedCells, capacity);
				utilities.push_back(i);
			}
				

			project.addBuilding(b);
		}

		project.setCity(city);
		project.residentials(residential);
		project.setUtilities(utilities);
	}
	else
		cout << "Le fichier n'existe pas" << endl;

	return project;
}

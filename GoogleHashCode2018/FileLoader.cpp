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
	ifstream openFile(source);
	int height, width, maxWalkingDistance, nbOfBuildingProjects, rowNum, columnNum, capacity;
	char test;
	string currentLine, projectType;
	vector<Building> vect;
	vector<int> residential, utilities;

	int** occupiedCells;

	if (openFile) //si le fichier existe
	{
		openFile >> height >> width >> maxWalkingDistance >> nbOfBuildingProjects; //lecture de la première ligne et enregistrement dans les varibales
		City c(height, width); //création de la city

		for (size_t i = 0; i < nbOfBuildingProjects; i++) { //Lecture des buildings
			openFile >> projectType >> rowNum >> columnNum >> capacity;
			//CREATION DE LA LISTE OCCUPIED CELLS

			for (size_t j = 0; j < (rowNum*columnNum); j++) //lecture du building
			{
				openFile >> test;
			}

			Building b(i, rowNum, columnNum, occupiedCells);//création du building
			vect.push_back(b); //ajout du bâtiment au vecteur

			if (projectType == "R") //Remplissage des index en fonction du type de bâtiment
				residential.push_back(i);
			else
				utilities.push_back(i);
		}
	}
	else
		cout << "Le fichier n'existe pas" << endl;

	return Project(c, vect, residential, utilities);
}

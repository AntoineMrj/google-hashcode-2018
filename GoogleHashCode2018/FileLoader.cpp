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
	string currentLine, projectType;
	vector<Building> vect;

	if (openFile) //si le fichier existe
	{
		openFile >> height >> width >> maxWalkingDistance >> nbOfBuildingProjects; //lecture de la première ligne et enregistrement dans les varibales

		for (size_t i = 0; i < nbOfBuildingProjects - 1; i++) { //Lecture des buildings
			openFile >> projectType >> rowNum >> columnNum >> capacity;

			//char map[rowNum][columnNum];

			for (size_t j = 0; j < (rowNum*columnNum)-1; j++) //lecture du building
			{

			}
		}
	}
	else
		cout << "Le fichier n'existe pas" << endl;

	
	while(getline(openFile, currentLine))
	{
		openFile >> projectType >> rowNum >> columnNum >> capacity;
		cout << projectType << "|" << rowNum << "|" << columnNum << "|" << capacity << endl;
	}

	//Création du vector de buildings de taille nbOfBuildingProjects et remplissage avec les buildings du fichier .in

	//return Project(City(width, height), );
	return Project();
}

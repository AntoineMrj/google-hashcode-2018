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
	int height, width, maxWalkingDistance, nbOfBuildingProjects;

	if (openFile) //si le fichier existe
	{

		openFile >> height >> width >> maxWalkingDistance >> nbOfBuildingProjects; //lecture de la première ligne et enregistrement dans les varibales
	}

	//Création du vector de buildings de taille nbOfBuildingProjects et remplissage avec les buildings du fichier .in

	//return Project(City(width, height), );
	return Project();
}

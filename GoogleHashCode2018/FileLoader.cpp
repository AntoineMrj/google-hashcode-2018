#include "FileLoader.h"

using namespace std;

FileLoader::FileLoader()
{
}


FileLoader::~FileLoader()
{
}

void FileLoader::loadProject(string source)
{
	Project& project = Project::globalProject;
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
		openFile >> height >> width >> maxWalkingDistance >> nbOfBuildingProjects; //lecture de la premi�re ligne
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

			int **occupiedCells = new int*[rowNum]; //Construction de la liste de cellules occup�es
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

		for (int i = 0; i <= buildingsToPlace; i++)
		{
			openFile >> buildingNum >> x >> y;

			building = project.buildings[buildingNum];
			if (city.getMapCell(x, y) == -1)
			{
				// On check les cellules que prend le building
				for (int row = 0; row < building->getRowNum(); row++)
				{
					for (int col = 0; col < building->getcolumnNum(); col++)
					{
						if (building->getCell(col, row) == 1)
						{
							// On met le numéro du building sur les cases qu'il prend sur la map
							city.setMapCell(x + row, y + col, buildingNum);
						}
					}
				}	
			}
			else
			{
				cout << "Solution invalide: au moins 2 bâtiments se chevauchent" << endl;
			}
		}
	}
	else
		cout << "Le fichier de solution n'existe pas" << endl;

	return city;
}

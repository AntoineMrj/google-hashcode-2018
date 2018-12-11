#include "Arbitror.h"
#include "FileHandling.h"
#include <iostream>
#include <sys/stat.h>
#include <chrono>
#include <Windows.h>
#include <utility>

#define NUMBER_EXEC 3

using namespace std;

/*
	Method that calculates the execution time of the solution's computation
*/
double computeExecutionTime(const string command)
{	
	auto start = chrono::steady_clock::now();
	// We execute the executable
	system(command.c_str());
	auto end = chrono::steady_clock::now();

	// Execution time
	chrono::duration<double> executionTime = end - start;

	return executionTime.count();
}

/*
	Main function
*/
int main(int argc, char **argv)
{
	// We check the number of arguments
	if (argc == 3)
	{
		const char * executableDirectory;
		const char * outputFile;
		executableDirectory = argv[1];

		// We check if the second argument is a directory
		if (!((GetFileAttributesA(executableDirectory) & FILE_ATTRIBUTE_DIRECTORY) != 0))
		{
			cout << "Error: the second argument is not a directory" << endl;
			cout << "Usage: " << argv[0] << " [executablesDirectory] [outputFile]" << endl;
			exit(0);
		}

		outputFile = argv[2];
		
		//We iterate through the directory
		vector<string> executables;
		executables = IterateOnFileDir(executableDirectory);

		Arbitror arbitror;
		vector<pair<double, int>> result;

		for (auto file : executables)
		{
			arbitror = Arbitror("projectFile ?????", "solution");
			double mean = 0;
			const string command = file + " solution";
			for (int i = 0; i < NUMBER_EXEC; i++)
			{
				mean += computeExecutionTime(command);
			}
			result.push_back(make_pair(mean / NUMBER_EXEC, arbitror.getScore()));
		}
		
		//TODO: sort results + print it in file

	}
	else
	{
		cout << "Usage: " << argv[0] << " [executablesDirectory] [outputFile]" << endl;
		exit(0);
	}
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.

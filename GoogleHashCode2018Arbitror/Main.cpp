#include "Arbitror.h"
#include "FileHandling.h"
#include <iostream>
#include <sys/stat.h>
#include <chrono>
#include <Windows.h>
#include <utility>
#include <algorithm>
#include <fstream>

#define NUMBER_EXEC 3

using namespace std;

/*
	Vector that contains the executables
*/
vector<string> executables;

/*
	Method that insert the executable files in a vector
*/
void handleExecutables(string file)
{
	cout << file << endl; //debug
	executables.push_back(file);
}

/*
	Method that calculates the execution time of the solution's computation
*/
double computeExecutionTime(const string command)
{	
	cout << "command: " << command << endl; //debug

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
		executableDirectory = argv[1];

		// We check if the second argument is a directory
		if (!((GetFileAttributesA(executableDirectory) & FILE_ATTRIBUTE_DIRECTORY) != 0))
		{
			cout << "Error: the second argument is not a directory" << endl;
			cout << "Usage: " << argv[0] << " [executablesDirectory] [outputFile]" << endl;
			exit(0);
		}
		
		//We iterate through the directory
		IterateOnFileDir(executableDirectory, handleExecutables);

		Arbitror arbitror;
		vector<pair<int, double>> result;

		for (auto file : executables)
		{
			arbitror = Arbitror("input/a_example.in", "solution");
			double mean = 0;
			const string command = file + " input/a_example.in solution_test";

			cout << command << endl; //debug

			for (int i = 0; i < NUMBER_EXEC; i++)
			{
				mean += computeExecutionTime(command);
			}
			result.push_back(make_pair(arbitror.getScore(), mean / NUMBER_EXEC));
		}
		
		//Sorting the vector on the first element of the pair (here the score)
		sort(result.begin(), result.end());

		// Writing the results in the output file
		ofstream outputFile;
		outputFile.open(argv[2]);
		outputFile << "Table of the sorted results" << endl;
		for (int i = 0; i < result.size(); i++)
		{
			outputFile << "Score: " << result[i].first
				<< "\t execution time: " << result[i].second << endl;
		}
	}
	else
	{
		cout << "Usage: " << argv[0] << " [executablesDirectory] [outputFile]" << endl;
		exit(0);
	}

	return EXIT_SUCCESS;
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

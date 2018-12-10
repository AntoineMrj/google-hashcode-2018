#include "Arbitror.h"
#include <iostream>
#include <sys/stat.h>

using namespace std;

int main(int argc, char **argv)
{
	// We check the number of arguments
	if (argc == 3)
	{
		const char * executableDirectory;
		const char * outputFile;
		executableDirectory = argv[1];

		struct stat buff;
		// We check if the second argument is a directory
		if (stat(executableDirectory, &buff) == 0)
		{
			if (!(buff.st_mode & S_IFDIR))
			{
				cout << "Error: the second argument is not a directory" << endl;
				cout << "Usage: ./program executablesDirectory outputFile" << endl;
				exit(0);
			}
		}
		else
		{
			cout << "Error while checking if the second argument is a directory" << endl;
			exit(0);
		}

		outputFile = argv[2];

	}
	else
	{
		cout << "Usage: ./program executablesDirectory outputFile" << endl;
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

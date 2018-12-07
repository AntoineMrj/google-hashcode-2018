#include"City.h"
#include "Project.h"
City::City() {
}

City::City(unsigned int w, unsigned int h)
{
	int width = w;
	int height = h;
	map = new unsigned int *[w]; // Type de la varibale map � modifier
	for (int a = 0; a < w; a++) {
	map[a] = new unsigned int[h];
	}
	for (unsigned int i = 0; i < h; i++) {
		for (unsigned int j = 0; j < h; j++)
		{
			map[i][j] = 0;
		}
	}
}

bool City::placeBuilding(Place P) {
	for (int i = 0; i < P.Shape.size(); i++) {
		if (map[P.Shape[i].row][P.Shape[i].column] == 0)
			map[P.Shape[i].row][P.Shape[i].column] = P.Shape.size()+1;
		else
			return false;
	}
	placeRegister.push_back(P);
	return true;
}

#include"City.h"

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
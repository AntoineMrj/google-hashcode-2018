#include"City.h"

City::City() {
}

City::City(int w, int h) {
	int width = w;
	int height = h;
	map = new int*[w]; // Type de la varibale map à modifier
	for (int a = 0; a < w; a++) {
		map[a] = new int[h];
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < h; j++) {
			map[i][j] = 0;
		}
	}
}
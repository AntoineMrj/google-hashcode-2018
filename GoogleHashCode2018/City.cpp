#include"City.h"

City::City(int w, int h) {
	width = w;
	height = h;
	map = new int*[w];
	for (int a = 0; a < w; a++) {
		map[a] = new int[h];
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < h; j++) {
			map[i][j] = 0;
		}
	}
}
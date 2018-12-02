#pragma once
#include<vector>

using namespace std;

class City {
private:
	struct Coord {
		int row;
		int column;
	};
	struct Place {
		int source;
		Coord position;
	};
	int width;
	int height;
	int** map;
	City(int h, int w);
	vector<Place> placeRegister;
};
#pragma once
#include<vector>

using namespace std;
struct Coord
{
	unsigned int row;
	unsigned int column;
};
struct Place
{
	unsigned int source;
	Coord position;
};

class City {
public:
	City();
	City(unsigned int h,unsigned int w);
private:
	unsigned int width;
	unsigned int height;
	unsigned int** map;
	vector<Place> placeRegister;
};
#include <iostream>
#include "FileLoader.h"

int main(int argc, char* argv[])
{
	FileLoader f;
	f.loadProject("input/a_example.in");

	int **test;
	int t = 2;
	test = &t;

	return EXIT_SUCCESS;
}
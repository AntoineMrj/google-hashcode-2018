#pragma once

class Arbitror
{
private:
	City *city;
	std::string projectFile;
	std::string solutionFile;
	int score;
public:
	Arbitror();
	Arbitror(std::string projectFile, std::string solutionFile);

	void evaluate();
	int getScore();

	~Arbitror();
};



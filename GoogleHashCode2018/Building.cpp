#import "Building.h"

Building::Building(int projectNum_; int rowNum_; int columnNum_; vector<int[]> occupiedCells_)
{
	this.projectNum = projectNum_;
	this.rowNum = rowNum_;
	this.columnNum = columnNum_;
	this.occupiedCells = occupiedCells_;
}
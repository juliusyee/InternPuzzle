#include <iostream>
#include <vector>

//Adjust these values to change the dimensions of the grid
#define ROW 5
#define COLUMN 5

using namespace std;

/////////////////////////////COORDINATE STRUCTURES///////////////////////////

struct Coordinate
{
	//Constructor
	Coordinate(int r, int c)
		:row(r), column(c) {}

	//Member Variables
	int row, column;
};

struct JumpPair
{
	//Constructor
	JumpPair(int r1, int c1, int r2, int c2)
		:row1(r1), column1(c1), row2(r2), column2(c2) {}

	//Member variables
	int row1, column1, row2, column2;
};

///////////////////////////HELPER FUNCTIONS///////////////////////////////////

//Helper function that checks if coordinate is within bounds
bool isValidCoord(int row, int column)
{
	//If the coordinate is out of bounds/off the grid, return false
	if (row < 0 || column < 0 || row >= ROW || column >= COLUMN)
	{
		return false;
	}
	return true; 
}

//Helper function that checks whether a grid coordinate is a jumpable coordinate
//If true, the Coordinate jumpTo contains the coordinate to jump to
bool isJumped(Coordinate c, vector<JumpPair> v, Coordinate& jumpTo)
{
	if (v.empty())
	{
		return false;
	}

	//Iterate through vector of JumpPairs for a match
	vector<JumpPair>::iterator itr = v.begin();
	while (itr != v.end())
	{
		//Iterate through vector of block coordinates
		if (((*itr).row1 == c.row) && ((*itr).column1 == c.column))
		{
			//Copy the second coordinate of the JumpPair into the jumpTo object
			//Then return true, otherwise, continue iterating through vector
			jumpTo.column = (*itr).column2;
			jumpTo.row = (*itr).row2;
			return true;
		}
		itr++;
	}
	return false;
}

////////////////////////////////////////////////PROGRAM FUNCTIONS//////////////////////////////////

//This function calculates the possible paths from (0,0) to each grid coordinate and returns the number of possible paths
//to the bottom right corner
int calculatePaths(int a[][COLUMN], int row, int column, vector<JumpPair> j)
{	
	//Compute for the path down 
	int downPath;
	Coordinate temp1(row + 1, column);
	Coordinate temp2(0, 0);
	//Check that it is a valid coordinate
	if (!isValidCoord(row + 1, column))
	{
		downPath = 0;
	}
	//If the grid coordinate is not visited
	else if (a[row + 1][column] == -1)
	{
		downPath = calculatePaths(a, row + 1, column,j);
		a[row + 1][column] = downPath;
	}
	//If the grid coordinate is a jumpable coordinate
	else if (isJumped(temp1,j,temp2))
	{
		downPath = calculatePaths(a, temp2.row, temp2.column, j);
		a[row + 1][column] = a[temp2.row][temp2.column];
	}
	else
	{
		downPath = a[row + 1][column];
	}

	//Compute for the path to the right
	int rightPath;
	Coordinate temp3(row, column + 1);
	Coordinate temp4(0, 0);
	//Check that it is a valid coordinate
	if (!isValidCoord(row, column + 1))
	{
		rightPath = 0;
	}
	//If the grid coordinate is not visited
	else if (a[row][column + 1] == -1)
	{
		rightPath = calculatePaths(a, row, column + 1,j);
		a[row][column + 1] = rightPath;
	}
	//IF the grid coordinate is jumpable coordinate
	else if (isJumped(temp3,j,temp4))
	{
		rightPath = calculatePaths(a, temp4.row, temp4.column, j);
		a[row][column + 1] = a[temp4.row][temp4.column];
	}
	else
	{
		rightPath = a[row][column + 1];
	}

	a[row][column] = rightPath + downPath;
	return(rightPath + downPath);
}

//This function sets up the grid based on the given dimensions and lets the program know where the block points are
//Following, this function calls the function calculatePaths to determine the number of paths from (0,0) to bottom right corner of the grid
int findPaths(vector<Coordinate> c, vector<JumpPair> j)
{
	//Initialize some variables for the start and end destination
	int endRow = ROW - 1;
	int endColumn = COLUMN - 1;
	int startRow = 0;
	int startColumn = 0;

	//Create new 2D array to keep track of possible paths and intialize each element to -1
	int path_array[ROW][COLUMN];
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			path_array[i][j] = -1;
		}
	}

	//Initialize the blocked coordinates to 0
	vector<Coordinate>::iterator itr = c.begin();
	while (itr != c.end())
	{
		path_array[(*itr).row][(*itr).column] = 0;
		itr++;
	}

	//Return the integer value in the bottom right corner of the grid
	path_array[endRow][endColumn] = 1;
	return(calculatePaths(path_array, startRow, startColumn,j));
}

/////////////////////////////////////////////////////TEST CODE//////////////////////////////////////////

//In order to test this code, you can adjust the dimensions of the grid by changing the definition of 
//ROW and COLUMN. A vector of Coordinate objects is used to represent the list of grid coordinates (list of states
//you can't get to) and a vector of JumpPair objects is used to represent the list of pairs of grid coordinates
//(list of states that will jump you to a different place altogether). The main routine below represents how to test 
//for Example 3 in the InternPuzzle Spec.


/*
int main()
{
	vector<Coordinate> v;
	Coordinate c(2, 1);
	vector<JumpPair> j;
	JumpPair jj(2, 1, 0, 3);
	v.push_back(c);
	j.push_back(jj);
	cout << findPaths(v, j) << endl;
}
*/

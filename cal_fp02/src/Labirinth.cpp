/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
	this->initializeVisited();
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y)
{
	int element = this->labirinth[y][x];
	if(this->visited[x][y])
		return false;
	this->visited[x][y] = true;


	if(element == 2)
	{
		cout << "Found the exit on " << x << " " << y <<endl;
		return true;
	}

	if(element == 0)
		return false;

	if(element == 1)
	{
		if(findGoal(x + 1, y))
			return true;
		else if (findGoal(x, y + 1))
			return true;
		else if (findGoal(x - 1, y))
			return true;
		else return findGoal(x , y - 1);

	}
	return false;
}



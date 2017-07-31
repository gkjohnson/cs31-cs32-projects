#ifndef _MYMAZE_H_
#define _MYMAZE_H_

#include "Maze.h"

class MyMaze: public Maze
{
  public:

	MyMaze(GraphManager* gm)//constructor
		: Maze(gm)
	{}

	// You may add additional code
	virtual bool LoadMaze(const std::string &sMazeFile); //loads the maze and gets the array of distances
	virtual bool GetNextCoordinate(int nCurX, int nCurY, int &nNextX, int &nNextY); //set nNextX, nNextY to the next coordinate for the maze

	//gets the array of distances for the loaded maze
	void GetDistances();

private:
	int m_dist[MAZE_WIDTH][MAZE_HEIGHT];

};

#endif //  _MYMAZE_H_

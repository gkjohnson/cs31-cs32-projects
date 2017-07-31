#include "MyMaze.h"
#include "constants.h"
#include <stack>
// Add student code here, if required


bool MyMaze::LoadMaze(const std::string &sMazeFile)
{
	//load the maze normally and save the return value
	bool val=Maze::LoadMaze(sMazeFile);

	//if the maze was not loaded properly, return false
	if(!val)return val;

	//get the distance of each grid space from the Monster's home point
	GetDistances();

	return val;
}

bool MyMaze::GetNextCoordinate(int nCurX, int nCurY, int &nNextX, int &nNextY){

	//save the distance at the current grid space in the map
	int value=m_dist[nCurX][nCurY];

	//if the value is 0, that means it is at the Monster's home space, so the function should return false
	if(value==0){
		return false;
	}

	//save the x and y values of the current location
	int x=nCurX;
	int y=nCurY;

	//for every direction, check if the distance value is one less than the current distance value
	//if it is, then set the nNextX and nNextY references equal to that space so they can be used

	if(m_dist[x+1][y]==value-1){ //RIGHT
		nNextX=x+1;
		nNextY=y;
	}else if(m_dist[x-1][y]==value-1){ //LEFT
		nNextX=x-1;
		nNextY=y;
	}else if(m_dist[x][y+1]==value-1){ //DOWN
		nNextX=x;
		nNextY=y+1;
	}else if(m_dist[x][y-1]==value-1){ //UP
		nNextX=x;
		nNextY=y-1;
	}
	return true;
}

//#include <iomanip>
//#include <iostream>
void MyMaze::GetDistances(){

	//set every space's distance in the grid to 99
	for(int i=0;i<MAZE_WIDTH;i++){
		for(int j=0;j<MAZE_HEIGHT;j++){
			m_dist[i][j]=99;
		}
	}

	//set the monster's starting grid distance to 0
	m_dist[GetMonsterStartX()][GetMonsterStartY()]=0;

	//local Coordinate class to keep track of X, Y values
	struct Coord{
		Coord(int setX, int setY)
			:x(setX),y(setY)
		{}
		int x;
		int y;
	};

	//create a stack with a starting coordinate of the Monster's start position
	std::stack<Coord> s;
	s.push(Coord(GetMonsterStartX(),GetMonsterStartY()));

	//while the stack is not empty
	while(!s.empty()){

		//pop the top coordinate off the stack
		Coord curr=s.top();
		s.pop();

		//get the smallest distance among the four neighboring coordinates
		int m=m_dist[curr.x-1][curr.y]; //LEFT
		if(m>m_dist[curr.x+1][curr.y])m=m_dist[curr.x+1][curr.y]; //RIGHT
		if(m>m_dist[curr.x][curr.y-1])m=m_dist[curr.x][curr.y-1]; //UP
		if(m>m_dist[curr.x][curr.y+1])m=m_dist[curr.x][curr.y+1]; //DOWN

		//if the current space's distance is larger than the smallest adjacent distance +1, then set the current distance to m+1
		if(m+1<m_dist[curr.x][curr.y]){
			m_dist[curr.x][curr.y]=m+1;
		}

		//save the current space's distance +1
		int v= m_dist[curr.x][curr.y]+1;


		//For every direction, check if the distance of the space is greater than v AND not a wall.
		//if both are true, then set the distance to V and add it to the stack because it has not been visited in its shortest distance yet

		//check RIGHT
		int newX=curr.x+1;
		int newY=curr.y;
		if(m_dist[newX][newY]>v&&GetGridContents(newX,newY)!=WALL){
			m_dist[newX][newY]=v;
			s.push(Coord(newX,newY));
		}
		//check LEFT
		newX=curr.x-1;
		newY=curr.y;
		if(m_dist[newX][newY]>v&&GetGridContents(newX,newY)!=WALL){
			m_dist[newX][newY]=v;
			s.push(Coord(newX,newY));
		}
		//check DOWN
		newX=curr.x;
		newY=curr.y+1;
		if(m_dist[newX][newY]>v&&GetGridContents(newX,newY)!=WALL){
			m_dist[newX][newY]=v;
			s.push(Coord(newX,newY));
		}
		//check UP
		newX=curr.x;
		newY=curr.y-1;
		if(m_dist[newX][newY]>v&&GetGridContents(newX,newY)!=WALL){
			m_dist[newX][newY]=v;
			s.push(Coord(newX,newY));
		}
	}

	//used to print out the map of distances
	/*for(int i=0;i<MAZE_HEIGHT;i++){
		for(int j=0;j<MAZE_WIDTH;j++){
				std::cout<<std::setw(2)<<m_dist[j][i]<<" ";
		}
		std::cout<<std::endl;
	}*/


}
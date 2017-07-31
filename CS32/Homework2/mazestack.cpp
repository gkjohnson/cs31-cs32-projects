#include <stack>
//#include <iostream>
//#include <iomanip>

using namespace std;

class Coord
{
 public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
 private:
	int m_r;
	int m_c;
};

void determineDistances(const char maze[][10], int sr, int sc, int dist[][10]){
	//Set every element of the distance array to 99.
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			dist[i][j]=99;
		}
	}
	//Set position (sr,sc) of the distance array to 0.
	dist[sr][sc]=0;

	//Push the starting coordinate (sr,sc) onto the coordinate stack.
	stack<Coord> c;
	Coord start(sr,sc);
	c.push(start);
	//While the stack is not empty,
	while(!c.empty()){
		//Pop the top coordinate off the stack. This gives you the current
		//(r,c) location that your algorithm is exploring.
		Coord curr=c.top();
		c.pop();

		//Let m be the minimum of the values of the four neighbors of (r,c)
		//in the distance array.
		int m=dist[curr.r()-1][curr.c()]; //UP by one - save the minimum value of the four neighbors

		if(m>dist[curr.r()+1][curr.c()]){ //DOWN by one
			m=dist[curr.r()+1][curr.c()];
		}
		if(m>dist[curr.r()][curr.c()+1]){ //RIGHT by one
			m=dist[curr.r()][curr.c()+1];
		}
		if(m>dist[curr.r()][curr.c()-1]){ //LEFT by one
			m=dist[curr.r()][curr.c()-1];
		}

		//If the value at (r,c) in the distance array is greater than m+1,
		//then set it to m+1.
		if(dist[curr.r()][curr.c()]>m+1){ //If the value at (r,c) in the distance array is greater than m+1, then set it to m+1.
			dist[curr.r()][curr.c()]=m+1;
		}

		//Let v be the value at (r,c) in the distance array.
		int v=dist[curr.r()][curr.c()];

		//Check where you can move from the current position:
		//If you can move NORTH and the value at position (r-1,c) in the
		//distance array is greater than v+1, then set it to v+1 and
		//push (r-1,c) onto the coordinate stack.
		int nr=curr.r()-1;
		int nc=curr.c();
		if(maze[nr][nc]!='X'
			&&dist[nr][nc]>v+1){ //check the space UP by one - NORTH
				dist[nr][nc]=v+1;

				Coord temp(nr,nc);
				c.push(temp);
		}
		nr=curr.r();
		nc=curr.c()+1;
		if(maze[nr][nc]!='X'
			&&dist[nr][nc]>v+1){ //check the space RIGHT by one - EAST
				dist[nr][nc]=v+1;

				Coord temp(nr,nc);
				c.push(temp);
		}
		nr=curr.r()+1;
		nc=curr.c();
		if(maze[nr][nc]!='X'
			&&dist[nr][nc]>v+1){ //check the space DOWN by one - SOUTH
				dist[nr][nc]=v+1;

				Coord temp(nr,nc);
				c.push(temp);
		}
		nr=curr.r();
		nc=curr.c()-1;
		if(maze[nr][nc]!='X'
			&&dist[nr][nc]>v+1){ //check the space LEFT by one - WEST
				dist[nr][nc]=v+1;

				Coord temp(nr,nc);
				c.push(temp);
		}
	}
}

/*int main()
{
	char myMaze[10][10] = {
		{ 'X','X','X','X','X','X','X','X','X','X'},
		{ 'X','.','.','.','.','.','X','.','.','X'},
		{ 'X','X','.','X','X','.','.','.','.','X'},
		{ 'X','.','.','X','.','.','.','X','.','X'},
		{ 'X','.','.','.','X','X','.','X','X','X'},
		{ 'X','X','X','.','.','.','.','X','.','X'},
		{ 'X','X','.','.','.','X','.','X','.','X'},
		{ 'X','X','.','X','.','X','.','X','X','X'},
		{ 'X','X','.','.','.','X','.','.','.','X'},
		{ 'X','X','X','X','X','X','X','X','X','X'}
	};

	int distances[10][10];
	determineDistances(myMaze, 6, 3, distances);
	for (int r = 0; r < 10; r++)
	{
		for (int c = 0; c < 10; c++)
			cout << ' ' << setw(2) << distances[r][c];
		cout << endl;
	}
              // Output should be
              //  99 99 99 99 99 99 99 99 99 99
              //  99  7  6  7  8  9 99  9 10 99
              //  99 99  5 99 99  8  7  8  9 99
              //  99  5  4 99  8  7  6 99 10 99
              //  99  4  3  2 99 99  5 99 99 99
              //  99 99 99  1  2  3  4 99 99 99
              //  99 99  1  0  1 99  5 99 99 99
              //  99 99  2 99  2 99  6 99 99 99
              //  99 99  3  4  3 99  7  8  9 99
              //  99 99 99 99 99 99 99 99 99 99
}
*/

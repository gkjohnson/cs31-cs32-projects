#include "History.h"
#include "globals.h"

#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
:m_rows(nRows),m_cols(nCols){
	
	m_grid=new int*[nRows]; //create a double array the size of the grid [rows][cols] and initialize all values to 0
	for(int i=0;i<nRows;i++){
		m_grid[i]=new int [nCols];
		for(int j=0;j<nCols;j++){
			m_grid[i][j]=0;
		}
	}
}
History::~History(){
	for(int i=0;i<m_rows;i++){ //deletes the arrays kept in the array
		delete [] m_grid[i];
	}
	delete [] m_grid; //deletes the array
}
bool History::record(int r, int c){
	if(r<=0||r>m_rows||c<=0||c>m_cols){ //if either the rows or cols are outside the previously stated size
			return false;
	}

	m_grid[r-1][c-1]++; //increment the space that is passed

	return true;
}
void History::display() const{
	clearScreen();

	for(int r=0;r<m_rows;r++){ //cycle through the rows
		for(int c=0; c<m_cols;c++){ //cycle through the cols
			if(m_grid[r][c]==0){ //if there is zero history at the space, draw '.'
				cout<<'.';
			}else if(m_grid[r][c]<9){ //if the history is between 0 and 9 at the space, draw the number
				cout<<m_grid[r][c];
			}else if(m_grid[r][c]>=9){ //if the history is greater than or equal to nine, draw nine
				cout<<'9';
			}
		}
		cout<<'\n'; //at the end of the row, move to the next one
	}
}
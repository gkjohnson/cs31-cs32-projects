#include "grid.h"
#include <string>
#include <iostream>
using namespace std;

bool isPathWellFormed(string path);
int followSegment(int r, int c, char dir, int maxSteps);
int followPath(int sr, int sc, int er, int ec, string path, int& nsteps);
bool charCompare(char c, string str);
int toDigit(string n);
int exponent(int n,int exp);




int main()
{
	
	int sr=3;
	int sc=1;
	int er=3;
	int ec=4;
	
	setSize(3,4);      // make a 3 by 4 grid
	setWall(1,4);      // put a wall at (1,4)
	setWall(2,2);      // put a wall at (2,2)
	if (!isWall(3,2))  // if there's no wall at (3,2)  [there isn't]
		setWall(3,2);  //    put a wall at (3,2)
	draw(sr,sc, er,ec);    // draw the grid, showing an S at (3,1)
                       //    start position, and an E at (3,4)

	int nsteps=-1;
	cerr<<"FollowPath with 'n2e2s3' Returns: "<<followPath(sr,sc,er,ec,"n2e2s3",nsteps)<<endl;
	cerr<<"nsteps: "<<nsteps<<endl;


//Personal Functions///////////////////////////////////
/*	//toDigit Testing
	cerr<<toDigit("3413")+1<<" - "<<3413+1<<endl;
	cerr<<toDigit("64242452")+1<<" - "<<64242452+1<<endl;
	cerr<<toDigit("345134")+1<<" - "<<345134+1<<endl;
	cerr<<toDigit("00394")+1<<" - "<<394+1<<endl;
	cerr<<toDigit("0000")+1<<" - "<<0000+1<<endl;
	cerr<<toDigit("002435")+1<<" - "<<2435+1<<endl;
	cerr<<toDigit("0030")+1<<" - "<<30+1<<endl;
	cerr<<toDigit("0341")+1<<" - "<<341+1<<endl;
	cerr<<toDigit("000524")+1<<" - "<<(int)524+1<<endl;
	cerr<<toDigit("531a5")+1<<" - "<<-1+1<<endl;
	cerr<<toDigit("43134l")+1<<" - "<<-1+1<<endl;
	cerr<<toDigit("jfkae")+1<<" - "<<-1+1<<endl;
	cerr<<toDigit("lo3")+1<<" - "<<-1+1<<endl;
	*/

/*	//exponent Testing
	cerr<<exponent(3,2)<<" - "<<3*3<<endl;
	cerr<<exponent(6,4)<<" - "<<6*6*6*6<<endl;
	cerr<<exponent(2,6)<<" - "<<2*2*2*2*2*2<<endl;
	cerr<<exponent(7,2)<<" - "<<7*7<<endl;
	cerr<<exponent(0,2)<<" - "<<0<<endl;
	cerr<<exponent(3,0)<<" - "<<1<<endl;
	cerr<<exponent(10,5)<<" - "<<10*10*10*10*10<<endl;
	cerr<<exponent(9,3)<<" - "<<9*9*9<<endl;
*/

/*	//charCompare testing
	cerr<<charCompare('1',"1234567890")<<"true"<<endl;
	cerr<<charCompare('a',"1234567890")<<"false"<<endl;
	cerr<<charCompare('q',"qwertyuiop")<<"true"<<endl;
	cerr<<charCompare('1',"qwertyuiop")<<"false"<<endl;
	cerr<<charCompare('q',"asdfghjkl;")<<"false"<<endl;
	cerr<<charCompare('z',"zxcvbnm,. ")<<"true"<<endl;
	cerr<<charCompare('3',"1234567890")<<"true"<<endl;
	cerr<<charCompare('e',"NnSsWwEe")<<"true"<<endl;
	cerr<<charCompare('z',"badfhuie")<<"false"<<endl;
	cerr<<charCompare('l',"ioiqwernf")<<"false"<<endl;
	cerr<<charCompare('1',"1234567890")<<"true"<<endl;
*/

//Assigned Functions/////////////////////////////////////
/*	//isPathWellFormed testing
	cerr<<isPathWellFormed("W144")<<"false"<<endl;
	cerr<<isPathWellFormed("N2e1E01n0e2e1")<<"true"<<endl;
	cerr<<isPathWellFormed("W14")<<"true"<<endl;
	cerr<<isPathWellFormed("sn3")<<"false"<<endl;
	cerr<<isPathWellFormed("e1x")<<"false"<<endl;
	cerr<<isPathWellFormed("w2+n3")<<"false"<<endl;
	cerr<<isPathWellFormed("")<<"true"<<endl;
	cerr<<isPathWellFormed("W144E90s9w2")<<"false"<<endl;
	cerr<<isPathWellFormed("W14s3w90N3")<<"true"<<endl;
	cerr<<isPathWellFormed("W14s3w90N")<<"false"<<endl;
	cerr<<isPathWellFormed("n73sw3n10")<<"false"<<endl;
	cerr<<isPathWellFormed("n89s29w2")<<"true"<<endl;
	cerr<<isPathWellFormed("n")<<"false"<<endl;
	cerr<<isPathWellFormed("1")<<"false"<<endl;
	*/

// followSegment testing

/*	setSize(1,1);
	cerr<<"followSegment:"<<endl;
	cerr<<followSegment(1,1,'n',1)<<" "<<0<<endl;
	cerr<<followSegment(1,1,'W',50)<<" "<<0<<endl;
	cerr<<followSegment(5,5,'s',2)<<" "<<-1<<endl;
	draw(1,1,1,1);
	*/
/*	setSize(1,2);
	setWall(1,2);
	cerr<<followSegment(1,1,'e',1)<<" "<<0<<endl;
	cerr<<followSegment(1,1,'e',50)<<" "<<0<<endl;
	cerr<<followSegment(1,2,'w',2)<<" "<<-1<<endl;
	draw(sr,sc, 1,1);
	*/

/*	setSize(20,20);
	int col=18;
	for(int i=1;i<19;i++){
		setWall(i,18);
	}
	cerr<<followSegment(5,5,'e',50)<<" "<<12<<endl;
	cerr<<followSegment(5,5,'S',50)<<" "<<15<<endl;
	cerr<<followSegment(5,5,'N',50)<<" "<<4<<endl;
	cerr<<followSegment(5,5,'W',50)<<" "<<4<<endl;
	cerr<<followSegment(20,5,'E',50)<<endl;
	cerr<<followSegment(5,5,'E',11)<<endl;
	cerr<<followSegment(0,1,'w',10)<<endl;
	cerr<<followSegment(1,0,'w',10)<<endl;
	cerr<<followSegment(-10,5,'W',10)<<endl;
	cerr<<followSegment(30,5,'w',10)<<endl;
	cerr<<followSegment(5,-10,'W',10)<<endl;
	cerr<<followSegment(5,30,'W',10)<<endl;
	cerr<<followSegment(10,10,'4',10)<<endl;
	cerr<<followSegment(10,10,'s',-10)<<endl;

	draw(sr,sc,er,ec);
*/
	
/*
	int nsteps=-1;

	//for followPath testing
	setSize(10,10);
	int col=2;
	for(int i=1;i<10;i++){
		setWall(i,col);
	}
	col=7;
	for(int i=2;i<11;i++){
		setWall(i,col);
	}
	cerr<<followPath(4,1,10,10,"N10e2S5sW10",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(0,1,1,1,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(1,0,1,1,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(1,1,0,1,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(1,1,1,0,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(-10,1,10,10,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(20,1,10,10,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(1,-10,10,10,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(1,20,10,10,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(1,1,-10,10,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(1,1,20,10,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(1,1,10,-10,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(1,1,10,20,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(1,2,10,10,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(1,1,1,2,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl<<"---"<<endl;

	cerr<<followPath(4,1,10,10,"s50E50N50e50s50",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(4,1,10,10,"N50s5N50e50s50",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(4,1,10,10,"W30s4N1e50s50",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(1,8,10,10,"e50s3n1s2",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(4,1,10,10,"s7E3",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(4,1,10,10,"s6E6S3",nsteps)<<" nSteps: ";cerr<<nsteps<<endl<<"---"<<endl;

	cerr<<followPath(4,1,10,10,"s6e5N9e3S9",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(4,1,10,10,"",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(4,1,10,10,"s6e5N9e4S9",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	cerr<<followPath(4,1,4,1,"N1S1",nsteps)<<" nSteps: ";cerr<<nsteps<<endl;
	draw(sr,sc, er,ec); 
	*/

	//cerr<<endl<<endl<<"followPath: "<<followPath(4,1,4,1,"",nsteps)<<endl<<endl;
	//cerr<<endl<<endl<<"followSegment: "<<followSegment(10,10,'s',-0)<<endl<<endl;
	//cerr<<endl<<endl<<"isWellFormed: "<<isPathWellFormed("N2e1E01n0e20w1") <<endl<<endl;
	
	//cerr<<"nsteps: "<<nsteps<<endl;
}


bool isPathWellFormed(string path){
	
	const int dir=0; //expecting the char to be from the string "NnSsEeWw"
	const int num=1; //expecting the char to be from the string "1234567890"
	const int either=2; //expecting a char from either string

	int maxDigits=2; //increase this value to increase the amount of allowed digits per line segment

	int expecting=dir; //holds the kind of character expected for the next position in the string
	int digits=0; //amount of digits that it has counted thus far for a path segment (cannot be more than two)

	for(int i=0; i<path.length(); i++){ //cycles through each character, checking for the expected characters

		if(expecting==dir){ //expecting a direction character?
			if(charCompare(path.at(i),"NnSsEeWw")){ //check if character is a direction character and move on to next character if true, otherwise return false
				digits=0;
				expecting=num; //only a number can come after a direction character
				continue;
			}else{
				return false;
			}
		}
		else if(expecting==num){ //expecting a number character?
			if(charCompare(path.at(i),"1234567890")){ //check if character is a number character and move on to next character if true, otherwise return false
				expecting=either; //a number or direction character can come after a number
				digits++;
				
				continue;
			}
			else{
				return false;
			}
		}
		else if(expecting==either){ //expecting a number or a character
			if(charCompare(path.at(i),"1234567890")){ //check if character is a number character and move on to next character if true
				expecting=either; //a number or direction character can come after a number
				digits++;
				if(digits>maxDigits)return false; //return false if the amount of digits in this line segment is too many
				continue;
			}
			else if(charCompare(path.at(i),"NnSsEeWw")) {//check if character is a direction character and move on to next character if true
				digits=0;
				expecting=num; //only a number can come after a direction character
				continue;
			}
			else{ //if the character is not a number or a direction character, return false
				return false;
			}
		}
	}
	if(expecting==num) //if it cycles through the for loop and expects a number aftergetting through the string (a number is only expected after a direction character, so if a number is expected, then the last character in the string must be a direction, which is invalid)
		return false; //return false

	return true; //if it cycles through the for loop and does not return false anywhere, return true;
}

int followSegment(int r, int c, char dir, int maxSteps){
	if(r>getRows()|| //if rows r is greater than the total amount of rows in the grid OR
		c>getCols()|| //if cols c is greater than the total amount of cols in the grid OR
		r<=0|| //if rows r is less than or equal to zero OR
		c<=0|| //if cols c is less than or equal to zero OR
		isWall(r,c)|| //if the starting position (r,c) is a wall OR
		!(charCompare(dir,"NnSsEeWw"))|| //if the direction character is not a valid direction character OR
		maxSteps<0 //if the max steps is less than zero (negative)
		){
			return -1; //then return -1
	}

	int stepsTaken=0; //keep track of the steps taken thus far

	for (int i=0;i<maxSteps;i++){

		switch(dir){ //increment or decrement rows or columns depending on the direction the robot is heading
		case 'N':
		case 'n':
			r--;
			break;
		case 'S':
		case 's':
			r++;
			break;
		case 'E':
		case 'e':
			c++;
			break;
		case 'W':
		case 'w':
			c--;
			break;
		}
		if(r<=0|| //check if robot would be outside grid
			c<=0|| //
			r>getRows()|| //
			c>getCols()|| //
			isWall(r,c)) //check if the robot would be at a wall after the amount of steps. 
			break; //if true, stop checking the statement

		stepsTaken++; // increase the amount of steps taken if the current space is not a wall
	}

	return stepsTaken; //return the amount of steps taken after finishing the for loop
}
int followPath(int sr, int sc, int er, int ec, string path, int& nsteps){
	//cerr<<"is path well formed!? "<<isPathWellFormed(path)<<endl;
	if(sr<=0|| //check if starting point is outside the grid
		sc<=0|| //
		sr>getRows()|| //
		sc>getCols()|| //
		isWall(sr,sc)|| //check if the starting point is on a wall space
		er<=0|| //check if ending point is outside the grid
		ec<=0|| //
		er>getRows()|| //
		ec>getCols()|| //
		isWall(er,ec)|| //check if the ending point is on a wall space
		!isPathWellFormed(path) //check if path string is well formed
		){
		return 3; //return 3 if the starting or ending point is in an invalid spot or if path string is invalid
	}
	
	int stepsTaken=0; //count the total amount of steps that the robot has taken so far

	int currRow=sr; //the current row that the robot is in
	int currCol=sc; //the current col that the robot is in
	
	//keeping track of the current segment
	char direction; //direction for current segment
	string num=""; //amount of steps for the current statement
	//path is definitely syntactically valid at this point
	for(int i=0;i<path.length();i++){ //cycle through the path string characters
		if(charCompare(path.at(i),"NnSsEeWw")){ //if it is a direction character, store it
			direction=path.at(i);
		}
		else if(charCompare(path.at(i),"1234567890")){ //if it is a number, put it in the number string
			num+=path.at(i);
		}

		if((i+1<path.length()&&charCompare(path.at(i+1),"NnSsEeWw"))|| //if there is a next character in the string AND it is a character OR
			(i+1==path.length())) //if there are no more characters left
		{ 
			//evaluate the amount of steps for the current line segment
			int steps=followSegment(currRow,currCol,direction,toDigit(num));

			switch(direction){ 
			case 'N':	//if the direction is north, move up the amount of steps
			case 'n':
				currRow-=steps;
				break;
			case 'S':	//if the direction is south, move down the amount of steps
			case 's':
				currRow+=steps;
				break;
			case 'E':	//if the direction is east, move right the amount of steps
			case 'e':
				currCol+=steps;
				break;
			case 'W':	//if the direction is west, move left the amount of steps
			case 'w':
				currCol-=steps;
				break;
			}

			stepsTaken+=steps; //add the move of steps for the segment to the total amount of steps taken

			if(steps<toDigit(num)){ //if the amount of steps taken is less than the amount of steps from the instructions (meaning the robot must have hit a wall)
				nsteps=stepsTaken;
				return 2;
			}

			num=""; //reset the line segment number variable
		}
	}
	nsteps=stepsTaken;
	if(currRow==er&&currCol==ec) //if, after properly cycling through the instructions path without issue, the column and row is the same as the end point
	{	
		return 0;
	}
	else
	{
		return 1;
	}
}


bool charCompare(char c, string str){
	//check if character c is within string str and return true if it is
	for(int i=0; i<str.length();i++){
		if(c==str.at(i))
			return true; // return true if the character is within the string
	}
	return false; //otherwise return false
}

int toDigit(string n){
	//take a number character and convert it into an integer
	int number=0;

	for(int i=0;i<n.length();i++){
		if(charCompare(n.at(i),"1234567890")){ //the character is a number
			number+=(int)(n.at(i)-'0')*exponent(10,n.length()-1-i); //add it to the total number
		}else{ //if the character is not a number
			return -1; //return -1
		}
	}
	return number; //if the loop finishes properly, return the number
}

int exponent(int n,int exp){
	//calculate the value for "n^exp" -- for integers only
	int number=1;
	for(int i=0;i<exp;i++){
		number*=n;
	}
	return number;
}
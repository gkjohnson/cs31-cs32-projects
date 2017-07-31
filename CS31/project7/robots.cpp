// robots.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows in the arena
const int MAXCOLS = 40;             // max number of columns in the arena
const int MAXROBOTS = 200;          // max number of robots allowed

const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
void clearScreen();


///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
              // type name, since it's mentioned in the Robot declaration.

int dangerVal(const int r,const int c, const Arena* a);
class Robot
{
  public:
        // Constructor
    Robot(Arena* ap, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
};

class Player
{
  public:
        // Constructor
    Player(Arena *ap, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;

        // Mutators
    string takeComputerChosenTurn();
    void   stand();
    void   move(int dir);
    bool   shoot(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;
};

class Arena
{
  public:
        // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     robotCount() const;
    int     nRobotsAt(int r, int c) const;
    void    display(string msg) const;

        // Mutators
    bool   addRobot(int r, int c);
    bool   addPlayer(int r, int c);
    bool   destroyRobot(int r, int c);
    bool   moveRobots();

  private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Robot*  m_robots[MAXROBOTS];
    int     m_nRobots;
};

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();

        // Mutators
    void play();

  private:
    Arena* m_arena;
};

///////////////////////////////////////////////////////////////////////////
//  Robot implementation
///////////////////////////////////////////////////////////////////////////

Robot::Robot(Arena* ap, int r, int c)
{
    if (ap == NULL)
    {
        cout << "***** A robot must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
}

int Robot::row() const
{
    return m_row; //return the row of the robot
}

int Robot::col() const
{
    return m_col; //return the col of the robot
}

void Robot::move()
{
      // Attempt to move in a random direction; if we can't move, don't move
    switch (rand() % 4)
    {
      case UP:
		if(row()>1){ //if robot is below uppermost row (one) then move up
			m_row--;
		}
		break;
      case DOWN:
		if(row()<m_arena->rows()){ //if robot is above the bottom row then move down
			m_row++;
		}
		break;
      case LEFT:
		if(col()>1){ //if robot is to the right of the leftmost col (one) then move left
			m_col--;
		}
		break;
      case RIGHT:
		if(col()<m_arena->cols()){ //if robot is to the left of the rightmost row then move right
			m_col++;
		}
        break;
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == NULL)
    {
        cout << "***** The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return this->m_row; //return the row that the player is in
}

int Player::col() const
{
    return this->m_col; //return the col that the player is in
}

int Player::age() const
{
    return this->m_age; //return the age of the player
}

string Player::takeComputerChosenTurn()
{
	const int STAND=4;
	int dangerNum[5]; //keep track of amount of robots that may step into that space on the next turn
	dangerNum[UP]=dangerVal(row()-1,col(),this->m_arena);
	dangerNum[DOWN]=dangerVal(row()+1,col(),this->m_arena);
	dangerNum[LEFT]=dangerVal(row(),col()-1,this->m_arena);
	dangerNum[RIGHT]=dangerVal(row(),col()+1,this->m_arena);
	dangerNum[STAND]=dangerVal(row(),col(),this->m_arena);

	if(dangerNum[STAND]==0){ //if the play is not in danger while standing, don't move and shoot if possible
		int dirToShoot=-1; //save the direction of the nearest bot
		int distToBot=100000; //save the distance to the nearest bot

		for(int i=1;i<=m_arena->rows();i++){ // check if character can shoot vertically
			if(m_arena->nRobotsAt(i,col())>0){
				int dist=row()-i;
				if(dist>0&&distToBot>dist){ // if a robot is found in this direction, save the distance and direction
					dirToShoot=UP;
					distToBot=dist;
				}else if(dist<0&&distToBot>-dist){
					dirToShoot=DOWN;
					distToBot=-dist;
				}
			}
		}
		for(int i=1;i<=m_arena->cols();i++){ // check if character can shot horizonatally
			if(m_arena->nRobotsAt(row(),i)>0){
				int dist=col()-i;
				if(dist>0&&distToBot>dist){ //if a robot is found in this direction, save the distance and direction
					dirToShoot=LEFT;
					distToBot=dist;
				}else if(dist<0&&distToBot>-dist){
					dirToShoot=RIGHT;
					distToBot=-dist;
				}
			}
		}

		if(dirToShoot!=-1){ //if a robot could be shot at
			if(shoot(dirToShoot)){ //shoot
				return "Shot and hit!";
			}else{
				return "Shot and missed!";
			}
		}else{ //otherwise, stand
			stand();
			return "Stood.";
		}
	}

	for(int i=0;i<5;i++){ //if one direction leads to a wall, set the danger to high so that it will not step in that direction and potentially get stepped on by a bot
		if(dangerNum[i]==-1){
			dangerNum[i]=MAXROBOTS;
		}
	}

	int safest=4;
	for(int i=0;i<5;i++){ //find the safest direction to move in
		if(dangerNum[safest]>=dangerNum[i]){
			safest=i;
		}
	}

	move(safest); //move in the safest direction
	return "Moved.";

}

void Player::stand()
{
    m_age++;
}


void Player::move(int dir)
{
	m_age++;
    switch (dir)
    {
      case UP:
		if(row()>1){ //if player is below uppermost row (zero) then move up
			m_row--;
		}
        break;
      case DOWN:
		if(row()<m_arena->rows()){ //if robot is above the bottom row then move down
			m_row++;
		}
		break;
      case LEFT:
		if(col()>1){ //if robot is to the right of the leftmost col (zero) then move left
			m_col--;
		}
		break;
      case RIGHT:
		if(col()<m_arena->cols()){ //if robot is to the left of the rightmost row then move right
			m_col++;
		}
        break;
    }
}

bool Player::shoot(int dir)
{
    m_age++;

    if (rand() % 3 != 0)  // miss with 2/3 probability
        return false;
		
    int moveR=0; //amount to move in the rows direction
	int moveC=0; //amount to move in the cols direction

	switch(dir){ //set the appropriate values for directions in rows and cols
	case UP:
		moveR=-1;
		moveC=0;
		break;
	case DOWN:
		moveR=1;
		moveC=0;
		break;
	case LEFT:
		moveR=0;
		moveC=-1;
		break;
	case RIGHT:
		moveR=0;
		moveC=1;
		break;
	}

	int currR=row(); //set current row to player's row
	int currC=col(); //set current col to player's col

	while(currR>=1&& //while the bullet (position to be checked) is still within the arena
		currR<=m_arena->rows()&&
		currC>=1&&
		currC<=m_arena->cols()){

		if(m_arena->destroyRobot(currR,currC)){ //try to destroy a robot at the grid (will return true if there is a robot there)
			return true;
		}

		currR+=moveR;
		currC+=moveC;
	}
    return false; //return false if it never runs into a robot
}

bool Player::isDead() const
{
	return this->m_dead; //return the state of the player
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementations
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = NULL;
    m_nRobots = 0;
}

Arena::~Arena()
{
	delete m_player; // delete the dynamically allocated player
	for(int i=0;i<robotCount();i++){ //delete the dynamically allocated robots
		delete m_robots[i];
	}
}

int Arena::rows() const
{
    return this->m_rows; //return the amount of rows in the arena
}

int Arena::cols() const
{
    return this->m_cols; //return the amount of cols in the arena
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::robotCount() const
{
    return m_nRobots;
}

int Arena::nRobotsAt(int r, int c) const
{
    int num=0;
	for(int i=0;i<this->robotCount();i++){ //cycle through each robot
		if(m_robots[i]->col()==c&& //if the robot is in the right spot
			m_robots[i]->row()==r){
				num++; //increment the counter
		}
	}
    return num; //return the amount of robots at the grid space
}

void Arena::display(string msg) const
{
      // Position (row,col) in the arena coordinate system is represented in
      // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
        // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';

        // Indicate each robot's position
	for(int i=0;i<robotCount();i++){
		int rC=m_robots[i]->col()-1; //robots position in the ARRAY (grid space 1,1 is represented at [0][0])
		int rR=m_robots[i]->row()-1;
		
		if(grid[rR][rC]=='.'){ //if there are no robots at the spot, set it to display a single robot
			grid[rR][rC]='R';
		}else if(grid[rR][rC]=='R'){ //if there is one robot at the spot already, set it to display two robots
			grid[rR][rC]='2';
		}else if(isdigit(grid[rR][rC])){ //if there is more than one robot at the spot already
			if((int)(grid[rR][rC]-'0')<9){ //and the amount is less than 9, add one robot to the spot
				grid[rR][rC]=grid[rR][rC]+1;
			}else if((int)(grid[rR][rC]-'0')>=9){// otherwise set it to 9
				grid[rR][rC]='9';
			}
		}
	}

    // Indicate player's position
    if (m_player != NULL)
    {
          // Set the char to '@', unless there's also a robot there,
          // in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

        // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

        // Write message, robot, and player info
    cout << endl;
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << robotCount() << " robots remaining." << endl;
    if (m_player == NULL)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Arena::addRobot(int r, int c)
{
	if(this->robotCount()>=MAXROBOTS){ //if there are already more robots then allowed then return false
		return false;
	}
	m_robots[robotCount()]=new Robot(this,r,c); //add a robot in the next available spot
	m_nRobots++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
      // Don't add a player if one already exists
    if (m_player != NULL)
        return false;

      // Dynamically allocate a new Player and add it to the arena
    m_player = new Player(this, r, c);
    return true;
}


bool Arena::destroyRobot(int r, int c)
{
    // CHECK
	int i=0;
	bool deleted=false; //if a robot has been deleted

	while(i<m_nRobots){
		if(m_robots[i]->col()==c&&m_robots[i]->row()==r&&!deleted){ // if it fits the criteria (row/col)
			delete m_robots[i];  //delete it and save that a robot has been deleted
			deleted=true;
		}
		if(deleted&&(i+1)<m_nRobots){ //While a robot has been deleted and the next element is not past the amount of robots
			m_robots[i]=m_robots[i+1]; //Move the robot pointers one to the left
		}
		i++;
	}
	if(deleted){ //if after looking through the robots a robot was deleted
		m_robots[i]=NULL; //remove the pointer that would be a duplicate pointer
		m_nRobots--;
		return true;
	}
    return false;
}

bool Arena::moveRobots()
{
    for (int k = 0; k < m_nRobots; k++) //cycle through the available robots
    {
		m_robots[k]->move(); //move each
		if(player()->row()==m_robots[k]->row()&&player()->col()==m_robots[k]->col()){ //if the robot is on the same space as the player
			player()->setDead(); // kill the player
		}
    }
    // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nRobots)
{
    if (1 + nRobots > rows * cols)
    {
        cout << "***** Game created with a " << rows << " by "
             << cols << " arena, which is too small too hold a player and "
             << nRobots << " robots!" << endl;
        exit(1);
    }

        // Create arena
    m_arena = new Arena(rows, cols);

        // Add player
    int rPlayer = 1 + rand() % rows;
    int cPlayer = 1 + rand() % cols;
    m_arena->addPlayer(rPlayer, cPlayer);

      // Populate with robots
    while (nRobots > 0)
    {
        int r = 1 + rand() % rows;
        int c = 1 + rand() % cols;
          // Don't put a robot where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_arena->addRobot(r, c);
        nRobots--;
    }
}

Game::~Game()
{
    delete m_arena;
}

void Game::play()
{
    Player* p = m_arena->player();
    if (p == NULL)
    {
        m_arena->display("");
        return;
    }
    string msg = "";
    do
    {
        m_arena->display(msg);
        msg = "";
        cout << endl;
        cout << "Move (u/d/l/r/su/sd/sl/sr/c//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)
            p->stand();
        else
        {
            switch (action[0])
            {
              default:   // if bad move, nobody moves
                cout << '\a' << endl;  // beep
                continue;
              case 'q':
                return;
              case 'c':  // computer moves player
                msg = p->takeComputerChosenTurn();
                break;
              case 'u':
              case 'd':
              case 'l':
              case 'r':
                p->move(decodeDirection(action[0]));
                break;
              case 's':
                if (action.size() < 2)  // if no direction, nobody moves
                {
                    cout << '\a' << endl;  // beep
                    continue;
                }
                switch (action[1])
                {
                  default:   // if bad direction, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                  case 'u':
                  case 'd':
                  case 'l':
                  case 'r':
                    if (p->shoot(decodeDirection(action[1])))
                        msg = "Hit!";
                    else
                        msg = "Missed!";
                    break;
                }
                break;
            }
        }
        m_arena->moveRobots();
    } while ( ! m_arena->player()->isDead()  &&  m_arena->robotCount() > 0);
    m_arena->display(msg);
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int dangerVal(const int r, const int c, const Arena* a){

	if(r>a->rows()||
		r<1||
		c>a->cols()||
		c<1){

			return -1;
	}

	int val=0;
	//check above current space
	val+=a->nRobotsAt(r-1,c);
	//check below current space
	val+=a->nRobotsAt(r+1,c);
	//check to the left of the current space
	val+=a->nRobotsAt(r,c-1);
	//check to the right of the current space
	val+=a->nRobotsAt(r,c+1);
	//the space is up against a "wall", include robots that are standing on the space in the value, because they may not move from that space
	//val+=a->nRobotsAt(r,c);
	if(r==1||
		r==a->rows()||
		c==1||
		c==a->cols()){
		val+=a->nRobotsAt(r,c);
	}

	return val;
}


int decodeDirection(char dir)
{
    switch (dir)
    {
      case 'u':  return UP;
      case 'd':  return DOWN;
      case 'l':  return LEFT;
      case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <cstring>

void clearScreen()
{
    static const char* term = getenv("TERM");
    static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
    if (term == NULL  ||  strcmp(term, "dumb") == 0)
        cout << endl;
     else
        cout << ESC_SEQ << "2J" << ESC_SEQ << "\x1B[H" << flush;
}

#endif


///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

/*void test1(){
	//REMEMBER TO SET THE GAME CONSTRUCTOR BACK TO MAKING A NEW PLAYER AND DELETE THE GAMES ARENA FUNCTION
	{
		Game g(10,10,0);
		Arena* a=g.arena();
		a->addPlayer(5,10);
		
		a->addRobot(5,3);
		a->addRobot(5,5);
		a->addRobot(5,7);
		g.play();
	}
	
	{
		Game g(10,10,0);
		Arena* a=g.arena();
		a->addPlayer(5,5);
		a->addRobot(6,5);
		a->addRobot(4,5);
		a->addRobot(5,6);
		a->addRobot(5,4);
		g.play();
	}
	{
		Game g(10,10,0);
		Arena* a=g.arena();
		a->addRobot(6,5);
		a->addRobot(4,5);
		a->addRobot(5,6);
		a->addRobot(5,4);
		g.play();
	}
	{
		Game g(10,10,0);
		Arena* a=g.arena();
		a->addPlayer(5,5);
		a->addRobot(4,5);
		a->addRobot(5,6);
		a->addRobot(5,4);
		g.play();
	}
	{
		Game g(10,10,0);
		Arena* a=g.arena();
		a->addPlayer(5,5);
		a->addRobot(6,5);
		a->addRobot(4,5);
		a->addRobot(5,4);
		g.play();
	}
	{
		Game g(10,10,0);
		Arena* a=g.arena();
		a->addPlayer(5,5);
		a->addRobot(6,5);
		a->addRobot(4,5);
		a->addRobot(5,6);
		g.play();
	}
	{
		Game g(10,10,0);
		Arena* a=g.arena();
		a->addPlayer(1,1);
		a->addRobot(1,2);
		a->addRobot(2,1);
		g.play();
	}
	{
		Game g(10,10,0);
		Arena* a=g.arena();
		a->addPlayer(1,5);
		a->addRobot(2,5);
		a->addRobot(1,6);
		a->addRobot(1,4);
		g.play();
	}
	{
		Game g(10,10,0);
		Arena* a=g.arena();
		a->addPlayer(10,5);
		a->addRobot(9,5);
		a->addRobot(10,6);
		a->addRobot(10,4);
		g.play();
	}
	{
		Game g(10,10,0);
		Arena* a=g.arena();
		a->addPlayer(5,1);
		a->addRobot(5,2);
		a->addRobot(4,1);
		a->addRobot(6,1);
		g.play();
	}
	{
		Game g(10,10,0);
		Arena* a=g.arena();
		a->addPlayer(5,10);
		a->addRobot(5,9);
		a->addRobot(4,10);
		a->addRobot(6,10);
		g.play();
	}
	{
		Game g(10,10,0);
		Arena* a=g.arena();
		a->addPlayer(5,10);
		for(int i=0;i<20;i++){
			a->addRobot(10,10);
		}
		g.play();
	}
}*/

int main()
{
      // Initialize the random number generator.  (You don't need to
      // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));

      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 3, 2);
    Game g(15, 18, 50);

      // Play the game
    g.play();
}
#include "Actor.h"
#include "World.h"
#include <cstdlib>

// Your code goes here

//Actor Functions
Actor::Actor(World* w, int x, int y, int id, colors c)
	:m_world(w), m_x(x), m_y(y), m_id(id), m_color(c), m_dir(NONE)
{}

//NachMan Functions
NachMan::NachMan(World* w, int x, int y)
	:Actor(w,x,y,ITEM_NACHMAN,YELLOW), m_lives(3), m_score(0)
{}
void NachMan::DoSomething()
{
	//PLAYER INPUT
	char ch;

	//Get a character
	if(getCharIfAny(ch)){
		GridContents gc;
		Direction d;

		//Get the gridContents at each grid space in each direction
		//save the direction that the arrow corresponds with
		switch(ch){
		case ARROW_LEFT:
			gc=GetWorld()->GetMaze()->GetGridContents(GetX()-1,GetY()); //grid space to the LEFT
			d=WEST;
			break;
		case ARROW_RIGHT:
			gc=GetWorld()->GetMaze()->GetGridContents(GetX()+1,GetY()); //grid space to the RIGHT
			d=EAST;
			break;
		case ARROW_UP:
			gc=GetWorld()->GetMaze()->GetGridContents(GetX(),GetY()-1); //grid space to UP
			d=NORTH;
			break;
		case ARROW_DOWN:
			gc=GetWorld()->GetMaze()->GetGridContents(GetX(),GetY()+1); //grid space to DOWN
			d=SOUTH;
			break;
		}

		switch(ch){ //if the arrow corresponds to an appropriate direction
		case ARROW_LEFT:
		case ARROW_RIGHT:
		case ARROW_UP:
		case ARROW_DOWN:
			if(gc!=WALL&&gc!=CAGEDOOR){ //and the the contents at the corresponding space are not a WALL or a CAGEDOOR(meaning Nachman can move there)
				setDir(d); //set the direction of Nachman to the appropriate direction
			}
		}
	}

	//MOVEMENT
	{
		int nextX=GetX(); //get the current position of Nachman
		int nextY=GetY();

		switch(getDir()){ //change the nextX and nextY variable to the appropriate grid space based off the direction
		case WEST:
			nextX--; //set one grid space to the LEFT (negative X)
			break;
		case EAST:
			nextX++; //set one grid space to the RIGHT (positive X)
			break;
		case NORTH:
			nextY--; //set one grid space to UP (negative Y)
			break;
		case SOUTH:
			nextY++; //set one grid space to DOWN (positive Y)
			break;
		}

		GridContents gc=GetWorld()->GetMaze()->GetGridContents(nextX,nextY); //get the grid contents of the new space

		if(gc!=WALL&&gc!=CAGEDOOR){ //if Nachman can move the to the next space (meaning it is not a WALL or a CAGEDOOR)
			SetX(nextX); //set Nachman's position to the next space
			SetY(nextY);
		}
	}

	//PELLET EATING
	{
		GridContents gc=GetWorld()->GetMaze()->GetGridContents(GetX(),GetY()); // get the gridcontents at Nachman's current spot
		
		//SMALL PELLET
		if(gc==PELLET){	
			addToScore(10); //add score of 10 for eating a pellet
			GetWorld()->GetMaze()->SetGridContents(GetX(),GetY(),EMPTY); //set the grid space to empty (so it cannot be eaten again)
			SoundFX::playNachManSound(PAC_SOUND_SMALL_EAT); //play "small pellet" sound
		//POWER PELLET
		}else if(gc==POWERPELLET){
			addToScore(100); //add score of 100 for eating a power pellet
			GetWorld()->GetMaze()->SetGridContents(GetX(),GetY(),EMPTY); //set the grid space to empty (so it cannot be eaten again)
			SoundFX::playNachManSound(PAC_SOUND_BIG_EAT); //play "power pellet" sound

			//update all the monster's states to be vulnerable if applicable
			for(int i=0; i<NUM_MONSTERS;i++){
				if(GetWorld()->GetMonster(i)->GetState()==NORMAL||GetWorld()->GetMonster(i)->GetState()==VULNERABLE){
					GetWorld()->GetMonster(i)->SetState(VULNERABLE); //this function takes care of setting the amound of vulnerable ticks
				}
			}
		}
	}
	
	//MONSTER HIT CHECKS
	for(int i=0;i<NUM_MONSTERS;i++){
		hitMonsterCheck(GetWorld()->GetMonster(i));
	}
}
bool NachMan::hitMonsterCheck(Monster* m){
	//Check if Nachman has hit the passed Monster

	if(m->GetX()==GetX()&&m->GetY()==GetY()){ //check if Nachman is on the same space as the monster
		if(m->GetState()==VULNERABLE){ //if the monster's state is set to vulnerable
			m->eaten(); //eat it (sets state to MONSTER_DIED)
			addToScore(1000); //add 1000 to score for eating the monster
		}else if(m->GetState()==NORMAL){ //if the monster is in a normal state
			setDead(); //set Nachman's state to dead
		}
		return true;
	}
	return false;
}

//Monster Functions
Monster::Monster(World* w, int x, int y, int id, colors c)
	:Actor(w, x, y, id, c), m_state(NORMAL), m_vulnerableTicks(0), destX(0),destY(0)
{}
colors Monster::GetDisplayColor() const
{
	//return the the color of the monster according to the Monster's state

	if(m_state==RETURN_HOME||m_state==MONSTER_DIE){
		return LIGHTGRAY; //monster is Light Gray if it is returning home or has Died
	}else if(m_state==VULNERABLE){
		return LIGHTBLUE; //if the monster is vulnerable
	}
	return Actor::GetDisplayColor(); //otherwise, display the monster as its default color
}
void Monster::decrementVulnerability()
{
	//decrement the monster's vulnerability ticks if it has them. If there are no more ticks, set the state to normal
	if(m_vulnerableTicks>0){
		m_vulnerableTicks--;
	}
	if(m_vulnerableTicks==0){
		m_state=NORMAL;
	}
}
void Monster::DoSomething()
{
	if(m_state==NORMAL||m_state==VULNERABLE)
	{
		//decrement the amount of vulnerable ticks and set the state to normal if appropriate
		decrementVulnerability();
		//pick the Monster's desired destination and move it in the direction of it
		decideDest();
		move();
		//check if the Monster has hit Nachman
		hitNachmanCheck();
	}
	else if(m_state==RETURN_HOME)
	{
		//if the Monster is to return home, find the next coordinate for it to move
		int x=GetX();
		int y=GetY();
		if(GetWorld()->GetMaze()->GetNextCoordinate(x,y,x,y)){
			SetX(x);
			SetY(y);
		}else{
			//if GetNextCoordinate return false, that means it is back at its home space, meaning the state should be set to normal
			SetState(NORMAL);
		}
	}
	else if(m_state==MONSTER_DIE)
	{
		//while the monster is in the monster die state, the m_vulnerable ticks must be set to 0
		m_vulnerableTicks=0;
		//the state should be set to RETURN_HOME right away
		m_state=RETURN_HOME;
		//the sound corresponding to an eaten monster is played
		SoundFX::playNachManSound(PAC_SOUND_BIG_EAT);
	}
}
void Monster::move()
{
	//Move algorithm follows that which is specified in the Spec

	//1 and 2 for the movement algorithm
	//if the destination is NOT in the same column (destination is EAST or WEST)
	if(GetX()!=destX){
		if(GetX()>destX) //destination is to the WEST
		{
			if(GetWorld()->GetMaze()->GetGridContents(GetX()-1,GetY())!=WALL&& //Check if the Monster can move one space to the LEFT without hitting a wall or turning around
				getDir()!=EAST)
			{
				SetX(GetX()-1); //Move the Monster if possible and remember that it moved WEST
				setDir(WEST);
				return;
			}
		}else if(GetX()<destX) //destination is to the EAST
		{
			if(GetWorld()->GetMaze()->GetGridContents(GetX()+1,GetY())!=WALL&& //Check if the Monster can move one space to the RIGHT without hitting a wall or turning around
				getDir()!=WEST)
			{
				SetX(GetX()+1); //Move the Monster if possible and remember that it moved EAST
				setDir(EAST);
				return;
			}
		}
	}
	//3 and 4 for the movement algorithm
	//if the destination is NOT in the same row (destination is NORTH or SOUTH) 
	if(GetY()!=destY){
		if(GetY()>destY) //destination is NORTH
		{
			if(GetWorld()->GetMaze()->GetGridContents(GetX(),GetY()-1)!=WALL&& //Check if the Monster can move one space to the UP without hitting a wall or turning around
				getDir()!=SOUTH)
			{
				SetY(GetY()-1); //Move the Monster if possible and remember that it moved NORTH
				setDir(NORTH);
				return;
			}
		}else if(GetY()<destY) //destination is to the SOUTH
		{
			if(GetWorld()->GetMaze()->GetGridContents(GetX(),GetY()+1)!=WALL&& //Check if the Monster can move one space to the DOWN without hitting a wall or turning around
				getDir()!=NORTH)
			{
				SetY(GetY()+1); //Move the Monster if possible and remember that it moved SOUTH
				setDir(SOUTH);
				return;
			}
		}
	}

	//5 and 6 for the movement algorithm
	//If the monster could not find a direction to move in, then pick a random direction
	Direction D=(Direction)(rand()%4);
	for(int i=0; i<4;i++){
		int newX=GetX();
		int newY=GetY();
		bool opposite=false;
		
		//save the flags associated with the direction (is it opposite/which direction on the axis does this take the monster)
		switch(D){
		case NORTH:
			newY--;
			if(getDir()==SOUTH){
				opposite=true;
			}
			break;
		case SOUTH:
			newY++;
			if(getDir()==NORTH){
				opposite=true;
			}
			break;
		case WEST:
			newX--;
			if(getDir()==EAST){
				opposite=true;
			}
			break;
		case EAST:
			newX++;
			if(getDir()==WEST){
				opposite=true;
			}
			break;
		}
		if(GetWorld()->GetMaze()->GetGridContents(newX,newY)==WALL || opposite){ //If it runs into a wall or must turn around in order to move this direction
			D=(Direction)(((int)D+1)%4); //then pick the next direction
			continue;
		}
		//if the direction worked, then move the monster and remember what direction was moved in
		SetX(newX);
		SetY(newY);
		setDir(D);
		return;
	}

	//7 from the movement algorithm
	//If the monster cannot move in any way without reversing direction, then move in reverse
	switch(getDir()){
	case NORTH:
		SetY(GetY()+1);
		setDir(SOUTH);
		break;
	case SOUTH:
		SetY(GetY()-1);
		setDir(NORTH);
		break;
	case EAST:
		SetX(GetX()-1);
		setDir(WEST);
		break;
	case WEST:
		SetX(GetX()+1);
		setDir(EAST);
		break;
	}
	return;

}
void Monster::eaten()
{
	this->SetState(MONSTER_DIE);
}
bool Monster::hitNachmanCheck()
{
	//use Nachman's Monster hit detection to check if the Monster hit Nachman so code is not repeated
	return GetWorld()->GetNachMan()->hitMonsterCheck(this);
}
void Monster::decideDest()
{
	//Decide where the Monster's next destination is based on the Monster's state

	if(m_state==NORMAL){
		whileNormal();
	}
	else if(m_state==VULNERABLE){
		whileVulnerable();
	}
}
void Monster::SetState(MonsterState m)
{
	//set the Monster's state the passed value
	m_state=m;

	//if the passed state was "Vulnerable"
	if(m==VULNERABLE){
		//set the Monster's vulnerable ticks accordingly
		if(GetWorld()->GetLevel()>8){
			m_vulnerableTicks=20;
		}else{
			m_vulnerableTicks=100-(GetWorld()->GetLevel())*10;
		}
	}
}

//Functions to decide where Monster's destination will be depending on the state. Both are virtual and can be overwritten in the derivitive classes as necessary
void Monster::whileNormal()
{
	//Default destination while the Monster's state is NORMAL is to grab a random coordinate and go there
	SetDest(rand()%MAZE_WIDTH,rand()%MAZE_HEIGHT);
}
void Monster::whileVulnerable(){
	//Default destination while the Monster's state is Vulnerable is to grab a random coordinate and go there
	SetDest(rand()%MAZE_WIDTH,rand()%MAZE_HEIGHT);
}

//Inky Functions
Inky::Inky(World* w, int x, int y)
	:Monster(w,x,y,ITEM_MONSTER1,LIGHTRED), m_decideTicks(0)
{}
void Inky::whileNormal(){
	//When decideTicks==0, then inky needs to decide what to do by picking a random number, and does it for 10 Ticks
	if(m_decideTicks>0){
		m_decideTicks--;
	}
	if(m_decideTicks==0){
		m_decideNum=rand()%100;
		m_decideTicks=10;
	} 
	//80% chance Inky will chase Nachman, otherwise he will just run around the maze
	if(m_decideNum<80){
		SetDest(GetWorld()->GetNachMan()->GetX(),GetWorld()->GetNachMan()->GetY());
	}else{
		Monster::whileNormal();
	}
}
//Inky uses the default WhileVulnerable function from Monster

//Stinky Functions
Stinky::Stinky(World* w, int x, int y)
	:Monster(w,x,y,ITEM_MONSTER2,LIGHTGREEN)
{}
void Stinky::whileNormal()
{
	//if Stinky is within 5 vertical and 5 horizontal spaces of Nachman, then set Nachman as his target
	if(abs(GetX()-(GetWorld()->GetNachMan()->GetX()))<=5 && abs(GetY()-(GetWorld()->GetNachMan()->GetY()))<=5 ){
		SetDest(GetWorld()->GetNachMan()->GetX(),GetWorld()->GetNachMan()->GetY());
	//Otherwise just run around the maze
	}else{
		Monster::whileNormal();
	}
}
//Stinky uses the default WhileVulnerable function from Monster

//Dinky Functions
Dinky::Dinky(World* w, int x, int y)
	:Monster(w,x,y,ITEM_MONSTER3,LIGHTMAGENTA)
{}
void Dinky::whileNormal()
{
	//If Dinky can SEE Nachman, his target is Nachman

	//save the current X and Y values of Dinky
	int currX=GetX();
	int currY=GetY();
	
	//get which direction Dinky would need to look in to see Nachman
	int xChange=0;
	int yChange=0;

	//if Nachman is in the same column as Dinky, but not the same row
	if(GetX()==GetWorld()->GetNachMan()->GetX()&&GetY()!=(GetWorld()->GetNachMan()->GetY())){
		//Then Dinky must be looking up or down the column
		yChange=(GetWorld()->GetNachMan()->GetY())-GetY();
		yChange=yChange/abs(yChange);
	}
	//if Nachman is in the same Row as Dinky, but not he same column
	else if(GetY()==GetWorld()->GetNachMan()->GetY()&&GetX()!=(GetWorld()->GetNachMan()->GetX())){
		//Then Dinky must be looking left or rightthe row
		xChange=(GetWorld()->GetNachMan()->GetX())-GetX();
		xChange=xChange/abs(xChange);
	}

	//if Dinky is looking in a direction
	if(xChange!=0||yChange!=0){
		//While the space that Dinky is looking at is not a WALL
		while(GetWorld()->GetMaze()->GetGridContents(currX,currY)!=WALL){
			//look at the next space
			currX+=xChange;
			currY+=yChange;
			//If the space is the same as Nachman's, then set him to the destination
			if(currX==GetWorld()->GetNachMan()->GetX()&&currY==GetWorld()->GetNachMan()->GetY()){
				SetDest(currX,currY);
				return;
			}
		}
	}
	//otherwise, just run around the maze
	Monster::whileNormal();
}
//Dinky uses the default WhileVulerable function from Monster

//Clyde Functions
Clyde::Clyde(World* w, int x, int y)
	:Monster(w,x,y,ITEM_MONSTER4,LIGHTCYAN)
{}
//Clyde uses the default WhileNormal function from Monster

void Clyde::whileVulnerable()
{
	//Get NachMan's Quadrant
	//by dividing Nachman's X and Y positions by the Width and Height of the Maze (decimals will be dropped because of int)
	int quadX=(GetWorld()->GetNachMan()->GetX())/(MAZE_WIDTH/2);
	int quadY=(GetWorld()->GetNachMan()->GetY())/(MAZE_HEIGHT/2);

	//Get Clyde's Desired Quadrant
	//There are only two quadrants in either X and Y direction, so change the quadrant from what Dinky is
	int cQuadX=(quadX+1)%2;
	int cQuadY=(quadY+1)%2;

	//values that will be set as the destination for Clyde (random numbers in the appropriate quadrant)
	int setX=cQuadX*((MAZE_WIDTH)/2+1)+rand()%((MAZE_WIDTH/2)+1-cQuadX);
	int setY=cQuadY*((MAZE_HEIGHT)/2+1)+rand()%((MAZE_HEIGHT/2)+1-cQuadY);

	//Set Clyde's destination to be a random x,y value in his desired quadrant
	SetDest(setX,setY);
}
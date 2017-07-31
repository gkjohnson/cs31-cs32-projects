#ifndef _ACTOR_H_
#define _ACTOR_H_

#include "testdefines.h"
#include "BGIgraphics.h"
#include "GraphManager.h"
#include "constants.h"

// Your code goes here

////////////////////
//Actor Base Class//
////////////////////

class World;

class Actor{
public:
	Actor(World* w, int x, int y, int id, colors c);
	virtual ~Actor(){};

	//Get and Set X and Y values
	int GetX() const {return m_x;}
	int GetY() const {return m_y;}
	void SetX(int newXCoord){m_x=newXCoord;}
	void SetY(int newYCoord){m_y=newYCoord;}
	
	//Return the ID of the Actor - tells if it is Nachman or which Monster
	int getMyID() const {return m_id;}

	//Get direction and set direction - keeps track of the direction that the Actor is moving in
	void setDir(Direction d){m_dir=d;}
	Direction getDir() const {return m_dir;}

	//Get a pointer to the world that the actor is in
	World* GetWorld() const{return m_world;}

	//return the current color to be displayed for the actor
	virtual colors GetDisplayColor() const {return m_color;}

	//the function that is called for all actors every frame in which they decide what to do
	virtual void DoSomething()=0;

private:
	int m_x;
	int m_y;
	int m_id;
	Direction m_dir;
	colors m_color;
	World* m_world;
};

///////////////////
//Derived Classes//
///////////////////
class Monster;

class NachMan:public Actor{
public:
	NachMan(World* w, int x, int y);
	virtual ~NachMan(){};

	//Get and decrement the number of lives Nachman has
	int GetNumLivesLeft() const {return m_lives;}
	void DecrementNumLives(){m_lives--;}

	//Get the score of the player
	int GetScore() const {return m_score;}

	//set whether Nachman is alive or dead
	void setAlive(){m_alive=true;}
	void setDead(){m_alive=false;}

	//check whether Nachman is dead or not
	bool isDead() const{return !m_alive;};

	//check whether the monster that is passed has been hit by Nachman, and then take an action accordingly
	bool hitMonsterCheck(Monster* m);

	virtual void DoSomething();

private:

	void addToScore(int s){m_score+=s;}
	int m_score;
	int m_lives;
	bool m_alive;
};

//MonsterState values that are used to keep track of the Monster's State
enum MonsterState
{NORMAL, VULNERABLE, MONSTER_DIE, RETURN_HOME};

class Monster:public Actor{
public:
	Monster(World* w, int x, int y, int id, colors c);
	virtual ~Monster(){}
	
	//Get and Set the monster's state from the above enum
	void SetState(MonsterState m);
	MonsterState GetState() const{return m_state;}

	//Set the destination of the Monster (where it wants to go - decided by algorithms)
	void SetDest(int x, int y){destX=x; destY=y;}

	//Decides the destination for the monster while it is in a vulnerable or normal state
	void decideDest();
	virtual void whileNormal();
	virtual void whileVulnerable();

	//Move function algorithm that is dictated by the spec
	void move();

	//called when the monster has been eaten
	void eaten();

	//checks to see if the monster has hit Nachman
	bool hitNachmanCheck();

	//called every 'tick' to check if the monster has run into Nachman
	void decrementVulnerability();

	virtual colors GetDisplayColor() const;
	virtual void DoSomething();
private:
	MonsterState m_state;
	int m_vulnerableTicks;
	int destX;
	int destY;
};

////////////////////
//Derived Monsters//
////////////////////
class Inky:public Monster{
public:
	Inky(World* w, int x, int y);

	virtual void whileNormal();
	//Inky uses the default whileVulnerable function
private:
	int m_decideNum;
	int m_decideTicks;
};

class Stinky:public Monster{
public:
	Stinky(World* w, int x, int y);

	virtual void whileNormal();
	//Stinky uses the default whileVulnerable function
private:
};

class Dinky:public Monster{
public:
	Dinky(World* w, int x, int y);

	virtual void whileNormal();
	//Dinky uses the default whileVulnerable function
private:
};

class Clyde:public Monster{
public:
	Clyde(World* w, int x, int y);

	//Clyde uses the default whileNormal function
	virtual void whileVulnerable();
private:
};

#endif // #ifndef _ACTOR_H_

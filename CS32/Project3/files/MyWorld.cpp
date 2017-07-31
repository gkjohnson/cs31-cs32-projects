#include "MyWorld.h"

GameStatus MyWorld::RunLevel()
{

// On entry to this function, the NachMan, Monster and
// Maze objects have already been created. To get a pointer
// to them, you can use the World class’s GetNachMan(),
// GetMonster(), and GetMaze() methods.
// YOU MUST WRITE CODE TO DO EXACTLY THIS:

	NachMan* nachman=GetNachMan();

// NachMan initialization:
// 1. Set NachMan’s state to ALIVE and
	nachman->setAlive();

// 2. Set NachMan’s current location to the
// specified NachMan-start-location in the Maze
	nachman->SetX(GetMaze()->GetNachManStartX());
	nachman->SetY(GetMaze()->GetNachManStartY());

// 3. Reset the NachMan’s direction to none so he
// doesn’t move until the player hits a key
	nachman->setDir(NONE);


// Monster initialization:
	for(int i=0;i<NUM_MONSTERS;i++){
// 1. Set all four monsters’ states to normal
		GetMonster(i)->SetState(NORMAL);

// 2. Set each monster’s start location in the maze
// to the monster home square in the Maze
		GetMonster(i)->SetX(GetMaze()->GetMonsterStartX());
		GetMonster(i)->SetY(GetMaze()->GetMonsterStartY());
	}

// Redisplay every cell on the screen before
// game play begins (true means redraw every grid cell)

	DisplayScreen(true); // use this exact function call

// Define your main game loop
// Each iteration of the loop is one game tick

	while (!(nachman->isDead())  && GetMaze()->GetRemainingFood()!=0 ) //While Nachman is not dead and there-are-uneaten-pellets-in-maze
	{
		// Ask the NachMan object to move itself
		nachman->DoSomething();

// Check if NachMan has died as a result of
// moving itself. 
		if(!(nachman->isDead())){
//If NachMan has not died,
// then ask each of the four monsters to move itself
			for(int i=0;i<NUM_MONSTERS;i++){
				GetMonster(i)->DoSomething();
			}
		}
// Now update the graphical display, only redrawing
// those sqares on the grid that changed due to
// movement (That’s what the false means)

		DisplayScreen(false); // use this exact function call
	}
	if (GetMaze()->GetRemainingFood()==0)//if all of the food was eaten
	{
// you must return finishedlevel if NachMan
// has eaten all of the pellets on this level
// and therefore has completed the level
		return FINISHED_LEVEL;
	}
	
// otherwise, NachMan died; you must return playerdied
// in this case.
	
	return PLAYER_DIED;
}
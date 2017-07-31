#include "MyMaze.h"
#include "Actor.h"
#include "World.h"

#include "GraphManager.h"

#include "UserInterface.h"
#include <iostream>
#include <sstream>
using namespace std;

// pass in true to redraw the entire screen, pass in false to redraw incrementally for faster animations
void World::DisplayScreen(bool reset)
{
	ostringstream oss;
#ifndef PROJ3_PART_ONE
	oss << "Lives: " << m_pcNachMan->GetNumLivesLeft() << ", Level: " << m_nLevel << ", Score: "
		<< m_pcNachMan->GetScore();
#else
	oss << "Level: %d" << m_nLevel;
#endif 
	m_graphManager.setStatusLine(oss.str().c_str());

	m_pcMaze->updateDisplay(reset);
}

bool World::PrepareLevel()
{
	m_pcMaze = new MyMaze(&m_graphManager);

	// now initialize our graphmanager
	m_graphManager.reset();

	// load the maze
	ostringstream oss;
	oss << "maze" << m_nLevel << ".txt";
	if (m_pcMaze->LoadMaze(oss.str().c_str()) == false)
	{
		//delete m_pcMaze;  cleaned up by destructor
		return false;
	}

	m_graphManager.setDelay(40);		// to slow the game down

	// place our player
	m_pcNachMan->SetX(m_pcMaze->GetNachManStartX());
	m_pcNachMan->SetY(m_pcMaze->GetNachManStartY());

#ifndef PROJ3_PART_ONE
	// initialize our monsters
	m_apcMonster[0] = new Inky(this,m_pcMaze->GetMonsterStartX(),m_pcMaze->GetMonsterStartY());
	m_apcMonster[1] = new Stinky(this,m_pcMaze->GetMonsterStartX(),m_pcMaze->GetMonsterStartY());
	m_apcMonster[2] = new Dinky(this,m_pcMaze->GetMonsterStartX(),m_pcMaze->GetMonsterStartY());
	m_apcMonster[3] = new Clyde(this,m_pcMaze->GetMonsterStartX(),m_pcMaze->GetMonsterStartY());

	for(int k = 0; k < 4; k++)
	{
		if (m_apcMonster[k] == NULL)
		{
			// maze/monster memory cleand up by destructor
			return false;
		}
	}
#endif

	// tell the maze about the players in it so the maze can plot properly
	m_pcMaze->SubmitActor(m_pcNachMan);

#ifndef PROJ3_PART_ONE
	for (int i = 0; i < NUM_MONSTERS; i++)
		m_pcMaze->SubmitActor(m_apcMonster[i]);
#endif

	return true;
}


void World::RunGame()
{
	m_graphManager.clearScreen();

	// reset the game; allocate the player 
	ResetGame();

	SoundFX::playNachManSound(PAC_SOUND_START);

	// load the maze and allocate the monsters
	if (PrepareLevel() == false)
	{
		printf("error: unable to load maze file or allocate memory!\n");
		return;
	}

	// Display the maze and prompt the user to start
	DisplayScreen(true);

	m_graphManager.displayMessageAndWait("Press enter to start NachMan.");

	// play until the player loses all of their lives or they win
	bool gameOver = false;
	do
	{
		// allow the user to play the current level until they either get caught by a monster and die
		// or finish the level
		switch (RunLevel())
		{
		  case PLAYER_DIED:
			SoundFX::playNachManSound(PAC_SOUND_DIE);

			// the player died; see if they've lost all of their lives or still have more
#ifndef PROJ3_PART_ONE
			m_pcNachMan->DecrementNumLives();

			if (m_pcNachMan->GetNumLivesLeft() == 0)
			{
				// game over
				m_graphManager.displayMessageAndWait("You have lost all of your lives! Press enter to quit.");
				gameOver = true;		// totally dead
			}
			else
			{
				// you get another try
				m_graphManager.displayMessageAndWait("You died but have more lives! Press enter to continue.");
			}
#endif
			break;
		  case FINISHED_LEVEL:
			// the player finished the current level

			CloseLevel();			// free previous level
			m_nLevel++;				// advance to next level
			if (!PrepareLevel())	// load and prepare the next level if there is one
			{
				// that was the last level
				m_graphManager.displayMessageAndWait("You've won the game! Press enter to quit.");
				gameOver = true;
			}
			else
			{
				// advance to next level
				m_graphManager.displayMessageAndWait("You've completed the level! Press enter to continue.");
			}
			break;
		}
	} while (!gameOver);
}


void World::CloseLevel()
{
	// free the monsters

#ifndef PROJ3_PART_ONE
	for (int i=0;i<NUM_MONSTERS;i++)
	{
		delete m_apcMonster[i];
		m_apcMonster[i] = NULL;
	}
#endif 

	// free the maze
	delete m_pcMaze;
	m_pcMaze = NULL;

	// don't free the player
}


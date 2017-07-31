#ifndef _WORLD_H_
#define _WORLD_H_

#include "testdefines.h"

#include "UserInterface.h"
#include "Actor.h"
#include "MyMaze.h"

//???? const int STATUS_LINE = 21;
//???? const int MESSAGE_LINE = 22;
const int NUM_MONSTERS = 4;

enum GameStatus {
	PLAYER_DIED, FINISHED_LEVEL
};

class World
{
public:
	World()
	{
		m_pcNachMan = NULL;
		m_pcMaze = NULL;
#ifndef PROJ3_PART_ONE
		for (int i=0;i<NUM_MONSTERS;i++)
			m_apcMonster[i] = NULL;
#endif 
		ResetGame();
	}

	virtual ~World()
	{
		delete m_pcNachMan;

#ifndef PROJ3_PART_ONE
		for (int i=0;i<NUM_MONSTERS;i++)
			delete m_apcMonster[i];
#endif 

		delete m_pcMaze;
	}

	void ResetGame()
	{
		m_nLevel = 0;
		if (m_pcNachMan != NULL)
			delete m_pcNachMan;
		m_pcNachMan = new NachMan(this,0,0);
	}

	void RunGame();

	NachMan* GetNachMan()
	{
		return(m_pcNachMan);
	}

#ifndef PROJ3_PART_ONE

	Monster* GetMonster(int nMonster)
	{
		return(m_apcMonster[nMonster]);
	}

#endif

	Maze* GetMaze()
	{
		return(m_pcMaze);
	}

	int GetLevel()
	{
		return(m_nLevel);
	}

	GraphManager* getGraphManager()
	{
		return &m_graphManager;
	}

	virtual GameStatus RunLevel() = 0;

	void DisplayScreen(bool reset);

private:

	bool PrepareLevel();
	void CloseLevel();

private:

	int				m_nLevel;
	NachMan*			m_pcNachMan;
#ifndef PROJ3_PART_ONE
	Monster*			m_apcMonster[NUM_MONSTERS];
#endif
	MyMaze*				m_pcMaze;
	GraphManager	m_graphManager;
};

#endif // #ifndef _WORLD_H_

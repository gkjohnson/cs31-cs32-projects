#ifndef _MAZE_H_

#define _MAZE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Actor.h"
#include "UserInterface.h"

#include "GraphManager.h"

enum GridContents {
	EMPTY, WALL, PELLET, POWERPELLET, CAGEDOOR
};

class Maze
{
public:

	Maze(GraphManager* gm)
	{
		m_nFood = 0;
		m_bFirstDisplay = true;
		m_graphManager = gm;
		m_graphManager->reset();
	}

	virtual ~Maze()
	{
		// n/a
	}

#ifndef PROJ3_PART_ONE
	virtual bool GetNextCoordinate(int nCurX, int nCurY, int &nNextX, int &nNextY) = 0;
#else
	virtual bool GetNextCoordinate(int nCurX, int nCurY, int &nNextX, int &nNextY)
	{
		return false;
	}
#endif

	virtual bool LoadMaze(const std::string &sMazeFile)
	{
		std::ifstream mazeFile(sMazeFile.c_str());
		if (!mazeFile)
			return false;

		for (int i=0;i<MAZE_HEIGHT;i++)
		{
			std::string line;
			if (!std::getline(mazeFile, line))
				return false;
			if (line.size() < MAZE_WIDTH)
				return false;
			for (int j = 0; j < MAZE_WIDTH; j++)
			{
				switch (line[j])
				{
					case '#':
						m_Grid[i][j] = WALL;
						m_graphManager->addItem(ITEM_WALL, j, i, WHITE, EAST);
						break;
					case '%':
						m_Grid[i][j] = CAGEDOOR;
						m_graphManager->addItem(ITEM_CAGEDOOR, j, i, WHITE, EAST);
						break;
					case '.':
						m_Grid[i][j] = PELLET;
						m_graphManager->addItem(ITEM_DOT, j, i, WHITE, EAST);
						m_nFood++;
						break;
					case '*':
						m_Grid[i][j] = POWERPELLET;
						m_graphManager->addItem(ITEM_POWER, j, i, WHITE, EAST);
						m_nFood++;
						break;
					case ' ':
						m_Grid[i][j] = EMPTY;
						break;
					case '$':
						m_nMonsterStartX = j;
						m_nMonsterStartY = i;
						m_Grid[i][j] = EMPTY;
						break;
					case '@':
						m_nNachManStartX = j;
						m_nNachManStartY = i;
						m_Grid[i][j] = EMPTY;
						break;
					default:  // unknown character in maze
						return false;
				}
			}
		}

		return m_nNachManStartX != -1 && m_nMonsterStartX != -1;
	}

	GridContents GetGridContents(int x, int y) const
	{
		return(m_Grid[y][x]);
	}

	void SetGridContents(int x, int y, GridContents nGC)
	{
		// update our display
		if (m_Grid[y][x] == PELLET && nGC == EMPTY)
			m_graphManager->removeItem(ITEM_DOT,x,y);
		else if (m_Grid[y][x] == POWERPELLET && nGC == EMPTY)
			m_graphManager->removeItem(ITEM_POWER,x,y);

		if ((m_Grid[y][x] == POWERPELLET || m_Grid[y][x] == PELLET) &&
			nGC != POWERPELLET && nGC != PELLET) 
			m_nFood--;

		m_Grid[y][x] = nGC;
	}

	int GetRemainingFood() const
	{
		return(m_nFood);
	}

	int GetMonsterStartX() const
	{
		return(m_nMonsterStartX);
	}

	int GetMonsterStartY() const
	{
		return(m_nMonsterStartY);
	}

	int GetNachManStartX() const
	{
		return(m_nNachManStartX);
	}

	int GetNachManStartY() const
	{
		return(m_nNachManStartY);
	}

	struct COORD
	{
		COORD(int xx, int yy)
		{
			x = xx; y = yy;
		}

		int x, y;
	};



	void SubmitActor(Actor* a)
	{
		m_vActors.push_back(a);
		m_lastActorCoords.push_back(COORD(a->GetX(),a->GetY()));
		m_graphManager->addItem(a->getMyID(),a->GetX(),a->GetY(),a->GetDisplayColor(),EAST);
	}

	void updateDisplay(bool reset)
	{
		if (!reset)
		{
			for (size_t i=0;i<m_vActors.size();i++)
			{
				

				Direction d = getDirectionFromDelta(m_vActors[i]->GetX()-m_lastActorCoords[i].x,
													m_vActors[i]->GetY()-m_lastActorCoords[i].y);

				m_graphManager->updateActorColor(m_vActors[i]->getMyID(),m_vActors[i]->GetDisplayColor());

				// the guy didn't move since last diplayed, so don't update our screen
				if (m_lastActorCoords[i].x == m_vActors[i]->GetX() && m_lastActorCoords[i].y == m_vActors[i]->GetY())
					d = NONE;
				m_lastActorCoords[i].x = m_vActors[i]->GetX();
				m_lastActorCoords[i].y = m_vActors[i]->GetY();

				if (d != NONE)
				{
					m_graphManager->moveActor(m_vActors[i]->getMyID(),d);
				}
				else
				{
					m_graphManager->updateActorLocation(m_vActors[i]->getMyID(),m_vActors[i]->GetX(),m_vActors[i]->GetY());
				}
			}
		}
		else
		{
			for (size_t i=0;i<m_vActors.size();i++)
			{
				m_graphManager->updateActorColor(m_vActors[i]->getMyID(),m_vActors[i]->GetDisplayColor());
				m_graphManager->updateActorLocation(m_vActors[i]->getMyID(),m_vActors[i]->GetX(),m_vActors[i]->GetY());
				m_lastActorCoords[i] = COORD(-1,-1);
			}
		}

		m_graphManager->animate();
	}

private:

	Direction getDirectionFromDelta(int dx, int dy)
	{
		if (dx == -1)
			return WEST;
		if (dx == 1)
			return EAST;
		if (dy == -1)
			return NORTH;
		if (dy == 1)
			return SOUTH;

		return NONE;
	}


private:

	GridContents		m_Grid[MAZE_HEIGHT][MAZE_WIDTH];
	int					m_nFood;
	int					m_nMonsterStartX;
	int					m_nMonsterStartY;
	int					m_nNachManStartX;
	int					m_nNachManStartY;
	bool				m_bFirstDisplay;
	std::vector<Actor*>m_vActors;
	GraphManager*		m_graphManager;
	std::vector<COORD>	m_lastActorCoords;
};


#endif // #ifndef _MAZE_H_

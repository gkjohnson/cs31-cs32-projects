#ifndef _GMAN_H_
#define _GMAN_H_

#include <string>
#include <vector>
#include <list>
#include <set>

#include "BGIgraphics.h"
#include "GraphObj.h"
#include "constants.h"
#include "UserInterface.h"
#include <windows.h>

const int MAZE_WIDTH = 21;
const int MAZE_HEIGHT = 15;

const int NUM_ACTORS = 9;
const int INVALID_LOCATION = -1;

const int DRAWABLE_PACMAN1 = 8;
const int DRAWABLE_PACMAN2 = 9;

const int NUM_ITEM_TYPES = 15;

const int STATUS_X = 20;
const int STATUS_Y = 460;
const int STATUS_WIDTH = 640;
const int STATUS_HEIGHT = 20;
const int STATUS_FONT_SIZE = 12;

const int MESSAGE_BOX_Y = 200;
const int MESSAGE_FONT_SIZE = 15;
const int MAXIMUM_MESSAGE_WIDTH_IN_PIXELS = (SCREEN_WIDTH - 20);
const int HORIZ_SLACK_PIXELS = 10;
const int VERT_SLACK_PIXELS = 4;

enum Direction {
	NORTH, SOUTH, EAST, WEST, NONE
};


const int START_X = (CELL_SIZE/2);
const int START_Y = (CELL_SIZE/2);
const int PIXEL_MULTIPLIER = 6;		// each square in the grid is this big

const int GRID_SIZE = (SCREEN_WIDTH/PIXEL_MULTIPLIER);

const int GRID_MULTIPLIER = 5;

const int NUM_PHASES = 5;

const int OPCODE_REMOVE = 0;
const int OPCODE_MOVE = 1;
const int OPCODE_COLOR = 2;
const int OPCODE_DRAW = 3;

//const int OPCODE_DIRECTION = 6;


struct GMCOORD
{
	GMCOORD(int _x = 0, int _y = 0)
	{
		x = _x;
		y = _y;
	}

	int x,y;
};

inline bool operator<(const GMCOORD &a, const GMCOORD &b)
{
	if (a.x < b.x)
		return true;
	if (a.x > b.x)
		return false;
	return a.y < b.y;
}


struct INSTRUCTION
{
	int opcode;
	int itemID;
	int x, y;
	colors color;
	int state;
	int dx,dy;
	Direction direction;
};

class GraphManager
{
public:
	GraphManager()
	 : m_screen(SCREEN_WIDTH, SCREEN_HEIGHT) 
	{
		m_curPage = 0;

		// get a blank image for erasing stuff
		int imageSize = imagesize(0,0,CELL_SIZE-1,CELL_SIZE-1);
		m_blankImage = new char[imageSize];
		getimage(0,0,CELL_SIZE-1,CELL_SIZE-1,m_blankImage);
		m_delayInMS = 0;

		reset();
	}

	~GraphManager()
	{
		delete [] m_blankImage;

		for (int i=0;i<GRID_SIZE;i++)
			for (int j=0;j<GRID_SIZE;j++)
			{
				std::list<GraphObject*>::iterator it;

				for (it=m_grid[i][j].begin(); it != m_grid[i][j].end();it++)
				{
					//if ((*it)->getItemID() >= ITEM_MONSTER1 && (*it)->getItemID() <= ITEM_NACHMAN)
					//	printf("id=%d, xy=%d,%d, grid=%d,%d\n",(*it)->getItemID(),(*it)->getX(),(*it)->getY(),j,i);
					delete *it;
				}
				m_grid[i][j].clear();
			}
	}

	void setStatusLine(const std::string &status)
	{
		m_status = status;
	}

	void displayMessageAndWait(const std::string &msg)
	{
		int visualPage = getActivePage();
		setactivepage(visualPage);
		int tw, th, startFontSize = MESSAGE_FONT_SIZE;

		do
		{
			settextstyle(DEFAULT_FONT, HORIZ_DIR, startFontSize);	
			tw = textwidth((char *)msg.c_str()) + 2*HORIZ_SLACK_PIXELS;
			th = textheight((char *)msg.c_str()) + 2*VERT_SLACK_PIXELS;
			startFontSize--;
		} while (tw > MAXIMUM_MESSAGE_WIDTH_IN_PIXELS && startFontSize > 1);

		int startX = (SCREEN_WIDTH - tw)/2;
		int boxX = startX - HORIZ_SLACK_PIXELS;
		if (boxX < 0)
			boxX = 0;

		clearArea(getActivePage(),boxX, MESSAGE_BOX_Y, SCREEN_WIDTH - 2*boxX - 1, th);
		setcolor(LIGHTRED);
		rectangle(boxX, MESSAGE_BOX_Y, SCREEN_WIDTH - boxX - 1, MESSAGE_BOX_Y + th);
		setcolor(LIGHTRED);
		outtextxy(startX + HORIZ_SLACK_PIXELS,MESSAGE_BOX_Y + VERT_SLACK_PIXELS,(char*)msg.c_str());

		waitForEnter();
		doFullScreenRedraw();
#if 0
		while (1)
		{
			char ch;
			if (getCharIfAny(ch) && ch == '\r')
			{
				doFullScreenRedraw();
				return;
			}
		}
#endif
	}

	void doFullScreenRedraw()
	{
		for (int i=0;i<MAZE_HEIGHT;i++)
			for (int j=0;j<MAZE_WIDTH;j++)
			{
				// request a redraw
				INSTRUCTION in;
				in.x = j*GRID_MULTIPLIER;
				in.y = i*GRID_MULTIPLIER;
				in.opcode = OPCODE_DRAW;

				m_instructions[0].push_back(in);
			}
	}

	void setDelay(int ms)
	{
		m_delayInMS = ms;
	}

	void clearScreen()
	{
		setcolor(BLACK);
		for (int j=0;j<SCREEN_HEIGHT;j++)
			line(0,j,SCREEN_WIDTH-1,j);
	}

	void reset()
	{
		for (int i=0;i<GRID_SIZE;i++)
			for (int j=0;j<GRID_SIZE;j++)
			{
				for (std::list<GraphObject*>::iterator it=m_grid[i][j].begin(); it != m_grid[i][j].end();it++)
					delete *it;
				m_grid[i][j].clear();
			}
		m_redrawCoords.clear();
		for (int i=0;i<NUM_PHASES;i++)
			m_instructions[i].clear();

		for (int i=0;i<NUM_ACTORS;i++)
			m_actors[i] = NULL;		// all actors deleted because of above
	}

	void addItem(int itemID, int x, int y, colors color, Direction direction)
	{
		// inser the item into the grid
		GraphObject* item = allocAndInsertItem(itemID,x*GRID_MULTIPLIER,y*GRID_MULTIPLIER,color,angleFromDirection(direction));
		if (item == NULL)
			return;

		// request a redraw
		INSTRUCTION i;
		i.x = x*GRID_MULTIPLIER;
		i.y = y*GRID_MULTIPLIER;
		i.opcode = OPCODE_DRAW;

		m_instructions[0].push_back(i);
	}

	void removeItem(int itemID, int x, int y)
	{
		INSTRUCTION i;
		i.x = x*GRID_MULTIPLIER;
		i.y = y*GRID_MULTIPLIER;
		i.itemID = itemID;
		i.opcode = OPCODE_REMOVE;

		m_instructions[0].push_back(i);
	}

	void removeActor(int itemID)
	{
		if (m_actors[itemID] == NULL)
			return;

		INSTRUCTION i;
		i.x = m_actors[itemID]->getX();
		i.y = m_actors[itemID]->getY();
		i.itemID = itemID;
		i.opcode = OPCODE_REMOVE;

		m_instructions[0].push_back(i);
	}

	void moveActor(int itemID, Direction direction)
	{
		if (m_actors[itemID] == NULL)
			return;

		INSTRUCTION in;
		int dx, dy;
		int startX, startY;

		getDxDyFromDirection(direction,dx,dy);

		// get their current location
		int fromX = m_actors[itemID]->getX();
		int fromY = m_actors[itemID]->getY();

		startX = fromX;
		startY = fromY;

		for (int i=0;i<GRID_MULTIPLIER;i++)
		{
			in.itemID = itemID;
			in.x = fromX;
			in.y = fromY;
			in.dx = dx;
			in.dy = dy;
			in.state = 0;
			in.direction = direction;
			in.opcode = OPCODE_MOVE;
			m_instructions[i].push_back(in);

			// make sure we have a request to redraw in our original square and in our new square
			// in EACH of our four iterations so we don't inadvertently clear an item in our previous
			// square 
			in.x = startX;
			in.y = startY;
			in.opcode = OPCODE_DRAW;
			m_instructions[i].push_back(in);

			in.x = startX + dx;
			in.y = startY + dy;
			in.opcode = OPCODE_DRAW;
			m_instructions[i].push_back(in);

			fromX += dx;
			fromY += dy;
		}
	}

	void updateActorColor(int itemID, colors toColor)
	{
		if (m_actors[itemID] != NULL)
		{
			INSTRUCTION in;

			in.itemID = itemID;
			in.color = toColor;
			in.opcode = OPCODE_COLOR;
			m_instructions[0].push_back(in);
		}
	}

	void updateActorLocation(int itemID, int toX, int toY)
	{
		GraphObject* go = m_actors[itemID];
		if (go == NULL)
			return;

		std::list<GraphObject*> &ref = m_grid[go->getY()][go->getX()];

		for (std::list<GraphObject*>::iterator it=ref.begin(); it != ref.end();it++)
		{
			if (*it == go)
			{	
				// remove the entry
				ref.erase(it);
				break;
			}
		}

		int oldX = go->getX();
		int oldY = go->getY();

		int newX = toX*GRID_MULTIPLIER;
		int newY = toY*GRID_MULTIPLIER;

		go->setX(newX);
		go->setY(newY);

		m_grid[newY][newX].push_back(go);

		// request drawing
		INSTRUCTION in;

		in.x = oldX;
		in.y = oldY;
		in.opcode = OPCODE_DRAW;
		m_instructions[0].push_back(in);

		in.x = newX;
		in.y = newY;
		in.opcode = OPCODE_DRAW;
		m_instructions[0].push_back(in);
	}


	void animate()
	{
		for (int i=0;i<GRID_MULTIPLIER;i++)
		{
			if (m_instructions[i].size() > 0)
			{
				outputTextLines();

				// draw to our hidden page and then make it visual
				executePlan(m_instructions[i]);

				switchPages();

				// now make the same changes to our old visual page so we're in sync
				// ok clear all regions that need to be cleared
				executeClearPlan();

				// ok, draw all items that need to be drawn
				executeDrawPlan();
				
				// now clean up for the next round
				m_instructions[i].clear();
				m_redrawCoords.clear();

				// sleep requested amount of time
				Sleep(m_delayInMS);
			}
		}
	}

private:

	void outputTextLines()
	{
		int nonVisualPage = getOtherPage();
		setactivepage(nonVisualPage);

		clearArea(getOtherPage(),STATUS_X, STATUS_Y, STATUS_WIDTH, STATUS_HEIGHT);
		setcolor(WHITE);
		settextstyle(DEFAULT_FONT, HORIZ_DIR, STATUS_FONT_SIZE);
		outtextxy(STATUS_X,STATUS_Y,(char*)m_status.c_str());
	}

	GraphObject* allocAndInsertItem(int itemID, int x, int y,colors color,int angle)
	{
		GraphObject* go = new GraphObject(itemID,x,y,color,angle);
		if (go == NULL)
			return NULL;

		switch (itemID)
		{
			case ITEM_DOT:
				{
					COORDINATE coordsDOT[] = { {3,0}, {0,-3},{-3,0},{0,3},{3,0} };
					go->setPolygon(0,coordsDOT,sizeof(coordsDOT)/sizeof(COORDINATE));
				}
				break;
			case ITEM_POWER:
				{
					COORDINATE coordsPOWER[] = { {8,0}, {0,-8},{-8,0},{0,8},{8,0} };
					go->setPolygon(0,coordsPOWER,sizeof(coordsPOWER)/sizeof(COORDINATE));
				}
				break;
			case ITEM_WALL:
				{
					COORDINATE coordsWALL[] = { {-15,-15}, {14,14},{-15,14},{-15,-15},{14,-15},{14,14},{14,-15},{-15,14} };
					go->setPolygon(0,coordsWALL,sizeof(coordsWALL)/sizeof(COORDINATE));
				}
				break;
			case ITEM_CAGEDOOR:
				{
					COORDINATE coordsDoor[] = { {-10,-10}, {9,-10},{9,9},{-10,9},{-10,-10} };
					go->setPolygon(0,coordsDoor,sizeof(coordsDoor)/sizeof(COORDINATE));
				}
				break;

			case ITEM_MONSTER1:
			case ITEM_MONSTER2:
			case ITEM_MONSTER3:
			case ITEM_MONSTER4:
				{
					COORDINATE coordsMONSTER[] = { {-9,9}, {-9,0}, {-5,-10}, {5,-10}, {9,0}, {9,9}, {5,5}, {0,9}, {-5,5}, {-9,9}};
					go->setPolygon(0,coordsMONSTER,sizeof(coordsMONSTER)/sizeof(COORDINATE));
					go->setAngle(0);		// never adjust angle for monsters
					m_actors[itemID] = go;
				}
				break;

			case ITEM_NACHMAN:
				{
					COORDINATE coordsPACMAN1[] = { {-6,11}, {-11,6},{-11,-6},{-6,-11},{6,-11},{11,-8},{0,0},{11,8},{6,11},{-6,11}};
					go->setPolygon(0,coordsPACMAN1,sizeof(coordsPACMAN1)/sizeof(COORDINATE));

					COORDINATE coordsPACMAN2[] = { {-6,11}, {-11,6},{-11,-6},{-6,-11},{6,-11},{11,-3},{0,0},{11,3},{6,11},{-6,11}};
					go->setPolygon(1,coordsPACMAN2,sizeof(coordsPACMAN2)/sizeof(COORDINATE));
					m_actors[itemID] = go;
				}
				break;
		}

		m_grid[y][x].push_back(go);

		return go;
	}


	void draw(GraphObject* go)
	{
		int nonVisualPage = getOtherPage();
		setactivepage(nonVisualPage);

		int gridX = go->getX();
		int gridY = go->getY();

		int jitterX = 0, jitterY = 0;
		if (go->getItemID() >= ITEM_MONSTER1 && go->getItemID() <= ITEM_MONSTER4)
		{
			jitterX = rand() % 3 - 1;
			jitterY = rand() % 3 - 1;
		}

		go->setX(gridX * PIXEL_MULTIPLIER + START_X + jitterX);
		go->setY(gridY * PIXEL_MULTIPLIER + START_Y + jitterY);

		go->draw();

		go->setX(gridX);
		go->setY(gridY);
	}

	void clearArea(int pageNum, int x, int y, int width, int height)
	{
		setactivepage(pageNum);

		if (width != CELL_SIZE || height != CELL_SIZE || m_blankImage == NULL)
		{
			setcolor(BLACK);
			for (int i=0;i<height;i++)
				line(x,y+i,x+width,y+i);
		}
		else
			putimage(x,y,m_blankImage,COPY_PUT);
	}

	void switchPages()
	{
		int nonVisualPage = getOtherPage();
		setvisualpage(nonVisualPage);
		switchVisualPage();
	}

	int getOtherPage() const
	{
		return (m_curPage+1) % 2;
	}

	int getActivePage() const
	{
		return m_curPage;
	}
	

	void switchVisualPage()
	{
		m_curPage = (m_curPage+1) % 2;
	}


	void executePlan(std::vector<INSTRUCTION> &plan)
	{
		for (size_t i=0;i<plan.size();i++)
		{
			switch (plan[i].opcode)
			{
				case OPCODE_REMOVE:
					removeFromGrid(plan[i]);
					break;
				case OPCODE_MOVE:
					moveItem(plan[i]);
					break;
				case OPCODE_COLOR:
					changeColor(plan[i]);
					break;
				case OPCODE_DRAW:
					drawSquare(plan[i]);
					break;
			}
		}
		
		// ok clear all regions that need to be cleared
		executeClearPlan();

		// ok, draw all items that need to be drawn
		executeDrawPlan();
	}

	void executeClearPlan()
	{
		std::set<GMCOORD>::iterator it;

		for (it = m_redrawCoords.begin();it != m_redrawCoords.end();it++)
		{
			int x = it->x * PIXEL_MULTIPLIER;
			int y = it->y * PIXEL_MULTIPLIER;

			clearArea(getOtherPage(),x,y, CELL_SIZE,CELL_SIZE);
		}

	}

	void executeDrawPlan()
	{
		std::set<GMCOORD>::iterator it;

		for (it=m_redrawCoords.begin();it!=m_redrawCoords.end();it++)
		{
			std::list<GraphObject*> &items = m_grid[it->y][it->x];
			std::list<GraphObject*>::iterator it2;

			for (it2 = items.begin();it2 != items.end();it2++)
			{
				draw(*it2);
			}
		}
	}

	void drawSquare(const INSTRUCTION &in)
	{
		m_redrawCoords.insert(GMCOORD(in.x,in.y));
	}

	void clearRegion(const INSTRUCTION &in)
	{
		GMCOORD r;
		r.x = in.x;
		r.y = in.y;

		m_redrawCoords.insert(r);
	}

	void changeColor(const INSTRUCTION &in)
	{
		if (m_actors[in.itemID] == NULL)
			return;

		m_actors[in.itemID]->setColor(in.color);
		m_redrawCoords.insert(GMCOORD(m_actors[in.itemID]->getX(),
									m_actors[in.itemID]->getY()));
	}


	void moveItem(const INSTRUCTION &in)
	{
		std::list<GraphObject*> &items = m_grid[in.y][in.x];
		std::list<GraphObject*>::iterator it;
	
		for (it = items.begin(); it != items.end(); it++)
		{
			GraphObject* go = *it;
			if (go->getItemID() == in.itemID)
			{
				// erase the old entry
				items.erase(it);

				// request a redraw of where this guy was
				m_redrawCoords.insert(GMCOORD(in.x,in.y));

				// move the guy next door
				int newX = in.x + in.dx;
				int newY = in.y + in.dy;

				go->setX(newX);
				go->setY(newY);
				
				// update it's state if necessary
				if (in.itemID == ITEM_NACHMAN)
				{
					go->setState(!go->getState());
					go->setAngle(angleFromDirection(in.direction));
				}

				// put it back in
				m_grid[newY][newX].push_back(go);

				// request a redraw of the new cell
				m_redrawCoords.insert(GMCOORD(newX,newY));
				break;
			}
		}
	}

	void removeFromGrid(const INSTRUCTION &in)
	{
		std::list<GraphObject*> &items = m_grid[in.y][in.x];
		std::list<GraphObject*>::iterator it;

		for (it = items.begin(); it != items.end(); it++)
		{
			if ((*it)->getItemID() == in.itemID)
			{
				delete *it;		// free the object
				items.erase(it);

				// redraw anything else in this cell
				m_redrawCoords.insert(GMCOORD(in.x,in.y));
				return;
			}
		}
	}

	void getDxDyFromDirection(int dir, int &dx, int &dy)
	{
		switch (dir)
		{
			case NORTH:
				dx = 0;
				dy = -1;
				return;
			case SOUTH:
				dx = 0;
				dy = 1;
				return;
			case WEST:
				dx = -1;
				dy = 0;
				return;
			case EAST:
				dx = 1;
				dy = 0;
				return;
		}

		printf("\a\a");
	}

	int directionFromAngle(int angle)
	{
		switch (angle)
		{
			case 0:
				return EAST;
			case 90:
				return NORTH;
			case 180:
				return WEST;
			case 270:
				return SOUTH;
		}

		printf("\a\a");

		return 0;
	}

	int angleFromDirection(int direction)
	{
		switch (direction)
		{
			case EAST:
				return 0;
			case NORTH:
				return 90;
			case WEST:
				return 180;
			case SOUTH:
				return 270;
		}

		printf("\a\a");

		return 0;
	}

private:
	Screen						m_screen;
	GraphObject* 				m_actors[NUM_ITEM_TYPES];
	std::list<GraphObject*>		m_grid[GRID_SIZE][GRID_SIZE];
	std::set<GMCOORD>			m_redrawCoords;
	std::vector<INSTRUCTION>	m_instructions[NUM_PHASES];
	int							m_delayInMS;
	int							m_curPage;
	char*						m_blankImage;
	std::string					m_status;
};

#endif // #ifndef _GMAN_H_

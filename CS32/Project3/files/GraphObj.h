#ifndef _GRAPHOBJ_H_
#define _GRAPHOBJ_H_

#include "BGIgraphics.h"
#include "constants.h"
#include <cmath>
#include <vector>

const int CELL_SIZE = 30;  // pixels

const int NUM_ANGLES = 4;
const int ANGLE_0_DEGREES_INDEX   = 0;
const int ANGLE_90_DEGREES_INDEX  = 1;
const int ANGLE_180_DEGREES_INDEX = 2;
const int ANGLE_270_DEGREES_INDEX = 3;

const int MAX_STATES = 10;

struct COORDINATE
{
	int x, y;
};

class GraphObject
{
public:

	GraphObject()
	{
		m_x = 0;
		m_y = 0;
		m_color = WHITE;
		m_angle = 0;
		m_state = 0;
	}

	GraphObject(int itemID, int x, int y, colors color, int angle)
	{
		m_itemID = itemID;
		m_x = x;
		m_y = y;
		m_state = 0;
		m_color = color;
		setAngle(angle);
	}

	virtual ~GraphObject()
	{
	}

	void setPolygon(int state, const COORDINATE coords[], int numCoords)
	{
		if (state >= MAX_STATES)
			return;

		for (int angles=0;angles<NUM_ANGLES;angles++)
		{
			for (int i=0;i<numCoords;i++)
			{
				if (angles > 0)
				{
					// now adjust this coord for the next rotation (90, 180, 270)
					COORDINATE c;

					c.x = m_curCoords[state][angles-1][i].y;
					c.y = m_curCoords[state][angles-1][i].x * -1;

					m_curCoords[state][angles].push_back(c);
				}
				else
					m_curCoords[state][angles].push_back(coords[i]);
			}
		}
	}


	virtual void draw() const
	{
		setcolor(m_color);

		const std::vector<COORDINATE> &curCoords = m_curCoords[m_state][m_angle];

		if (curCoords.size() > 1)
		{
			size_t i;
			for (i=0;i<curCoords.size()- 1;i++)
				line((int)(curCoords[i].x + m_x),
					 (int)(curCoords[i].y + m_y),
					 (int)(curCoords[i+1].x + m_x),
					 (int)(curCoords[i+1].y + m_y)
				 );
		}
	}

	virtual void setX(int x)
	{
		m_x = x;
		while (m_x < 0)
			m_x += SCREEN_WIDTH;
		while (m_x > SCREEN_WIDTH)
			m_x -= SCREEN_WIDTH;
	}

	virtual void setY(int y)
	{
		m_y = y;
		while (m_y < 0)
			m_y += SCREEN_HEIGHT;
		while (m_y > SCREEN_HEIGHT)
			m_y -= SCREEN_HEIGHT;
	}

	void setColor(colors color)
	{
		m_color = color;
	}

	colors getColor() const
	{
		return m_color;
	}

	void setState(int newState) 
	{
		m_state = newState;
	}

	int getState() const
	{
		return m_state;
	}

	virtual void setAngle(int angle)
	{
		switch (angle)
		{
			case 0:
				m_angle = ANGLE_0_DEGREES_INDEX;
				break;
			case 90:
				m_angle = ANGLE_90_DEGREES_INDEX;
				break;
			case 180:
				m_angle = ANGLE_180_DEGREES_INDEX;
				break;
			case 270:
				m_angle = ANGLE_270_DEGREES_INDEX;
				break;
		}
	}

	virtual int getX() const
	{
		return m_x;
	}

	virtual int getY() const
	{
		return m_y;
	}

	int getItemID() const
	{ 
		return m_itemID;
	}

private:
	std::vector<COORDINATE>		m_curCoords[MAX_STATES][NUM_ANGLES];
	colors						m_color;
	int							m_x, m_y;
	int							m_angle;
	int							m_state;
	int							m_itemID;
};


#endif // #ifndef _GRAPHOBJ_H_

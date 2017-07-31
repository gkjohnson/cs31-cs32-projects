#include "UserInterface.h"

#if 0 // ????
#include "GraphObject.h"
#include "globals.h"
#endif

#include <windows.h>
#include "BGIgraphics.h"

#if 0 // ????
#include <tchar.h>
#endif 

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


///////////////////////////////////////////////////////////
// Screen -- Visual Output
///////////////////////////////////////////////////////////

const int STATUS_X = 10;
const int STATUS_Y = 460;

  // Correct the bad interfaces in BGIgraphics.h
inline int textwidth(const char* s) { return textwidth(const_cast<char*>(s)); }
inline int textheight(const char* s) { return textheight(const_cast<char*>(s)); }
inline void outtextxy(int x, int y, const char* s) { outtextxy(x, y, const_cast<char*>(s)); }

Screen::Screen(int width, int height)
 : m_width(width), m_height(height) 
{
		// request autodetection, initialize graphics
	int gdriver = VGA;  // Detect
	int gmode = VGAHI;
	initgraph(&gdriver, &gmode, "");
	int errorcode = graphresult();
	if (errorcode != grOk)  // error
	{
		cout << "Error initializing graphics: " << grapherrormsg(errorcode) << endl;
		abort();
	}
}

Screen::~Screen()
{
	closegraph();
}

void Screen::updateStatus(string status)
{
	m_status = status;
}

#if 0
void Screen::draw(const GraphObject* const go[], int size)
{
	static int displayedPage = 0;
	const int nonDisplayedPage = 1 - displayedPage;

	setactivepage(nonDisplayedPage);
	clearviewport();

	for (int i = 0; i < size; i++)
		go[i]->draw(*this);

	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	outtextxy(STATUS_X, STATUS_Y, m_status.c_str());

	displayedPage = nonDisplayedPage;
	setvisualpage(displayedPage);
}

void Screen::drawPolygon(const std::vector<Coord>& vertices, Color color)
{
	  // Map our colors to BGIgraphics colors
	static const int colorMap[COLOR_MAXCOLORS] = {
		WHITE, CYAN, YELLOW, LIGHTBLUE,	LIGHTGREEN, LIGHTRED, LIGHTMAGENTA
	};
	setcolor(colorMap[color]);
	if (vertices.size() > 1)
	{
		size_t i;
		for (i = 0; i < vertices.size()-1; i++)
			line(vertices[i].x,   (m_height - 1) - vertices[i].y,
				 vertices[i+1].x, (m_height - 1) - vertices[i+1].y);
		line(vertices[i].x, m_height - vertices[i].y - 1,
			 vertices[0].x, m_height - vertices[0].y - 1);
	}
}

void Screen::displayBanner(string text, unsigned int secsToWait)
{
	const char* txt = text.c_str();

	  //  Determine largest size that fits screen width
	
	int width;
	int height;
	int mult = 40;
	do
	{
		settextstyle(TRIPLEX_FONT, HORIZ_DIR, mult);
		height = textheight(txt);
		width = textwidth(txt);
		mult--;
	} while (width >= m_width);
	outtextxy((m_width-width)/2, (m_height-height)/2, txt);
	Sleep(secsToWait*1000);
}
#endif

///////////////////////////////////////////////////////////
// SoundFX -- Audio Output
///////////////////////////////////////////////////////////

const int SMALL_EAT_DELAY = 250; // msec
const int BIG_EAT_DELAY   = 520; // msec

void SoundFX::playNachManSound(int sound)
{
	static DWORD endSuppressSmallEatSoundTime = 0;
	DWORD now = GetTickCount();

	switch (sound)
	{
	  case PAC_SOUND_SMALL_EAT:
		if (now >= endSuppressSmallEatSoundTime)
		{
			playClip("paceatsmall.wav");
			endSuppressSmallEatSoundTime = now  + SMALL_EAT_DELAY;
		}
		break;
	  case PAC_SOUND_BIG_EAT:
		playClip("paceatbig.wav");
		endSuppressSmallEatSoundTime = now  + BIG_EAT_DELAY;
		break;
	  case PAC_SOUND_START:
		playClip("pacstart.wav");
		break;
	  case PAC_SOUND_DIE:
		playClip("pacdie.wav");
		break;
	}
}

void SoundFX::playClip(std::string ClipFile)
{
	PlaySound(ClipFile.c_str(), NULL, SND_ASYNC);
}

void SoundFX::playTone(int hertz, int milliseconds)
{
	Beep(hertz, milliseconds);
}

///////////////////////////////////////////////////////////
// Functions for Keyboard Input
///////////////////////////////////////////////////////////

// If the user has hit a key, set ch to that character and return true;
//   otherwise, leave ch unchanged and return false.
bool getCharIfAny(char& ch)
{
    if (kbhit())
    {
		int c = getch();
		if (c == 0xE0  ||  c == 0x00)  // first of the two sent by arrow keys
        {
            c = getch();
            switch (c)
            {
              case 'K':  ch = ARROW_LEFT;  break;
              case 'M':  ch = ARROW_RIGHT; break;
              case 'H':  ch = ARROW_UP;    break;
              case 'P':  ch = ARROW_DOWN;  break;
              default:   ch = '?';         break;
            }
        }
        else
		{
			switch (c)
			{
			  case 'a':  ch = ARROW_LEFT;  break;
			  case 'd':  ch = ARROW_RIGHT; break;
			  case 'w':  ch = ARROW_UP;    break;
			  case 's':  ch = ARROW_DOWN;  break;
			  default:   ch = c;           break;
			}
		}
        return true;
    }
    return false;
}

void discardPendingKeys()
{
	char ch;
	while (getCharIfAny(ch))
		;
}

void waitForEnter()
{
	char ch;
	while (ch = getch(), ch != '\n' && ch != '\r')
		;
}

///////////////////////////////////////////////////////////
// Functions for Timing
///////////////////////////////////////////////////////////

// delay - sleep for 20 milliseconds (env. variable NACHDELAY overrides)

void delay()
{
    static unsigned long amt = 0;
	if (amt == 0)
    {
#pragma warning(push)
#pragma warning(disable : 4996)
        const char* p = std::getenv("NACHDELAY");
#pragma warning(pop)
        if (p == NULL  ||  (amt = std::strtoul(p, NULL, 0)) == 0)
            amt = 20;
    }
    Sleep(amt);
}

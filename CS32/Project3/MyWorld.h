#ifndef _MYWORLD_H_
#define _MYWORLD_H_

#include "World.h"

class MyWorld : public World
{
  public:
	virtual GameStatus RunLevel(); //Gameloop function
  private:
	  // You may add whatever private members you wish
};

#endif // #ifndef _MYWORLD_H_

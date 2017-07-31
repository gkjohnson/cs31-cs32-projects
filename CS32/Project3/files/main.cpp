#include "MyWorld.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	MyWorld w;
	w.RunGame();
}

#include "classes.h"

int main()
{
	Board board(1500, 1000);
	while (board.alive())
	{
		board.draw();
	}
	return 0;
}

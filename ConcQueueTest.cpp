#include "ConcQueue.h"

int main()
{
	ConcQueue<int> intqueue;

	intqueue.AddElement(5);
	intqueue.AddElement(6);
	intqueue.AddElement(7);

	intqueue.PrintQueue();
}



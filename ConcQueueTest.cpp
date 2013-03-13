#include "ConcQueue.h"

int main()
{
	ConcQueue<int> intqueue;
	const QueueElement<int>* p1 = intqueue.AddElement(5);
	cout<<"Value is"<<(p1->GetData())<<endl;
	cout<<(intqueue.AddElement(6)->GetData())<<endl;
	intqueue.AddElement(7);

	intqueue.PrintQueue();
}



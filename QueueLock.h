#include "ConcQueue.h"

class QueueLock
{
	ConcQueue<int> lock_queue;
	int lock_taken;
public:
	QueueLock():lock_taken(0)
	{
	}

	int GetLock()
	{

		if(lock_taken != 0)
		{
			const QueueElement<int> *p_add = lock_queue.AddElement(0);
			const int *p_spin = p_add->GetPointerToData();

			while(*(p_spin) != 1)
			{
				//Spinning waiting for lock
			}

		}

		lock_taken = 1;

		return 1;
	}

	void ReleaseLock()
	{
		QueueElement<int> *p_release = lock_queue.GetElement();

		if(p_release == NULL)
		{
			lock_taken = 0;
		}
		else
		{
			p_release->SetData(1);
		}

	}
};

			

/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to you under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "ConcQueue.h"
#include <ctime>

#define BILLION 1E9

class QueueLock
{
	ConcQueue<int> lock_queue;
	int lock_taken;
	int number_of_elements;
	float timeout_period;
public:
	QueueLock():lock_taken(0),number_of_elements(0),timeout_period(3.0)
	{
	}

	int GetLock(char *name1)
	{
		struct timespec requestStart, requestEnd;
		if(lock_taken != 0)
		{
			const QueueElement<int> *p_add = lock_queue.AddElement(0);
			++number_of_elements;
			const volatile int *p_spin = p_add->GetPointerToData();

			clock_gettime(CLOCK_REALTIME, &requestStart);

			while(*(p_spin) != 1)
			{
				//Spinning waiting for lock
				clock_gettime(CLOCK_REALTIME, &requestEnd);

				double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
  					+ ( requestEnd.tv_nsec - requestStart.tv_nsec )
  					/ BILLION;

				if(accum >= timeout_period)
				{
					break;
					return (0);
				}

			}

		}

		lock_taken = 1;

		return (1);
	}

	void ReleaseLock(char *name1)
	{
		QueueElement<int> *p_release = lock_queue.GetElement();

		if(p_release == NULL)
		{
			lock_taken = 0;
		}
		else
		{
			--number_of_elements;
			p_release->SetData(1);
		}

	}

	int ForceLock(char *name1)   //Use with EXTREME caution.
	{
		const QueueElement<int> *p_add = lock_queue.AddElementInFront(0);
		const int *p_spin = p_add->GetPointerToData();
		struct timespec requestStart, requestEnd;

		if(lock_taken != 0)
		{
			clock_gettime(CLOCK_REALTIME, &requestStart);

			while(*(p_spin) != 1)
			{
				//Spinning waiting for lock
				clock_gettime(CLOCK_REALTIME, &requestEnd);

				double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
  					+ ( requestEnd.tv_nsec - requestStart.tv_nsec )
  					/ BILLION;

				if(accum >= timeout_period)
				{
					break;
					return (0);
				}

			}

		}

		lock_taken = 1;

		return (1);
	}


	int CheckLockIsAcquired()
	{

		return (lock_taken);
	}

	const int* GetPointerToFlag() const
	{

		return (&lock_taken);
	}

	void SetTimeOutPeriod(float timeout_period_val)
	{
		timeout_period = timeout_period_val;
	}

};

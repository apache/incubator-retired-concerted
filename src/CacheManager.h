#include <iostream>
#include "ConcDef.h"
using namespace std;

class CacheManager
{
	ConcertedDef *val_array[10];
	int current_counter;
public:
	CacheManager()
	{
		int i = 0;

		for (i = 0;i < 10;i++)
		{
			val_array[i] = NULL;
		}

		current_counter = 0;
	}

	virtual ConcertedDef* search_val(...);

	void add_val(ConcertedDef *val)
	{
		if (current_counter < 10)
		{
			val_array[current_counter] = val;
			++current_counter;

			return;
		}

		val_array[0] = val;
	}
};

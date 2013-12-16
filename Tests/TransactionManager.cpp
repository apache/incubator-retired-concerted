#include <iostream>
#include "QueueLock.h"

using namespace std;

class TransactionManager
{
	int active_transaction_number;
	int counter;
	int lock_counter;
	static int active_transactions[10];
	QueueLock *lock_val_array[10];
public:
	TransactionManager()
	{
		int i = 0;

		for(i = 0;i < 10;i++)
		{
			active_transactions[i] = 0;
		}

		active_transaction_number = 0;
		counter = 0;
		lock_counter = 0;

	}

	int add_transaction()
	{

		if (counter == 10)
		{
			cout<<"A new transaction number cannot be inserted due to lack of space"<<endl;
			return -1;
		}

		++active_transaction_number;
		active_transactions[counter] = active_transaction_number;
		++counter;

		return active_transaction_number;
	}

	void delete_transaction(int val)
	{
		int i = 0;

		for (i = 0;i < 10;i++)
		{
			if (active_transactions[i] == val)
			{
				active_transactions[i] = 0;
			}

		}

	}

	void add_lock(QueueLock *val)
	{

		if (lock_counter == 10)
		{
			cout<<"lock cannot be added due to lack of element in array"<<endl;
			return;
		}

		lock_val_array[lock_counter] = val;
		++lock_counter;
	}
};

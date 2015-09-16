#include <iostream>
#include "QueueLock2.h"
#include "ConcDef.h"
using namespace std;

class TransactionManager
{
	static int active_transaction_number;
	int current_transaction_number;
	static int counter;
	int lock_counter;
	int memory_counter;
	int commit_val_counter;
	static int active_transactions[10];
	int delete_val;
	ConcertedDef* current_val[10];
	ConcertedDef* copy_val[10];
	void *mem_allocated_val_array[10];
	QueueLock *lock_val_array[10];
public:
	TransactionManager()
	{
		int i = 0;

		for(i = 0;i < 10;i++)
		{
			current_val[i] = NULL;
			copy_val[i] = NULL;
			active_transactions[i] = 0;
			lock_val_array[i] = NULL;
			mem_allocated_val_array[i] = NULL;
		}

		if (counter == 10)
		{
			cout<<"A new transaction number cannot be inserted due to lack of space"<<endl;
			throw -1;
		}

		current_transaction_number = ++active_transaction_number;
		active_transactions[counter] = active_transaction_number;
		++counter;

		lock_counter = 0;
		memory_counter = 0;
		commit_val_counter = 0;
		delete_val = 1;
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

	void delete_lock(QueueLock *val)
	{
		int i = 0;
		int j = 0;

		for(i = 0;i < lock_counter;i++)
		{
			if (lock_val_array[i] == val)
			{
				lock_val_array[i] = NULL;
				for (j = i;j < lock_counter;j++)
				{
					lock_val_array[j] = lock_val_array[j + 1];
				}

				--lock_counter;
				break;
			}

		}

	}

	int add_mem_location(ConcertedDef *mem)
	{
		if (memory_counter == 10)
		{
			cout<<"new memory location val cannot be added due to lack of element in array"<<endl;
			throw -1;
		}

		mem_allocated_val_array[memory_counter] = mem;
		++memory_counter;

		return 1;
	}

	void delete_mem_location(ConcertedDef *val)
	{
		int i = 0;
		int j = 0;

		for (i = 0; i < memory_counter;i++)
		{
			if (mem_allocated_val_array[i] != NULL)
			{
				if (mem_allocated_val_array[i] == val)
				{
					mem_allocated_val_array[i] = NULL;
					for (j = i;j < memory_counter;j++)
					{
						mem_allocated_val_array[j] = mem_allocated_val_array[j + 1];
					}

					--memory_counter;
					break;
				}

			}

		}

	}

	void delete_transaction(int val)
	{
		int i = 0;
		int j = 0;

		for (i = 0;i < 10;i++)
		{
			if (active_transactions[i] == val)
			{
				active_transactions[i] = 0;
				for (j = i;j < counter;j++)
				{
					active_transactions[j] = active_transactions[j + 1];
				}

				--counter;
			}

		}

	}

	void add_commit_val(ConcertedDef *val, ConcertedDef *copy_val1)
	{

		if (commit_val_counter == 10)
		{
			cout<<"commit val cannot be added due to lack of element in array"<<endl;
			throw -1;
		}

		current_val[commit_val_counter] = val;
		copy_val[commit_val_counter] = copy_val1;
		++commit_val_counter;
	}

	void add_lock(QueueLock *val)
	{

		if (lock_counter == 10)
		{
			cout<<"lock cannot be added due to lack of element in array"<<endl;
			throw -1;
		}

		lock_val_array[lock_counter] = val;
		++lock_counter;
	}

	void commit_transaction()
	{
		int i = 0;

		delete_val = 0;
		for (i = 0;i < commit_val_counter;i++)
		{
			(current_val[i])->copy_pointer_val(copy_val[i]);
		}

		cout<<"commit"<<endl;

	}

	~TransactionManager()
	{
		int i = 0;

		if (delete_val == 1)
		{
			cout<<"Rollback"<<endl;
			for (i = 0;i < lock_counter;i++)
			{
				if (lock_val_array[i] != NULL && (lock_val_array[i])->CheckLockIsAcquired())
				{
					lock_val_array[i]->ReleaseLock();
				}

			}

			i = 0;

			for (i = 0;i < memory_counter;i++)
			{
				if (mem_allocated_val_array[i] != NULL)
				{
					free(mem_allocated_val_array[i]);
				}

			}

		delete_transaction(current_transaction_number);

		}

	}
};

int TransactionManager::counter = 0;
int TransactionManager::active_transaction_number = 0;
int TransactionManager::active_transactions[10] = {0,0,0,0,0,0,0,0,0,0};

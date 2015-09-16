#include "QueueLock.h"

template<class data_val_type> class ConcSegHashTable
{
	data_val_type **hash_tables;
	QueueLock *read_lock_queues;
	QueueLock *write_lock_queues;
	int number_of_segments;
	int number_of_buckets;
	int last_insert_segment;
public:
	ConcSegHashTable(int m,int n)
	{
		int i;
		int j;

		i = 0;
		j = 0;
		number_of_segments = n;
		number_of_buckets = m;
		last_insert_segment = -1;
		hash_tables = new data_val_type*[n];
		for(i = 0;i < n;i++)
		{
			*(hash_tables + i) = new data_val_type[m];
			for(j = 0;j < m;j++)
			{
				*(*(hash_tables + i) + j) = 0;
			}

		}

		read_lock_queues = new QueueLock[m * n];
		write_lock_queues = new QueueLock[m * n];
		read_lock_queues->SetTimeOutPeriod(3.0);
		write_lock_queues->SetTimeOutPeriod(3.0);	
	}

	int HashVal(data_val_type val)
	{

		return ((val/3) + 1);
	}

	int GetReadLock(int seg_index, int pos, char *name1)
	{
		QueueLock *current_write = write_lock_queues + (seg_index + pos);
		QueueLock *current_read = read_lock_queues + (seg_index + pos);
		const volatile int *p_write_lock_flag = current_write->GetPointerToFlag();

		if(current_write->CheckLockIsAcquired() == 1)
		{
			while(*(p_write_lock_flag) != 0)
			{
				//Spinning waiting for write lock to release
			}

		}

		return (current_read->GetLock(name1));
	}

	int GetWriteLock(int seg_index, int pos, char *name1)
	{
		QueueLock *current_write = write_lock_queues + (seg_index + pos);
		QueueLock *current_read = read_lock_queues + (seg_index + pos);
		const int *p_read_lock_flag = current_read->GetPointerToFlag();

		if(current_read->CheckLockIsAcquired())
		{
			while(*(p_read_lock_flag) != 0)
			{
				//Spinning waiting for read lock to release
			}

		}

		return (current_write->GetLock(name1));
	}

	void UpgradeLock(int seg_index, int pos, char *name1)
	{
		int i;

		QueueLock *current_write = write_lock_queues + (seg_index + pos);

		current_write->ForceLock(name1);   //We need to immediately get a write lock in order to upgrade the lock.
		ReleaseReadLock(name1);
	}

	void ReleaseWriteLock(int seg_index, int pos, char *name1)
	{
		QueueLock *current_write = write_lock_queues + (seg_index + pos);

		current_write->ReleaseLock(name1);
		cout<<"Write lock released"<<endl;
	}

	void ReleaseReadLock(int seg_index, int pos, char *name1)
	{
		QueueLock *current_read = read_lock_queues + (seg_index + pos);

		current_read->ReleaseLock(name1);
	}

	int SegmentInsert(int seg_index, data_val_type val, int pos, bool ReplaceValue, char *name1)
	{
		int get_write_lock = 0;
		int get_read_lock = 0;
		int check_lock_status = 0;

		check_lock_status = (write_lock_queues + (seg_index + pos))->CheckLockIsAcquired();
		if(check_lock_status == 1)
		{
			cout<<"Lock already taken"<<endl;
		}
		else
		{	
			get_write_lock = GetWriteLock(seg_index, pos, name1);
			if(get_write_lock == 0)
			{
				cout<<"did not get lock"<<" "<<seg_index<<" "<<pos<<" "<<name1<<endl;
				return (0);
			}

			if(*(*(hash_tables + seg_index) + pos) == 0 || ReplaceValue == true)
			{
				*(*(hash_tables + seg_index) + pos) = val;
				ReleaseWriteLock(seg_index, pos, name1);

				return (1);
			}
			
		}

			return (0);
	}

	int InsertElement(data_val_type val, bool ReplaceValue, char *name1)
	{
		int i;
		int k;
		int j;
		int pos = HashVal(val);

		j = 0;

		if(last_insert_segment == -1)
		{
			k = 0;
		}
		else
		{
			k = last_insert_segment;
		}

		for(i = k;i < number_of_segments;i++)
		{
			if(SegmentInsert(i, val, pos, false, name1) == 1)
			{
				cout<<"value inserted at"<<" "<<i<<" "<<pos<<endl;
				last_insert_segment = i;
				return 1;
			}
		
		}

		for(i = 0;i < k;i++)
		{
			if(SegmentInsert(i, val, pos, false, name1) == 1)
			{
				cout<<"value inserted at"<<" "<<i<<" "<<pos<<endl;
				last_insert_segment = i;
				return 1;
			}

		}

		for(i = k;i < number_of_segments;i++)
		{
			for(j = pos;j < number_of_buckets;j++)
			{
				if(SegmentInsert(i, val, j, false, name1) == 1)
				{
					cout<<"value inserted open addressing"<<" "<<i<<" "<<j<<endl;
					return (1);
				}

			}

		}

		return (0);
	}

	void PrintValues()
	{
		int i;
		int j;

		i = 0;
		j = 0;

		for(i = 0;i < number_of_segments;i++)
		{
			for(j = 0;j < number_of_buckets;j++)
			{
				cout<<i<<" "<<j<<" "<<*(*(hash_tables + i) + j)<<endl;
			}

		}

	}
	~ConcSegHashTable()
	{
		delete hash_tables[number_of_segments];
		delete[] read_lock_queues;
		delete[] write_lock_queues;
	}

};

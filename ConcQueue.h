#ifndef CONCQUEUE_INCLUDED
#define CONCQUEUE_INCLUDED

#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct {

    volatile int lock_value;

} lock_queue;

template<class data_val_type> class QueueElement
{
	data_val_type data_value;
	QueueElement *next;
public:
	QueueElement(data_val_type a):data_value(a),next(NULL)
	{
	}

	data_val_type GetData()
	{
		return data_value;
	}

	void SetData(data_val_type val)
	{
		data_value = val;
	}

	void SetPointer(QueueElement *a)
	{
		next = a;
	}

	QueueElement* GetPointer()
	{
		return next;
	}
};

template<class data_val_type> class ConcQueue
{
	QueueElement<data_val_type> *head;
	QueueElement<data_val_type> *tail;
	lock_queue insertion_lock;
	lock_queue deletion_lock;
public:
	ConcQueue():head(NULL),tail(NULL)
	{
		insertion_lock.lock_value = 0;
		deletion_lock.lock_value = 0;
	}
	
	int CAS(volatile int *val, int compare_value, int swap_value)
	{

		return __sync_bool_compare_and_swap(val, compare_value, swap_value);
	}

	void PrintQueue()
	{
		QueueElement<data_val_type> *traverse = NULL;

		traverse = head;

		while(traverse != NULL)
		{
			cout<<traverse->GetData()<<endl;
			traverse = traverse->GetPointer();
		}
	}
	
	void AddElement(data_val_type val)
	{
		QueueElement<data_val_type> *temp = NULL;
		lock_queue current_lock;
		timespec time1, time2;

		temp = new QueueElement<data_val_type>(val);
		temp->SetPointer(NULL);

		/* Synchronization by locking with compare and swap.The current value of 
                 * lock is compared with the expected value(locked,unlocked) and  
                 * swapped accordingly.Threads spin until they acquire the lock.
                 */
		 while(!(CAS(&(insertion_lock.lock_value), 0, 1)))
		 {
			// Spinning waiting for lock.
		 }

		 if(head == NULL && tail == NULL)
		 {
		 	head = new QueueElement<data_val_type>(val);
		 	tail = head;
			CAS(&(insertion_lock.lock_value), 1 ,0);
		 }
		 else
		 {
		 	tail->SetPointer(temp);
		 	tail = temp;
			CAS(&(insertion_lock.lock_value), 1, 0);
		 }
	}

	QueueElement<data_val_type>* GetElement()
	{
		QueueElement<data_val_type>* current_element = NULL;
		
		current_element = head;
		while(!(CAS(&(deletion_lock.lock_value), 0, 1)))
		{
			//Spin waiting for the lock
		}

		if(head != NULL)
		{
			head = head->GetPointer();
		}

		CAS(&(deletion_lock.lock_value) ,1, 0);

		return (current_element);
	}

	~ConcQueue()
	{
		QueueElement<data_val_type> *temp = NULL;

		temp = head;

		while(head != NULL)
		{
			temp = head->GetPointer();
			delete head;
			head = temp;
		}

	}
};
		 
#endif

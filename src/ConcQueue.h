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

	data_val_type GetData() const
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

	QueueElement* GetPointer() const
	{
		return next;
	}

	const data_val_type* GetPointerToData() const
	{
		return (&data_value);
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
		const QueueElement<data_val_type> *traverse = NULL;

		traverse = head;

		while(traverse != NULL)
		{
			cout<<traverse->GetData()<<endl;
			traverse = traverse->GetPointer();
		}
	}
	
	const QueueElement<data_val_type>* AddElement(data_val_type val)
	{
		QueueElement<data_val_type> *temp = NULL;
		lock_queue current_lock;

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
		 	tail = new QueueElement<data_val_type>(val);
		 	head = tail;
			CAS(&(insertion_lock.lock_value), 1 ,0);

			return (head);
		 }
		 else
		 {
		 	tail->SetPointer(temp);
		 	tail = temp;
			CAS(&(insertion_lock.lock_value), 1, 0);

			return (temp);
		 }
	}

	const QueueElement<data_val_type>* AddElementInFront(data_val_type val)   //Use with EXTREME caution.
	{
		QueueElement<data_val_type> *temp = NULL;
		lock_queue current_lock;

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
		 	tail = new QueueElement<data_val_type>(val);
		 	head = tail;
			CAS(&(insertion_lock.lock_value), 1 ,0);

			return (head);
		 }
		 else
		 {
			temp->SetPointer(head);
			head = temp;
		 }

		 return (temp);
	}
	QueueElement<data_val_type>* GetElement()
	{
		QueueElement<data_val_type> *current_element = head;
		QueueElement<data_val_type> *temp = NULL;
		
		while(!(CAS(&(deletion_lock.lock_value), 0, 1)))
		{
			//Spin waiting for the lock
		}

		if(head != NULL)
		{
			head = head->GetPointer();
		}

		CAS(&(deletion_lock.lock_value) ,1, 0);
		/* When popping an element from the queue and returning it,the
		 * ownership of the element is changed from the queue to the
		 * calling function. Hence, the element is no longer required
		 * to be const.
		 */
		//temp = const_cast<QueueElement<data_val_type>*> (current_element);
		temp = current_element;
		return (temp);
	}

	QueueElement<data_val_type>* SearchQueue(data_val_type val)
	{
		QueueElement<data_val_type> *traverse = head;

		while (traverse != NULL)
		{
			if ((traverse->GetData()) == val)
			{
				return (traverse);
			}

			traverse = traverse->GetPointer();

		}

		cout<<"value not found SearchQueue"<<endl;

		return NULL;
	}

	int GetToFront(QueueElement<data_val_type> val)
	{
		int val_found = 0;
		QueueElement<data_val_type> *traverse = head;
		QueueElement<data_val_type> *traverse2 = head;

		while (traverse != NULL)
		{
			if ((traverse->GetData()) == val)
			{
				cout<<"value found GetToFront"<<endl;
				val_found = 1;
				break;
			}

			traverse2 = traverse;
			traverse = traverse->GetPointer();

		}

		if (val_found == 1)
		{
			traverse2->SetPointer(traverse->GetPointer());
			AddElementInFront(traverse->GetData());
			return 1;
		}

		return -1;
	}

	~ConcQueue()
	{
		QueueElement<data_val_type>* temp = head;

		while(head != NULL)
		{
			temp = head->GetPointer();
			delete head;
			head = temp;
		}

	}
};
		 
#endif

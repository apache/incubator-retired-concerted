#include <iostream>
#include "TransactionManager.h"
using namespace std;

class dct_node:public ConcertedDef
{
	int value;
	int level;
	int current_insertion_index;
	dct_node *child_pointer;
	dct_node *next;
	QueueLock *read_lock_val;
	QueueLock *write_lock_val;
public:
	dct_node()
	{
		value = 0;
		level = 0;
		current_insertion_index = 0;
		child_pointer = NULL;
		next = NULL;
		read_lock_val = new QueueLock;
		write_lock_val = new QueueLock;
	}

	void copy_pointer_val(ConcertedDef *copy_val1)
	{
		//dct_node *val = (dct_node*)val1;
		dct_node *copy_val = (dct_node*)copy_val1;

		cout<<"In dct_node copy_pointer_val"<<endl;
		*this = *copy_val;
	}

	int getval()
	{
		return value;
	}

	void setval(int a)
	{
		value = a;
	}

	int getlevel()
	{
		return level;
	}

	void setlevel(int a)
	{
		level = a;
	}

	void insert(dct_node *pointer_val)
	{
		dct_node *traverse = NULL;

		if (child_pointer == NULL)
		{
			child_pointer = pointer_val;
			return;
		}

		traverse = child_pointer;

		while ((traverse->getnext()) != NULL)
		{
			traverse = traverse->getnext();
		}

		traverse->setnext(pointer_val);

	}

	dct_node* get_child_pointer()
	{
		return child_pointer;
	}

	void setnext(dct_node *next_element_pointer)
	{
		next = next_element_pointer;
	}

	dct_node* getnext()
	{
		return next;
	}

	QueueLock* getread_lock_val()
	{
		return read_lock_val;
	}

	QueueLock* getwrite_lock_val()
	{
		return write_lock_val;
	}

	~dct_node()
	{
		dct_node *traverse = child_pointer;
		dct_node *temp = NULL;

		if (child_pointer != NULL)
		{
			temp = child_pointer->getnext();
		}

		while (traverse != NULL)
		{
			if (child_pointer != NULL)
			{
				delete child_pointer;
			}

			traverse = temp;
			if (traverse != NULL)
			{
				temp = traverse->getnext();
			}

		}

	}
};

class dct_tree
{
	dct_node *dummy;
	int number_of_nodes;
public:
	dct_tree(int n)
	{
		dummy = new dct_node;
		dummy->setlevel(0);
		number_of_nodes = n;
	}

	dct_tree(dct_node *val, int n)
	{
		dummy = val;
		dummy->setlevel(0);
		number_of_nodes = n;
	}

	dct_node* getdummy()
	{
		return dummy;
	}

	int getnumber_of_nodes()
	{
		return number_of_nodes;
	}

	~dct_tree()
	{
		delete dummy;
	}

};

	dct_node* search_val(int[3], dct_node*);
	dct_node* search_node(int, dct_node*);
	dct_node* insert_val(int[3], dct_node*);
	dct_tree* build_dcttree();

	dct_tree* build_dcttree(int n)
	{
		dct_tree *tree_val = NULL;

		tree_val = new dct_tree(n);

		return tree_val;
	}

	dct_node* search_node(int val, dct_node *parent_pointer, int locksTaken)
	{
		dct_node *head = NULL;
		dct_node *traverse = NULL;
		QueueLock *write_lock_val = parent_pointer->getwrite_lock_val();
		QueueLock *read_lock_val = parent_pointer->getread_lock_val();

		if (locksTaken == 0)
		{
			while ((write_lock_val->CheckLockIsAcquired()) == 1)
			{
				cout<<"Waiting for write lock release1"<<endl;
			}

		}

		if (locksTaken == 0)
		{
			read_lock_val->GetLock();
			//cout<<"Taken read lock1"<<endl;
		}

		if (parent_pointer == NULL)
		{
			//cout<<"parent pointer is NULL"<<endl;
			return NULL;
		}

		head = parent_pointer->get_child_pointer();
		if (locksTaken == 0)
		{
			read_lock_val->ReleaseLock();
			//cout<<"Released read lock1"<<endl;
		}

		traverse = head;

		if ((parent_pointer->get_child_pointer()) == NULL)
		{
			cout<<"child pointer is NULL search node"<<endl;
		}
		else
		{
			cout<<"child pointer is not NULL search node"<<" "<<(parent_pointer->get_child_pointer()->getval())<<endl;
		}

		while (traverse != NULL)
		{

			cout<<"In loop"<<endl;
			write_lock_val = traverse->getwrite_lock_val();
			read_lock_val = traverse->getread_lock_val();

			while ((write_lock_val->CheckLockIsAcquired()) == 1)
			{
			}

			if (locksTaken == 0)
			{
				read_lock_val->GetLock();
				//cout<<"Taken read lock2"<<endl;
			}

			if ((traverse->getval()) == val)
			{
				cout<<"value found search"<<" "<<traverse->getval()<<" "<<val<<endl;
				return traverse;
			}
			else
			{
				cout<<"value not found search2"<<" "<<traverse->getval()<<endl;
			}

			if (locksTaken == 0)
			{
				read_lock_val->ReleaseLock();
				//cout<<"Released read lock2"<<endl;
			}

			traverse = traverse->getnext();
		}

		cout<<"value not found"<<endl;
		return NULL;
	}

	dct_node* search_val(int search_val_array[3], dct_tree *tree_val)
	{
		dct_node *dummy = tree_val->getdummy();
		dct_node *traverse = dummy;
		dct_node *temp = NULL;
		int i = 0;
		int current_value = 0;

		for (i = 0;i < (tree_val->getnumber_of_nodes());i++)
		{
			current_value = search_val_array[i];
			temp = search_node(current_value, traverse,1);
			if (temp == NULL)
			{
				cout<<"value not found search val"<<" "<<current_value<<endl;
				return NULL;
			}

			traverse = temp;
		}

		return traverse;

	}

	dct_tree* copy_val(dct_node *val, int number_of_nodes)
	{
		int i = 0;
		dct_node *traverse1 = new dct_node();
		dct_node *traverse2 = val->get_child_pointer();
		dct_node *temp = NULL;
		dct_tree *return_val = NULL;

		i = val->getlevel();

		traverse1->setval(val->getval());
		traverse1->setlevel(val->getlevel());
		for (;i < number_of_nodes;i++)
		{
			while (traverse2 != NULL)
			{
				temp = new dct_node(*(traverse2));
				traverse1->insert(temp);
				copy_val(temp, number_of_nodes);
				traverse2 = traverse2->getnext();
			}

		}

		return_val = new dct_tree(traverse1, number_of_nodes);

		return return_val;

	}

	dct_node* insert_val(int val_array[3], dct_tree *tree_val, TransactionManager &transact_val1)
	{
		dct_tree *val1 = copy_val((tree_val->getdummy()), (tree_val->getnumber_of_nodes()));
		dct_node *dummy = val1->getdummy();
		dct_node *dummy2 = tree_val->getdummy();
		dct_node *traverse = NULL;
		dct_node *temp = NULL;
		dct_node *temp_return = NULL;
		QueueLock *write_lock_val = dummy->getwrite_lock_val();
		QueueLock *read_lock_val = dummy->getread_lock_val();
		int i = 0;

		traverse = dummy;
		transact_val1.add_commit_val(dummy2, dummy);
		for (i = 0;i < (tree_val->getnumber_of_nodes());i++)
		{
			write_lock_val = traverse->getwrite_lock_val();
			read_lock_val = traverse->getread_lock_val();
			transact_val1.add_lock(write_lock_val);
			cout<<"lock value insert1"<<" "<<write_lock_val<<endl;

			while ((read_lock_val->CheckLockIsAcquired()) == 1)
			{
			}

			if (!(write_lock_val->GetLock()))
			{
				cout<<"write lock not taken"<<endl;
				throw -1;
			}
			else
			{
				cout<<"write lock taken"<<endl;
			}

			//throw -1;

			//cout<<"Write lock taken2"<<endl;

			temp_return = search_node(val_array[i], traverse,1);
			if (temp_return == NULL)
			{
				temp = new dct_node;
				temp->setval(val_array[i]);
				temp->setlevel(i);
				traverse->insert(temp);
				write_lock_val->ReleaseLock();
				transact_val1.delete_lock(write_lock_val);
				if ((traverse->get_child_pointer()) == NULL)
				{
					cout<<"child pointer is NULL insert"<<endl;
				}
				else
				{
					cout<<"child pointer is not NULL insert"<<" "<<((traverse->get_child_pointer()->getval()))<<endl;
				}
				//cout<<"Write lock released2"<<endl;
				traverse = temp;
				cout<<"value inserted1"<<" "<<val_array[i]<<endl;
			}
			else
			{
				write_lock_val->ReleaseLock();
				transact_val1.delete_lock(write_lock_val);
				if ((traverse->get_child_pointer()) == NULL)
				{
					cout<<"child pointer is NULL insert2"<<endl;
				}
				else
				{
					cout<<"child pointer is not NULL insert2"<<" "<<((traverse->get_child_pointer())->getval())<<endl;
				}
				//cout<<"Write lock released3"<<endl;
				traverse = temp_return;
				cout<<"value inserted2"<<" "<<val_array[i]<<endl;
			}

			cout<<"val is insert"<<" "<<dummy2<<" "<<dummy<<endl;
			//transact_val1.commit_transaction();
		}

		if (search_node(val_array[0], dummy, 1))
		{
			cout<<"0 value found after insertion"<<endl;
		}
		else
		{
			cout<<"0 value not found after insertion"<<endl;
		}

	}

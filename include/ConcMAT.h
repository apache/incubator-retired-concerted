#include<iostream>
using namespace std;

class mat_node
{
	int value;
	int level;
	int current_insertion_index;
	mat_node *child_pointer_array[10];
public:
	mat_node()
	{
		int i = 0;
		value = 0;
		level = 0;
		current_insertion_index = 0;
		for (i = 0;i < 10;i++)
		{
			*(child_pointer_array + i) = NULL;
		}
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

	void insert(mat_node *pointer_val)
	{
		child_pointer_array[0] = pointer_val;
	}

	mat_node** get_child_pointer_array()
	{
		return child_pointer_array;
	}

	~mat_node()
	{
		mat_node *traverse = child_pointer_array[0];
		int i = 0;

		while(traverse != NULL && i < 10)
		{
			delete traverse;
			++i;
			traverse = *(child_pointer_array + i);
		}

		delete traverse;

	}
};

	class mat_tree
	{
		mat_node *dummy;
		int number_of_attributes;
	public:
		mat_tree(int n)
		{
			dummy = new mat_node;
			dummy->setlevel(0);
			number_of_attributes = n;
		}

		mat_node* getdummy()
		{
			return dummy;
		}

		int getnumber_of_attributes()
		{
			return number_of_attributes;
		}

		~mat_tree()
		{
			delete dummy;
		}
	};

	mat_tree* build_mattree(int);
	mat_node* search_node(int, mat_node*, mat_node*);
	mat_node* search_val(int[3],mat_node*);
	mat_node* insert_val(int[3],mat_node*);

	mat_tree* build_mattree(int n)
	{
		mat_tree* tree_val = NULL;

		tree_val = new mat_tree(n);

		return tree_val;
	}

	mat_node* search_node(int val, mat_node *parent_pointer, mat_node *dummy)
	{
		mat_node **traverse = parent_pointer->get_child_pointer_array();
		mat_node *temp = NULL;
		int i = 0;

		if (parent_pointer == NULL)
		{
			cout<<"parent pointer is NULL"<<endl;
			return NULL;
		}

		while (i < 3)
		{
			temp = *(traverse + i);
			if (temp != NULL)
			{
				if ((temp->getval()) == val)
				{
					cout<<"value found"<<" "<<temp->getval()<<" "<<val<<endl;
					return temp;
				}

			}

			++i;
		}

		cout<<"value not found"<<endl;
		return NULL;
	}

	mat_node* search_val(int search_val_array[3], mat_tree *tree_val)
	{
		mat_node *dummy = tree_val->getdummy();
		mat_node *traverse = dummy;
		mat_node *temp = NULL;
		int i = 0;
		int current_value = 0;

		for (i = 0;i < 3;i++)
		{
			current_value = search_val_array[i];
			temp = search_node(current_value, traverse, dummy);
			if (temp == NULL)
			{
				cout<<"value not found"<<" "<<current_value<<endl;
				return NULL;
			}

			traverse = temp;
		}

	}

	mat_node* insert_val(int val_array[3], mat_tree *tree_val)
	{
		mat_node *dummy = tree_val->getdummy();
		mat_node *traverse = NULL;
		mat_node *temp = NULL;
		mat_node *temp_return = NULL;
		int i = 0;

		traverse = dummy;
		for (i = 0;i < 3;i++)
		{
			temp_return = search_node(val_array[i], traverse, dummy);
			if (temp_return == NULL)
			{
				temp = new mat_node;
				temp->setval(val_array[i]);
				temp->setlevel(i);
				traverse->insert(temp);
				traverse = temp;
			}
			else
			{
				traverse = temp_return;
			}

		}

	}

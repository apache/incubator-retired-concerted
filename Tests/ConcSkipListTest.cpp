#include "../QueueLock.h"

class linked_list
{
	int val;
	linked_list *next;
public:
	linked_list()
	{
		val = 0;
		next = NULL;
	}
	int getval()
	{
		return val;
	}

	void setval(int a)
	{
		val = a;
	}

	linked_list* getnext()
	{
		return next;
	}

	void setnext(linked_list *val)
	{
		next = val;
	}
};

class skip_list_master
{
	int curr_level;
	int max_level;
	float probability_val;
	linked_list **list_array;
public:
	skip_list_master()
	{
		curr_level = 0;
		max_level = 5;
		list_array = NULL;
		probability_val = 0.25;
	}

	void insert_val(int location, int index, linked_list *temp)
	{
		linked_list *traverse = NULL;
		int i = 0;

		if (list_array == NULL)
		{
			list_array = (linked_list**)malloc(sizeof(linked_list*));
			list_array[0] = temp;
			curr_level = 1;

			cout<<"Inserted condition 1"<<" "<<list_array[0]->getval()<<endl;

			return;
		}

		i = index;
		traverse = list_array[location];

		/*while((traverse->getnext()) != NULL && (traverse->getval()) < a && ((traverse->getnext())->getval()) < a)
		{
			cout<<"In loop"<<endl;
			traverse = traverse->getnext();
		}*/

		while (i > 0)
		{
			traverse = traverse->getnext();
			--i;
		}

		if ((traverse->getnext()) == NULL)
		{
			traverse->setnext(temp);
			return;
		}
		/*else if ((traverse->getval()) >= a)
		{
			temp->setnext(traverse);
			return;
		}*/

		temp->setnext(traverse->getnext());
		traverse->setnext(temp);

	}

	void insert_skip(int a)
	{
		linked_list **traverse_skip = NULL;
		linked_list *traverse_list = NULL;
		linked_list *previous_pointer = NULL;
		linked_list *temp = NULL;
		int i = 0;
		int j = 0;
		int level = 0;
		int iteration_value = 0;

		level = level_generate();
		i = level - 1;

		if (level > max_level)
		{
			iteration_value = max_level;
		}
		else
		{
			iteration_value = level;
		}

		temp = (linked_list*)malloc(sizeof(linked_list));

		temp->setval(a);

		if (!list_array)
		{
			insert_val(a, 0, temp);
			return;
		}
		else
		{
			traverse_skip = (linked_list**)malloc(sizeof(linked_list*) * max_level);
		}

		traverse_list = list_array[level - 1];

		for (i = (level - 1);i >= 0;i--)
		{
			previous_pointer = NULL;

			if (j > 0)
			{
				while (j > 0)
				{
					traverse_list = traverse_list->getnext();
					--j;
				}
			}

			if (traverse_list == NULL)
			{
				cout<<"traverse_list is NULL"<<endl;
			}
			else
			{
				cout<<"traverse_list is not NULL"<<endl;
			}

			while (traverse_list != NULL && (traverse_list->getval()) < a)
			{
				cout<<"In loop 2"<<" "<<(traverse_list->getval())<<endl;
				++j;
				previous_pointer = traverse_list;
				traverse_list = traverse_list->getnext();
			}

			traverse_skip[i] = previous_pointer;

			traverse_list = list_array[i];
		}

		insert_val(0, j, temp);
		/*for (i = 1;i <= (level - 1);i++)
		{*/
			
	}


	void print_val()
	{
		linked_list *traverse = NULL;

		if (list_array)
		{
			traverse = list_array[0];
		}

		while (traverse != NULL)
		{
			cout<<"val is"<<" "<<traverse->getval()<<endl;
			traverse = traverse->getnext();
		}
	}

	int level_generate()
	{
		double rand_val = static_cast<double>(rand()) / RAND_MAX;
		int level = 0;

		while (rand_val > probability_val && level < max_level)
		{
			++level;
			rand_val = static_cast<double>(rand()) / RAND_MAX;
		}

		return level;
	}

	int search_val(int key)
	{
		linked_list **traverse_skip = NULL;
		linked_list *traverse_list = NULL;
		int i = 0;
		int j = 0;

		i = curr_level;

		if (!list_array)
		{
			return 0;
		}
		else
		{
			traverse_skip = (linked_list**)malloc(sizeof(linked_list*) * max_level);
		}

		traverse_list = list_array[curr_level - 1];

		for (i = (curr_level - 1);i >= 0;i--)
		{
			if (j > 0)
			{
				while (j > 0)
				{
					traverse_list = traverse_list->getnext();
					--j;
				}
			}

			while (traverse_list != NULL && (traverse_list->getval()) != key)
			{
				cout<<"In loop 2"<<" "<<(traverse_list->getval())<<endl;
				++j;
				traverse_list = traverse_list->getnext();
			}

			if (traverse_list != NULL)
			{
				return 1;
			}

			traverse_list = list_array[i];
		}

		return -1;
	}	
};

int main()
{
	srand(time(0));
	int low = 0;
	int high = 1;
	int result_search = 0;
	double dUniform = static_cast<double>(rand()) / RAND_MAX;
	skip_list_master list1;
	int val1 = list1.level_generate();

	//list1.insert_val(1,0);
	//list1.insert_val(2,0);
	//list1.insert_val(4,0);
	//list1.insert_val(7,0);
	//list1.insert_val(6,0);

	list1.insert_skip(1);
	//list1.insert_skip(2);
	//list1.insert_skip(3);
	//list1.insert_skip(4);
	//list1.insert_skip(5);


	//list1.print_val();

	result_search = list1.search_val(1);

	cout<<"search result"<<" "<<result_search<<endl;

	if (dUniform > 5)
	{
		cout<<"insertion"<<dUniform<<" "<<val1<<endl;
	}
	else
	{
		cout<<"no insertion"<<dUniform<<" "<<val1<<endl;
	}
}

#include<iostream>
using namespace std;

template<int n, int index> class inv_index_node
{
	int key;
	int values_array[10][n-1];
	inv_index_node<n, index> *next;
	int number_of_attributes;
	int index_location;
public:
	inv_index_node()
	{
		int i = 0;
		int j = 0;

		key = 0;

		for(i = 0;i < n;i++)
		{
			for(j = 0;j < 10;j++)
			{
				values_array[i][j] = 0;
			}

		}

		number_of_attributes = n - 1;
		index_location = index;
		next = NULL;
	}

	void setkey(int val)
	{
		key = val;
	}

	int getkey()
	{
		return key;
	}

	void setval(int val, int row, int column)
	{
		values_array[row][column] = val;
	}

	int getval(int row, int column)
	{
		return values_array[row][column];
	}

	void setnext(inv_index_node<n, index> *val)
	{
		next = val;
	}

	inv_index_node<n, index>* getnext()
	{
		return next;
	}

	const int getnumber_of_attributes()
	{
		return number_of_attributes;
	}

	const int getindex_location()
	{
		return index_location;
	}
};

	template<int n, int index> class inv_index
	{
		inv_index_node<n,index> *dummy;
	public:
		inv_index()
		{
			dummy = NULL;
		}

		inv_index_node<n,index>* get_dummy()
		{
			return dummy;
		}

		void insert_val(inv_index_node<n,index> *val)
		{
			inv_index_node<n, index> *traverse = dummy;

			if (dummy == NULL)
			{
				dummy = val;
				return;
			}

			while ((dummy->getnext()) != NULL)
			{
				dummy = dummy->getnext();
			}

			dummy->setnext(val);
		}

	};



	template<int n, int index> int search_val(int *att_values, inv_index<n,index> *index_val)
	{
		int i = 0;
		inv_index_node<n,index> *traverse = index_val->get_dummy();
		int number_of_attributes = traverse->getnumber_of_attributes();
		int index_search = *(att_values + traverse->getindex_location());
		int return_val;
		inv_index_node<n,index> *temp = NULL;

		return_val = 0;

		temp = search_list(index_search, index_val);

		if (temp == NULL)
		{
			cout<<"value not found1"<<" "<<index_search<<endl;
			return -1;
		}

		for (i = 1;i < n;i++)
		{
			if (i != index)
			{
				return_val = search_array_val(*(att_values + i), temp, i);
				//return_val = search_array(&(att_values[1]), (inv_index->get_dummy()));

				if (return_val == -1)
				{
					cout<<"value not found"<<" "<<*(att_values + i)<<" "<<i<<" "<<index<<endl;
					return -1;
				}

			}

		}

		return 1;
	}

	template<int n, int index> inv_index_node<n, index>* search_list(int val, inv_index<n,index> *index_val)
	{
		inv_index_node<n,index> *traverse = index_val->get_dummy();

		while (traverse != NULL && traverse->getkey() != val)
		{
			traverse = traverse->getnext();
		}

		if (traverse == NULL)
		{
			return NULL;
		}

		return traverse;
	}

	template<int n, int index> int search_array(int *val_array, inv_index_node<n,index> *index_node_val)
	{
		int i;
		int j;
		int found;

		i = 0;
		j = 0;
		found = 0;

		for (i = 0; i < (n - 1);i++)
		{
			for (j = 0;j < 10;j++)
			{
				if (*(val_array + i) == (index_node_val->getval(i,j)))
				{
					cout<<"value found"<<" "<<*(val_array + i)<<" "<<i<<" "<<j<<endl;
					++found;
					break;
				}
				else
				{
					cout<<"value not found"<<" "<<*(val_array + i)<<" "<<i<<" "<<j<<endl;
				}
			}
		}

		if (found == (n - 1))
		{
			cout<<"values found"<<" "<<found<<endl;
			return 1;
		}

		cout<<"values not found"<<" "<<found<<endl;
		return -1;
	}

	template<int n, int index> int search_array_val(int val, inv_index_node<n, index> *index_node_val, int index_location)
	{
		int i = 0;

		cout<<"index location value is"<<" "<<val<<" "<<index_location<<endl;
		for (i = 0;i < 10;i++)
		{
			if (i != index)
			{
				if ((index_node_val->getval((index_location - 2), i)) == val)
				{
					cout<<"value found2"<<" "<<val<<" "<<i<<endl;
					return i;
				}
				else
				{
					cout<<"value not found4"<<" "<<val<<" "<<index_node_val->getval((index_location - 2), i)<<" "<<index_location<<endl;
				}

			}

		}

		cout<<"value not found2"<<" "<<val<<" "<<(index_location - 2)<<endl;
		return -1;
	}

	template<int n, int index> int insert_val_array(int val, inv_index<n, index> *index_val, int index_location)
	{
		int i = 0;
		int j = 0;
		int flag_found = 0;
		inv_index_node<n,index> *traverse = index_val->get_dummy();

		cout<<"index_location is"<<" "<<val<<" "<<index_location<<endl;
			for (j = 0;j < 10;j++)
			{
				if ((traverse->getval((index_location - 1), j)) == 0)
				{
					cout<<"empty space found"<<" "<<(index_location - 1)<<" "<<j<<endl;
					flag_found = 1;
					break;
				}

			}

		if (flag_found == 1)
		{
			traverse->setval(val, (index_location - 1), j);
			cout<<"value inserted"<<" "<<val<<" "<<(index_location - 1)<<" "<<j<<endl;
			return 1;
		}

		return -1;
	}

	template<int n,int index> void insert_val(int att_values[], inv_index<n, index> *index_val)
	{
		int i = 0;
		int return_val = 0;
		int return_val_2 = 0;
		inv_index_node<n,index> *traverse = NULL;
		inv_index_node<n,index> *temp = NULL;

		traverse = search_list(*(att_values + index), index_val);

		if (traverse == NULL)
		{
			temp = new inv_index_node<n,index>;
			temp->setkey(*(att_values + index));
			index_val->insert_val(temp);
			traverse = temp;
		}
			
		for (i = 1;i < n;i++)
		{
			if (i != index)
			{
				return_val = search_array_val(*(att_values + i), (index_val->get_dummy()), i);

				if (return_val == -1)
				{
					return_val_2 = insert_val_array(*(att_values + i), index_val, i);

					if (return_val_2 == -1)
					{
						cout<<"value not inserted due to lack of space"<<endl;
						return;
					}

					return_val = 0;
					return_val_2 = 0;
				}

			}

		}

	}

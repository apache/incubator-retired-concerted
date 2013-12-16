Concerted
=========

PLEASE NOTE: The project is highly WIP. Skip lists and Cache are not yet completely working. Please refrain from using them. Rest of the components are completely functional.

Concerted is a highly concurrent library of data structures which is built with in built support for multi variate queries and looks at performing well over many styles of workloads.

The IRC channel is #concerted on Freenode.

The data is read and stored in various data structures, and the data from data structures written to disk.

Concerted is fully ACID compliant.

Concerted has APIs for accessing the data structures available. It aims at abstracting a lot of details from the user and aims to provide an easy to use interface to the user for interacting with the data structures.

Concerted has many different types of indexes, which are useful for various types of queries.

Concerted has various systems to provide access for data analytics and supports   various sorts of data access in different patterns for help in data analysis of different dimensions.

Concerted has locking schemes which allow for high scalability in both read and write.

Concerted implements its own locking manager using g++'s built in atomics.

Dependencies
============

Concerted has to be built with g++, since it uses g++'s built ins.

For running the tests, pthread library is required. It is not required for building or using Concerted itself.

Features of Concerted
=====================

Concerted has many features. We will be discussing three of them here:

ACID Compliant.
Highly read and write scalable.
Support for multi dimensional queries.

Concerted is built on the principle of optimistic concurrency control.


Fundamental Principles behind building Concerted
================================================

Using multidimensional data structures to store data: 

If we store data in multidimensional data structures and use them to read data, then, we can support multivariate queries efficiently, since we will be able to take into consideration the correlation between the different attributes of a table. Data shall be seen in terms of records instead of individual attributes.


Highly Scalable systems: 
Highly scalable systems can be built by fine graining the locking that takes place inside the system. Scalability can be improved by using appropriate locking techniques and ensuring that the costs of locks are less. This also has to be ensured that the time duration of holding the lock is minimized.


Components of Concerted
=======================

The components of Concerted are:


1) Locking manager: The locking manager is the component of Concerted which handles all the locking and concurrency in Concerted.

2) Data store: The data store is the part of Concerted which stores the data and reads and supports queries on the data.

3) Cache: The cache brings in the data in pages of a fixed size from the disk.

4) Transaction Manager: The Transaction Manager handles the transactions and the 'all-or-nothing' aspect of the transactions and operations.



Locking Manager
==============

The locking manager manages the locking in Concerted. It manages the locking with read and write locks and lock upgradation.

The locking manager has locking queues and spinlocks. A lock is granted, and any other request for the lock while the lock is being held by some thread are added to a queue with a flag. The waiting thread checks the value of the flag and once the value of the flag becomes a specific value, the thread can proceed with its operations as it has been granted the lock.

After completing the tasks, the thread which holds the lock currently calls ReleaseLock to release the lock from itself.

The locking manager is designed with NUMA in mind. Hence, the flags for checking whether the lock the thread is waiting for has been granted or not are distributed, so that threads can access the flag in their cache lines, so that the lookup is less expensive.


Data Store
==========

The data store is the component of Concerted which holds the data present in the database. The data is stored in various data structures and written to disk. The data from a specific data structure is read from disk into main memory when queries based on it are present.



Cache
=====

A cache is present which reads the data from disk and keeps it in main memory. The cache has LRU based page replacement algorithm.


Transaction Manager
===================

The Transaction Manager manages the transactions taking place inside the database and ensures consistency in the data. The transaction manager makes all the changes done to the data in a local copy of the data and writes the changes to the main data store only when commit takes place. Commit takes place when all the operations complete successfully.

Examples
========

<pre><code> 

		int att_array[3];
		int i = 0;
		// An object of TransactionManager corresponds to one transaction. When an object is instantiated, a transaction is initiated. If commit_transaction() is not explicitly called, when
		// the object is destroyed, the transaction is auto rollbacked.
		TransactionManager transact_val1;

		// A pointer to a DCT tree instance.
		dct_tree *tree_val = NULL;

		tree_val = build_dcttree(3);
		att_array[0] = 1;
		att_array[1] = 2;
		att_array[2] = 3;
		try
		{
		// insert_val takes in an array of values to be searched, a pointer to an instance of DCT tree and the object of TransactionManager class being used.
		insert_val(att_array, tree_val, transact_val1);

		// Committing the transaction
		transact_val1.commit_transaction();
		}catch (int e)
		{
			cout<<"exception caught"<<" "<<e<<endl;
			return 1;
		}

		if (search_val(att_array, tree_val))
		{
			cout<<"All values found"<<endl;
		}
		else
		{
			cout<<"All values not found"<<endl;
		}
</pre></code>

For more examples of usage, please see the tests included.

Tests
=====

For running any test present in the Tests folder, please use:

g++ [name of code file to compile] -lpthread -lrt



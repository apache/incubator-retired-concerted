Concerted
=========


Concerted is a next generation big data engine aimed at supporting massive in memory reads for OLAP support.

The IRC channel is #concerted on Freenode.

The engine is flexible, with no single point of entry and flexibility to use APIs suited for each use case with full scalability.

Concerted is fully ACID compliant.

Concerted allows applications to use the native APIs to have the flexibility to store, access, scale data in memory on demand. No auxillary infrastructure is needed.

Concerted implements its own locking manager and transaction manager utilizing the object oriented model, thus greatly simplifying the management of processes like commit and abort, depending a lot on the OS's native support.


Dependencies
============

Concerted has to be built with g++, since it uses g++'s built ins.

For running the tests, pthread library is required. It is not required for building or using Concerted itself.

Features
=====================

Concerted was built with the principal of "Write Less Read Many". Although tapes are no longer much in use, the principal of highly scalable reads still applies to big data. In memory scaling of reads can help OLAP engines to have massive read mostly data in memory available on demand and for a high number of concurrent readers.

Imagine a star schema. OLAP engine would like fact table to be present in memory and optimized for high analytical reads. Concerted fills that gap.

Concerted has storage layouts which allow pre aggregation and multi dimensional view of data.

And yes, Concerted's own footprint will not affect your application size!


Plug and Play Model
================================================

Concerted works on the principle of Plug and Play. Instead of providing a fixed engine and structure to mould your data and requirements in, Concerted's dynamic APIs allow you to use Concerted as and when required in your core application while ensuring massive scalability and all of Concerted's features whenever you use them!


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



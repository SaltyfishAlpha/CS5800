#include <vector>
#include "SpareSet.h"
using namespace std;


class Solution {
public:
    void static log(SparseSet<int>& myset)
    {
        for (auto& value : myset.activeIds()) {
			cout<<value<<", ";
		}
        cout<<"\n";
        for (auto& value : myset) {
			cout<<value<<", ";
		}
        cout<<"\n"<<endl;
    }

    void static SparseSetTest(vector<int>& nums) {
        SparseSet myset(nums);
        log(myset);

		cout<<"Erase Test"<<endl;
        myset.erase(5);
        log(myset);
        myset.erase(1);
        log(myset);
        myset.erase(3);
        log(myset);

		cout<<"Insert Test"<<endl;
        size_t id1 = myset.insert(100);
		cout<<id1<<endl;
        log(myset);
        size_t id2 = myset.insert(114);
		cout<<id2<<endl;
        log(myset);
        size_t id3 = myset.insert(514);
		cout<<id3<<endl;
        log(myset);

		cout<<"Edge Test"<<endl;
        myset.erase(myset.size()-1);
        log(myset);
        myset.erase(0);
        log(myset);
        myset.erase(id1);
        log(myset);

    	cout<<"Error Test"<<endl;
		try
		{
			myset.insert(999);
			myset.insert(9999);
			myset.insert(99999);
			myset.insert(999999);
			myset.insert(9999999);
			log(myset);
		} catch (exception& e)
		{
			cerr<<e.what()<<endl;
		}

    	try
    	{
    		myset.erase(100000000);
    		log(myset);
    	} catch (exception& e)
    	{
    		cerr<<e.what()<<endl;
    	}

    	try{
    		size_t id = myset.size()-1;
    		myset.erase(id);
    		myset.erase(id);
    		log(myset);
    	} catch (exception& e)
    	{
    		cerr<<e.what()<<endl;
    	}
    }

	void static VectorLoadTest(size_t SIZE)
    {
    	srand(0);
    	leetcode::ScopedTimer *timer;

    	vector<int> arr(SIZE);

    	timer = new leetcode::ScopedTimer("Vector Insert");
    	for (int i = 0; i < SIZE; ++i)
    		arr[i] = rand();
    	delete timer;

    	timer = new leetcode::ScopedTimer("Vector Modify");
    	for (int i = 0; i < SIZE; ++i)
    		arr[rand() % SIZE] = rand();
    	delete timer;

    	int sum = 0;
    	timer = new leetcode::ScopedTimer("Vector Search");
    	for (auto& value : arr)
    		sum += value;
    	delete timer;
    	cout<<sum<<endl;

    	timer = new leetcode::ScopedTimer("Vector Delete");
    	for (auto i = arr.begin(); i != arr.end(); ++i)
    		arr.erase(i);
    	delete timer;
    }

	void static SparseSetLoadTest(size_t SIZE)
    {
    	srand(0);
    	leetcode::ScopedTimer *timer;

	    SparseSet<int> myset(SIZE);

    	timer = new leetcode::ScopedTimer("Sparse Set Insert");
    	for (int i = 0; i < SIZE; ++i)
			myset.insert(rand());
    	delete timer;

    	timer = new leetcode::ScopedTimer("Sparse Set Modify");
    	for (int i = 0; i < SIZE; ++i)
    		myset[rand() % SIZE] = rand();
    	delete timer;

    	int sum = 0;
    	timer = new leetcode::ScopedTimer("Sparse Set Search");
    	for (auto& value : myset)
    		sum += value;
    	delete timer;
    	cout<<sum<<endl;

    	timer = new leetcode::ScopedTimer("Sparse Set Delete");
    	for (int i = 0; i < SIZE; ++i)
    		myset.erase(i);
    	delete timer;
    }
};


#include "newBag.h"
#include "newBag.h"

#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	{/*TEST CODE FROM testBag.cpp*/
	Bag b;
	assert(b.empty());
	b.start();
	assert(b.ended());

	assert( ! b.contains(42));
	b.insert(42);
	b.insert(42);
	b.insert(83);
	b.insert(91);
	b.insert(83);
	b.insert(103);
	b.insert(83);
	assert(b.size() == 7  && b.uniqueSize() == 4);
	b.start();
	assert( ! b.ended()  &&  b.currentValue() == 42 &&  b.currentCount() == 2);
	b.next();
	assert( ! b.ended()  &&  b.currentValue() == 83 &&  b.currentCount() == 3);
	b.next();
	assert( ! b.ended()  &&  b.currentValue() == 91 &&  b.currentCount() == 1);
	b.next();
	assert(!b.ended());
	b.next();
	assert(b.ended());
	assert(b.contains(42)&&b.contains(83)&&b.contains(91)&&b.contains(103));

	b.erase(42);
	assert(b.size() == 6  && b.uniqueSize() == 4);
	b.insert(42);
	b.insert(42);
	assert(b.count(42)==3);
	assert(b.eraseAll(42)==3);
	assert(b.count(42)==0);
	assert(b.size() == 5  && b.uniqueSize() == 3);

	b.start();
	assert(b.currentCount()==3&&b.currentValue()==83);

	Bag b1;
	Bag b2;
	b1.insert(1);
	b1.insert(1);
	b1.insert(1);
	b1.insert(3);
	b1.insert(3);
	b1.insert(5);


	b2.insert(10);
	b2.insert(10);
	b2.insert(10);
	b2.insert(9);
	b2.insert(9);
	b2.insert(7);
	b2.insert(7);
	b2.insert(7);
	b2.insert(7);
	b2.insert(8);

	b1.swap(b2);

	assert(b1.size()==10 && b1.uniqueSize()==4 && b1.count(10)==3 && b1.count(9)==2 && b1.count(7)==4 && b1.count(8)==1 && !b1.contains(1) && !b1.contains(5));

	assert(b2.size()==6 && b2.uniqueSize()==3 && b2.count(1)==3 && b2.count(3)==2 && b2.count(5)==1 && !b2.contains(10) && !b2.contains(7));


	Bag b2_copied(b2);

	Bag b2_assigned;
	b2_assigned=b2;

	assert(b2.size()==b2_copied.size()&&b2.size()==b2_assigned.size());
	assert(b2.uniqueSize()==b2_copied.uniqueSize()&&b2.uniqueSize()==b2_assigned.uniqueSize());

	for(b2.start(),b2_copied.start(),b2_assigned.start();
		!b2.ended()||!b2_copied.ended()||!b2_assigned.ended();
		b2.next(),b2_copied.next(),b2_assigned.next()){

			assert(b2.currentCount()==b2_assigned.currentCount()
				&&b2.currentCount()==b2_copied.currentCount());
			assert(b2.currentValue()==b2_assigned.currentValue()
				&&b2.currentValue()==b2_copied.currentValue());

	}

	}
	 {/*CODE PROVIDED FROM PROBLEM 5*/
		Bag a(1000);   // a can hold at most 1000 distinct items
		Bag b(5);      // b can hold at most 5 distinct items
		Bag c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
		ItemType v[6] = { 1,2,3,4,5,6 };
		// No failures inserting 5 distinct items twice each into b
		for (int k = 0; k < 5; k++)
		{
			assert(b.insert(v[k]));
			assert(b.insert(v[k]));
		}
		assert(b.size() == 10  &&  b.uniqueSize() == 5  &&  b.count(v[0]) == 2);
		// Failure if we try to insert a sixth distinct item into b
		assert(!b.insert(v[5]));
	
		// When two Bags' contents are swapped, their capacities are swapped
		// as well:
		a.swap(b);
		assert(!a.insert(v[5]));
	 }

	 /*TEST CODE FOR newBag.h*/

	Bag b(100);
	assert(b.empty());
	b.start();
	assert(b.ended());

	assert( ! b.contains(42));
	b.insert(42);
	b.insert(42);
	b.insert(83);
	b.insert(91);
	b.insert(83);
	b.insert(103);
	b.insert(83);
	assert(b.size() == 7  && b.uniqueSize() == 4);
	b.start();
	assert( ! b.ended()  &&  b.currentValue() == 42 &&  b.currentCount() == 2);
	b.next();
	assert( ! b.ended()  &&  b.currentValue() == 83 &&  b.currentCount() == 3);
	b.next();
	assert( ! b.ended()  &&  b.currentValue() == 91 &&  b.currentCount() == 1);
	b.next();
	b.next();
	assert(b.ended());

	assert(b.erase(42));
	assert(b.size() == 6  && b.uniqueSize() == 4);
	b.insert(42);
	b.insert(42);
	assert(b.count(42)==3);
	assert(b.eraseAll(42)==3);
	assert(b.count(42)==0);
	assert(b.size() == 5  && b.uniqueSize() == 3);

	b.start();
	assert(b.currentCount()==3&&b.currentValue()==83);

	Bag b1;
	Bag b2;
	b1.insert(1);
	b1.insert(1);
	b1.insert(1);
	b1.insert(3);
	b1.insert(3);
	b1.insert(5);


	b2.insert(10);
	b2.insert(10);
	b2.insert(10);
	b2.insert(9);
	b2.insert(9);
	b2.insert(7);
	b2.insert(7);
	b2.insert(7);
	b2.insert(7);
	b2.insert(8);

	b1.swap(b2);

	assert(b1.size()==10 && b1.uniqueSize()==4 && b1.count(10)==3 && b1.count(9)==2 && b1.count(7)==4 && b1.count(8)==1 && !b1.contains(1) && !b1.contains(5));

	assert(b2.size()==6 && b2.uniqueSize()==3 && b2.count(1)==3 && b2.count(3)==2 && b2.count(5)==1 && !b2.contains(10) && !b2.contains(7));

	Bag b2_copied(b2);

	Bag b2_assigned;
	b2_assigned=b2;

	assert(b2.size()==b2_copied.size()&&b2.size()==b2_assigned.size());
	assert(b2.uniqueSize()==b2_copied.uniqueSize()&&b2.uniqueSize()==b2_assigned.uniqueSize());

	for(b2.start(),b2_copied.start(),b2_assigned.start(); //cycle through all three (original, copy, and assigned) and make sure that their values match
		!b2.ended()||!b2_copied.ended()||!b2_assigned.ended();
		b2.next(),b2_copied.next(),b2_assigned.next()){
			assert(b2.currentCount()==b2_assigned.currentCount()
				&&b2.currentCount()==b2_copied.currentCount());
			assert(b2.currentValue()==b2_assigned.currentValue()
				&&b2.currentValue()==b2_copied.currentValue());

	}

	for(b2.start();!b2.ended();b2.next()){ //erase all values in the copies and make sure that it does not affect b2
		b2_assigned.eraseAll(b2.currentValue());
		b2_copied.eraseAll(b2.currentValue());
	}

	assert(b2.size()==6 && b2.uniqueSize()==3 && b2.count(1)==3 && b2.count(3)==2 && b2.count(5)==1);
	assert(b2_copied.size()==0 && b2_copied.uniqueSize()==0);
	assert(b2_assigned.size()==0 && b2_assigned.uniqueSize()==0);


	cout << "Passed all tests" << endl;
}

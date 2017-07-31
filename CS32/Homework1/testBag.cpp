#include "Bag.h"
#include "Bag.h"

#include <iostream>
#include <cassert>
using namespace std;

int main()
{
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

	cout << "Passed all tests" << endl;
}

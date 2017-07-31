#ifndef STUDENTBAG_INCLUDED
#define STUDENTBAG_INCLUDED

#include "Bag.h"

class StudentBag
{
public:
	StudentBag();       // Create an empty student bag.

	bool add(unsigned long id);
	// Add a student id to the StudentBag.  Return true if and only
	// if the id was actually added.

	int size() const;
	// Return the number of items in the StudentBag.  If an id was
	// added n times, it contributes n to the size.

	void print();
	// Print every student id in the StudentBag one per line; print as
	// many lines for each id as it occurs in the StudentBag.

private:
	// Some of your code goes here.
	Bag m_bag;
};

#endif

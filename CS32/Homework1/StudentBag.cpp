#include "StudentBag.h"
#include <iostream>

StudentBag::StudentBag(){       // Create an empty student bag.

}
bool StudentBag::add(unsigned long id){
// Add a student id to the StudentBag.  Return true if and only
// if the id was actually added.
	return m_bag.insert(id);
}

int StudentBag::size() const{
// Return the number of items in the StudentBag.  If an id was
// added n times, it contributes n to the size.
	return m_bag.size();
}

void StudentBag::print(){
// Print every student id in the StudentBag one per line; print as
// many lines for each id as it occurs in the StudentBag.
	for(m_bag.start();!m_bag.ended();m_bag.next()){
		for(int i=0; i<m_bag.currentCount();i++){
			std::cout<<m_bag.currentValue()<<std::endl;
		}
	}
}

/*
Answer to Question:
You cannot declare "print" to be const because it ends up modifying
the Bag data member within Studentbag because it calls the "start()"
and "next()" bag member functions, both of which are not const because
they change a data member within "Bag".
*/

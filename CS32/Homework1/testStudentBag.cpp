#include "StudentBag.h"
#include "StudentBag.h"
#include <cassert>

using namespace std;

int main()
{
	StudentBag bag;

	bag.print();

	bag.add(123456789);
	bag.add(123456789);
	bag.add(987654321);
	bag.add(000000001);
	bag.add(000000002);
	bag.add(000000001);
	bag.add(123456789);

	assert(bag.size()==7);
	
	bag.print();

	StudentBag bag_copied (bag);
	StudentBag bag_assigned;
	bag_assigned=bag;

	assert(bag.size()==bag_copied.size()&&
		bag.size()==bag_assigned.size());

	bag_copied.print();
	bag_assigned.print();

}

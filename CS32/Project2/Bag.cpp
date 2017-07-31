#include "Bag.h"

/*BAG CLASS FUNCTION DEFINITIONS*/
//CONSTRUCTORS & DESTRUCTORS
//BAG
Bag::Bag()
	:m_head(NULL,NULL),m_curr(NULL){
	// Create an empty bag.
}
Bag::Bag(const Bag& b)
	:m_head(NULL,NULL),m_curr(b.m_curr){ 
	//Copy Constructor

	const BagItem* bCurr=&b.m_head; //pointer to the current item for the passed object
	BagItem* curr=&m_head; //pointer to the current item for the copy

	while(bCurr->next!=NULL){ //cycle through all of the items for the passed object
		curr->next=new BagItem(bCurr->next->value,bCurr->next->count,curr,NULL); //make an object to point to from the current object with the current object as the previous one

		curr=curr->next;
		bCurr=bCurr->next;
	}
}
Bag::~Bag(){ //Destructor
	BagItem* curr=m_head.next; //keep track of all the current object (starting at the first)
	BagItem* next;

	while(curr!=NULL){ //delete the items until curr is NULL
		next=curr->next; // save where the next item is
		delete curr;
		curr=next;
	}
}

//BAGITEM
Bag::BagItem::BagItem(ItemType val, int count, BagItem* prev, BagItem* next)
	:value(val),count(count),prev(prev),next(next){ //BagItem constructor
}
Bag::BagItem::BagItem(BagItem* prev, BagItem* next)
	:prev(prev), next(next){ //BagItem constructor - used for Bag constructor ONLY to construct m_head with no values
}

//OPERATOR OVERLOADING
//BAG
Bag& Bag::operator=(const Bag& b){
	if(&b!=this){ //make sure that b is not already the same object that is being set equal to it
		Bag temp(b); //use the copy constructor (Because it does a lot of what you need it to) to create a temp object
		swap(temp); //swap the values so that the temp points to the current objects items(they will be deleted when it goes out of scope
	}

	return *this; //return the this pointer so that it can be passed to the next thing after the assignment
}

//FUNCTIONS
//BAG
bool Bag::empty() const{  // Return true if the bag is empty, otherwise false.
	if(m_head.next==NULL){ //if the dummy head object points to NULL, then the bag must be empty
		return true;
	}
	return false;
}
int Bag::size() const{
	// Return the number of items in the bag.  For example, the size
	// of a bag containing "cumin", "cumin", "cumin", "turmeric" is 4.
	BagItem* curr=m_head.next; //start at the first element after head
	int sz=0;

	while(curr!=NULL){ //move along thorugh the list, add the count of each element to sz for each element until curr==NULL
		sz+=curr->count;
		curr=curr->next;
	}

	return sz;
}
int Bag::uniqueSize() const{
          // Return the number of distinct items in the bag.  For example,
          // the uniqueSize of a bag containing "cumin", "cumin", "cumin",
          // "turmeric" is 2.
	BagItem* curr=m_head.next; //start at the first element after head
	int sz=0;

	while(curr!=NULL){ //move along thorugh the list, increment sz for every object
		sz++;
		curr=curr->next;
	}

	return sz;
}
bool Bag::insert(const ItemType& value){
	// Insert value into the bag.  Return true if the value was
	// actually inserted.  Return false if the value was not inserted
	// (perhaps because the bag has a fixed capacity and is full).

	BagItem* curr=&m_head; //start at the head object 

	while(curr->next!=NULL && curr->next->value!=value){ //continue until the next item is null or if the next item matches the value criteria
		curr=curr->next;
	}
	if(curr->next==NULL){ //if it is NULL, then it has hit the end of the list
		curr->next=new BagItem(value,1,curr,NULL);

		return true;
	}
	curr->next->count++; //otherwise increment the item because it fell out of hte loop becuase it matched
	return true;
}
int Bag::erase(const ItemType& value){
          // Remove one instance of value from the bag if present.
          // Return the number of instances removed, which will be 1 or 0.
	BagItem* temp =whereIs(value); //find where the matching item is in the list
	if(temp!=NULL){ //if it exists
		temp->count--;
		if(temp->count==0){ //if thre are no more copies of the same value, call eraseAll, because it will delete that object
			eraseAll(value);
		}
		return 1;
	}
	return 0;
}
int Bag::eraseAll(const ItemType& value){
          // Remove all instances of value from the bag if present.
          // Return the number of instances removed.
	BagItem* temp=whereIs(value); //find where the item is that is to be deleted
	if(temp!=NULL){ //if the item exists
		temp->prev->next=temp->next; //set the previous item to use the next pointer from the object to be deleted

		if(temp->next!=NULL){
			temp->next->prev=temp->prev; //if the next object exists, set it to use the prev pointer from the object to be deleted
		}
		int count=temp->count;

		delete temp;
		return count;
	}
	return 0;
}
bool Bag::contains(const ItemType& value) const{
	// Return true if the value is in the bag, otherwise false.
	if(whereIs(value)!=NULL){ //if the item with the value exists
		return true;
	}
	return false;
}
int Bag::count(const ItemType& value) const{
	// Return the number of instances of value in the bag.
	BagItem* temp=whereIs(value); //find the object

	if(temp!=NULL){
		return temp->count; //return the count, if it exists
	}
	return 0;
}
void Bag::swap(Bag& other){
	// Exchange the contents of this bag with the other one.

	BagItem* temp=m_head.next;

	m_head.next=other.m_head.next;
	if(m_head.next!=NULL){
		m_head.next->prev=&m_head;
	}
	other.m_head.next=temp;
	if(other.m_head.next!=NULL){
		other.m_head.next->prev=&(other.m_head);
	}
}

Bag::BagItem* Bag::whereIs(ItemType val) const{
	//cycle through the list of items and return a pointer to the item that matches the value
	BagItem* curr=m_head.next;
	while(curr!=NULL && curr->value!=val){
		curr=curr->next;
	}
	return curr;
}



/*GLOBAL BAG FUNCTION DEFINITION*/
void combine(Bag& b1, Bag& b2, Bag& result){

	Bag b1_temp(b1);
	Bag b2_temp(b2); //could use iterator from b2 directly, but am i allowed to change that?

	for(b2_temp.start();!b2_temp.ended();b2_temp.next()){ //cycle through b2
		for(int i=0;i<b2_temp.currentCount();i++){
			b1_temp.insert(b2_temp.currentValue()); //insert the value of the current item for every count of one
		}
	}
	result.swap(b1_temp);
}
void subtract(Bag& b1, Bag& b2, Bag& result){

	Bag b1_temp(b1);
	Bag b2_temp(b2); //could use iterator from b2 directly, but am i allowed to change that?

	for(b2_temp.start();!b2_temp.ended();b2_temp.next()){ //cycle through b2
		if(b2_temp.currentCount()>=b1_temp.count(b2_temp.currentValue())){ //if the amount of copies of the value in b2 is greater than the amount in b1
			b1_temp.eraseAll(b2_temp.currentValue()); //delete them all
			continue;
		}
		
		for(int i=0;i<b2_temp.currentCount();i++){
			b1_temp.erase(b2_temp.currentValue()); //remove the value of the current item for every count of one
		}
	}

	result.swap(b1_temp);
}

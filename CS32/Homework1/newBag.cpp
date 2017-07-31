#include "newBag.h"
#include <iostream>
// CONSTRUCTORS
	Bag::Bag(int sz)
		:m_size(sz){
		if(sz<0){
			std::cout<<"The bag may not be of negative size"<<std::endl;
			exit(1);
		}
		m_bag=new BagItem [sz];
	}
	Bag::Bag(const Bag& b)
		:m_size(b.m_size), m_curr(b.m_curr){ //copy the curr and size variables
		
		m_bag=new BagItem [m_size]; //allocate memory of the appropriate size

		for(int i=0;i<m_size;i++){ //copy over the elements of the array
			m_bag[i]=b.m_bag[i];
		}
	}
	Bag::~Bag(){
		delete [] m_bag;
	}
	Bag::BagItem::BagItem() //BagItem Constructor
		:count(0){
	}

// OPERATORS
	Bag& Bag::operator=(const Bag& b){
		if(this!=&b){ //if it equals itself, there is nothing to do
			Bag temp(b); //create a copy of the passed bag (because most of the needed code is already in the copy constructor)
			swap(temp); //swap the values from the copy over to the current value (swaps 
			m_curr=b.m_curr;
		}
		
		return *this;
	}

// MEMBER FUNCTIONS
	bool Bag::empty() const{
		// Return true if the bag is empty, otherwise false.
		for(int i=0;i<m_size;i++){
			if(m_bag[i].count>0){ //if any of the elements are not 0, it is not empty
				return false;
			}
		}
		return true;
	}

	int Bag::size() const{
		// Return the number of items in the bag.  For example, the size
		// of a bag containing "cumin", "cumin", "cumin", "turmeric" is 4.	
		int count=0;
		
		for (int i=0;i<m_size;i++){ //go through every unique element and count the amount of items
			count+=m_bag[i].count;
		}

		return count;
	}

	int Bag::uniqueSize() const{
		// Return the number of distinct items in the bag.  For example,
		// the uniqueSize of a bag containing "cumin", "cumin", "cumin",
		// "turmeric" is 2.
		int count=0;
		
		for(int i=0;i<m_size;i++){
			if(m_bag[i].count>0){ //if any of the elements is not 0, it is not empty
				count++;
			}
		}

		return count;
	}
     
	bool Bag::insert(const ItemType& value){
		// Insert value into the bag.  Return true if the value was
		// actually inserted.  Return false if the value was not inserted
		// (perhaps because the bag has a fixed capacity and is full).

		for(int i=0;i<m_size;i++){ //if the kind of item is not new, increment the object that holds the item
			if(m_bag[i].value==value){
				m_bag[i].count++;
				return true;
			}
		}
		for(int i=0;i<m_size;i++){ //find a spot where there is no value and insert the passed value
			if(m_bag[i].count==0){
				m_bag[i].count=1;
				m_bag[i].value=value;
				return true;
			}
		}
		return false;
	}
     
	int Bag::erase(const ItemType& value){
		// Remove one instance of value from the bag if present.
		// Return the number of instances removed, which will be 1 or 0.
		
		for(int i=0;i<m_size;i++){ //go through the elements
			if(m_bag[i].value==value&&m_bag[i].count>0){ //if the value is found and there is more than 0
				m_bag[i].count--;
				return 1;
			}
		}
		return 0;
	}
	int Bag::eraseAll(const ItemType& value){
		// Remove all instances of value from the bag if present.
		// Return the number of instances removed.

		for(int i=0;i<m_size;i++){ //cycle through all of the objects
			if(m_bag[i].value==value){
				int count = m_bag[i].count;

				m_bag[i].count=0;

				return count;
			}
		}
		return 0;
	}
     
	bool Bag::contains(const ItemType& value) const{
		// Return true if the value is in the bag, otherwise false.
		for(int i=0;i<m_size;i++){
			if(m_bag[i].value==value&&m_bag[i].count>0){
				return true;
			}
		}
		return false;
	}
     
	int Bag::count(const ItemType& value) const{
		// Return the number of instances of value in the bag.
		for(int i=0;i<m_size;i++){
			if(m_bag[i].value==value){
				return m_bag[i].count;
			}
		}
		return 0;
	}
	void Bag::swap(Bag& other){
		// Exchange the contents of this bag with the other one.

		BagItem* tempPtr=m_bag;
		int tempSz=m_size;

		m_bag=other.m_bag;
		m_size=other.m_size;

		other.m_bag=tempPtr;
		other.m_size=tempSz;
		
	}
          // Iteration functions (explained below)
	void Bag::start(){ //initialize where to point (starts at the first element that has an item)
		for(int i=0; i<m_size;i++){
			if(m_bag[i].count>0){
				m_curr=i;
				return;
			}
		}
		m_curr=m_size;
	}
	void Bag::next(){
		for(int i=m_curr+1;i<m_size;i++){ //find the next element with more than zero elements in it
			if(m_bag[i].count>0){
				m_curr=i;
				return;
			}
		}
		m_curr=m_size; //sets m_curr to the array size (off the end by one) if there are no more. 
	}
	bool Bag::ended() const{
		if(m_curr<m_size){ //if it is not off the end, then it must be pointing to an object with count values > 0
			return false;
		}

		return true; //this will only be reached if m_curr is greater than or equal to m_size, which only happens when it is at the end
	}

	const ItemType& Bag::currentValue() const{
		return m_bag[m_curr].value;	
	}
	int Bag::currentCount() const{
		return m_bag[m_curr].count;

	}

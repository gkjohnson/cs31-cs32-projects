#include "Bag.h"

	Bag::Bag(){} //Bag Constructor

	Bag::BagItem::BagItem() //BagItem Constructor
		:count(0){
	}

	bool Bag::empty() const{
		// Return true if the bag is empty, otherwise false.
		for(int i=0;i<DEFAULT_MAX_ITEMS;i++){
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
		
		for (int i=0;i<DEFAULT_MAX_ITEMS;i++){ //go through every unique element and count the amount of items
			count+=m_bag[i].count;
		}

		return count;
	}

	int Bag::uniqueSize() const{
		// Return the number of distinct items in the bag.  For example,
		// the uniqueSize of a bag containing "cumin", "cumin", "cumin",
		// "turmeric" is 2.
		int count=0;
		
		for(int i=0;i<DEFAULT_MAX_ITEMS;i++){
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

		for(int i=0;i<DEFAULT_MAX_ITEMS;i++){ //if the kind of item is not new, increment the object that holds the item
			if(m_bag[i].value==value){
				m_bag[i].count++;
				return true;
			}
		}
		for(int i=0;i<DEFAULT_MAX_ITEMS;i++){ //find a spot where there is no value and insert the passed value
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
		
		for(int i=0;i<DEFAULT_MAX_ITEMS;i++){ //go through the elements
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

		for(int i=0;i<DEFAULT_MAX_ITEMS;i++){ //cycle through all of the objects
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
		for(int i=0;i<DEFAULT_MAX_ITEMS;i++){
			if(m_bag[i].value==value&&m_bag[i].count>0){
				return true;
			}
		}
		return false;
	}
     
	int Bag::count(const ItemType& value) const{
		// Return the number of instances of value in the bag.
		for(int i=0;i<DEFAULT_MAX_ITEMS;i++){
			if(m_bag[i].value==value){
				return m_bag[i].count;
			}
		}
		return 0;
	}
	void Bag::swap(Bag& other){
		// Exchange the contents of this bag with the other one.

		for(int i=0;i<DEFAULT_MAX_ITEMS;i++){
			BagItem temp=m_bag[i];
			m_bag[i]=other.m_bag[i];
			other.m_bag[i]=temp;
		}
	}
          // Iteration functions (explained below)
	void Bag::start(){ //initialize where to point (starts at the first element)
		for(int i=0; i<DEFAULT_MAX_ITEMS;i++){ //cycle through the elements and find the first object that has more than zero items
			if(m_bag[i].count>0){
				m_curr=i;
				return;
			}
		}
		m_curr=DEFAULT_MAX_ITEMS;
	}
	void Bag::next(){
		for(int i=m_curr+1;i<DEFAULT_MAX_ITEMS;i++){ //start at the element one after the current and find the next object to have more than zero elements
			if(m_bag[i].count>0){
				m_curr=i;
				return;
			}
		}
		m_curr=DEFAULT_MAX_ITEMS; //set curr to the max size if there are no more items
	}
	bool Bag::ended() const{
		if(m_curr<DEFAULT_MAX_ITEMS){ //it's only set to the MAX if it has ended
			return false;
		}

		return true; //will return true only if m_curr is greather than or equal to MAX
	}

	const ItemType& Bag::currentValue() const{
		return m_bag[m_curr].value;	
	}
	int Bag::currentCount() const{
		return m_bag[m_curr].count;

	}

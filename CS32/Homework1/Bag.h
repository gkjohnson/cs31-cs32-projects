#ifndef BAG_INCLUDED
#define BAG_INCLUDED

typedef unsigned long ItemType;
const int DEFAULT_MAX_ITEMS = 200;

class Bag{
public:
	Bag();         // Create an empty bag.

	bool empty() const;  // Return true if the bag is empty, otherwise false.

	int size() const;
          // Return the number of items in the bag.  For example, the size
          // of a bag containing "cumin", "cumin", "cumin", "turmeric" is 4.

	int uniqueSize() const;
          // Return the number of distinct items in the bag.  For example,
          // the uniqueSize of a bag containing "cumin", "cumin", "cumin",
          // "turmeric" is 2.
     
	bool insert(const ItemType& value);
          // Insert value into the bag.  Return true if the value was
          // actually inserted.  Return false if the value was not inserted
          // (perhaps because the bag has a fixed capacity and is full).
     
	int erase(const ItemType& value);
          // Remove one instance of value from the bag if present.
          // Return the number of instances removed, which will be 1 or 0.
     
	int eraseAll(const ItemType& value);
          // Remove all instances of value from the bag if present.
          // Return the number of instances removed.
     
	bool contains(const ItemType& value) const;
          // Return true if the value is in the bag, otherwise false.
     
	int count(const ItemType& value) const;
          // Return the number of instances of value in the bag.

	void swap(Bag& other);
          // Exchange the contents of this bag with the other one.

          // Iteration functions (explained below)
	void start();
	void next();
	bool ended() const;
	const ItemType& currentValue() const;
	int currentCount() const;

private:
	class BagItem{
		public:
		BagItem();
		ItemType value;
		int count;
	};

	BagItem m_bag[DEFAULT_MAX_ITEMS];

	int m_curr; //current value its pointing to - must be between 0 and m_amount

};

#endif //BAG_INCLUDED

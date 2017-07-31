#ifndef BAG_INCLUDED
#define BAG_INCLUDED
#define NULL 0

typedef unsigned long ItemType;

/*BAG CLASS DEFINITION*/
class Bag
{
public:
    Bag();
	Bag(const Bag& b);
	~Bag();

	Bag& operator=(const Bag& b);

    bool empty() const;
    int size() const; 
    int uniqueSize() const;
    bool insert(const ItemType& value);
    int erase(const ItemType& value);
    int eraseAll(const ItemType& value);
    bool contains(const ItemType& value) const;
    int count(const ItemType& value) const;
    void swap(Bag& other);
    void start();
    void next();
    bool ended() const;
    const ItemType& currentValue() const;
    int currentCount() const;
private:
	struct BagItem{ //Item in the linked list - the "Node"
		BagItem(ItemType val, int count, BagItem* p, BagItem* n=NULL);
		BagItem(BagItem* prev=NULL, BagItem* next=NULL);

		BagItem* next;
		BagItem* prev;

		ItemType value;
		int count;
	};

	BagItem* whereIs(ItemType val) const;

	BagItem m_head; //Beginning object - Junk object - Always start one after the beginning

	BagItem* m_curr;
};

/*GLOBAL BAG FUNCTIONS*/
void combine(Bag& b1, Bag& b2, Bag& result);
void subtract(Bag& b1, Bag& b2, Bag& result);

/*INLINE FUNCTIONS*/
// Iteration functions
inline void Bag::start(){
	m_curr=m_head.next; //start at the first object after the head
}
inline void Bag::next(){
	m_curr=m_curr->next; //move to the next object
}
inline bool Bag::ended() const{
	if(m_curr==NULL){ //if it is NULL, that means it has run off the end of the list
		return true;
	}
	return false;
}
inline const ItemType& Bag::currentValue() const{
	return m_curr->value;
}
inline int Bag::currentCount() const{
	return m_curr->count;
}

#endif //BAG_INCLUDED

#ifndef _MAPPER_H_
#define _MAPPER_H_
#include <string>

//HASH TABLE Implementation
template<typename T>
class StringMapper
{
public:
	StringMapper(int bucketNum=10000);
    ~StringMapper();
    void insert(std::string from, const T& to);
    bool find(std::string from, T& to) const;
    bool getFirstPair(std::string& from, T& to);
    bool getNextPair(std::string& from, T& to);
	int size() const{return m_distinctCount;}

private:
	//Pairs at each bucket - holds the Key and value and points to the next pair
	struct Pair{
	public:
		Pair(const std::string& newKey, const T& newValue):key(newKey),value(newValue),next(NULL){}
		Pair(const Pair& p):key(p.key),value(p.value){}
		
		std::string key;
		T value;

		Pair* next;
	};
	//Nodes that point to every pair inserted - form a linked list
	struct Node{
	public:
		Node(Pair* newPair,Node* p=NULL, Node* n=NULL):pair(newPair),prev(p),next(n){}
		
		Pair* pair;
		
		Node* prev;
		Node* next;
	};
	int hash(std::string s) const;

	Node m_head;
	Node* m_tail;
	int m_bucketCount;
	Pair** m_buckets;


	int m_distinctCount;

	Node* m_curr;
};

template <typename T>
int StringMapper<T>::hash(std::string s) const
{
	//Hash the id to find which bucket it is in

	unsigned int h=2166136261;
	for(unsigned int i=0;i<s.size();i++)
	{
		h+=s.at(i);
		h*=16777619;
	}

	int id=h%m_bucketCount;

	//if(s.size()==0)return 0;
	return id;
}



//Functions
template <typename T>
StringMapper<T>::StringMapper(int bucketNum=10000)
	:m_head(NULL),m_tail(&m_head),m_bucketCount(bucketNum),m_distinctCount(0),m_curr(NULL)
{//Constructor
	//create the buckets and set them to NULL
	m_buckets=new  Pair* [bucketNum];
	for(int i=0;i<bucketNum;i++){
		m_buckets[i]=NULL;
	}
}

template <typename T>
StringMapper<T>::~StringMapper()
{//Destructor
	//keep track of the current Node and save it in temp so curr can be moved forward before deletion
	Node* curr=m_head.next;
	Node* temp=curr;

	//while there are nodes to delete
	while(curr!=NULL){
		temp=curr;
		curr=curr->next;
		delete temp->pair;
		delete temp;
	}
	delete m_buckets;
}

template <typename T>
void StringMapper<T>::insert(std::string from, const T& to)
{//Insert a new pair into the Hash Table
	//find which bucket to put the pair into
	int hashId=hash(from);
	Pair* newPair;

	//if the proposed bucket is empty, place the bucekt in the root of the bucket
	if(m_buckets[hashId]==NULL){
		m_buckets[hashId]=new Pair(from, to);
		newPair=m_buckets[hashId];
	//other wise, cycle through to the end of the bucket's list and add the node there
	}else{
		Pair* curr=m_buckets[hashId];
		while (curr->next!=NULL){
			//if the key already exists, dont insert
			if(curr->key==from)break;
			curr=curr->next;
		}
		if(curr->key==from)
		{
			curr->value=to;
			return;
		}

		curr->next=new Pair(from, to);
		newPair=curr->next;
	}
	//place a new Node at the end of the list
	m_tail->next=new Node(newPair,&m_head);
	m_tail=m_tail->next;
	m_distinctCount++;
}

template <typename T>
bool StringMapper<T>::find(std::string from, T& to) const
{//find the "from" value in the key, and insert the value into "to"
	//find the bucket where the key would be
	int hashId=hash(from);
	if(m_buckets[hashId]==NULL)return false;

	//cycle through the bucket and look for the key and return if it is found
	Pair* curr=m_buckets[hashId];
	do{
		if(curr->key==from){
			to=curr->value;
			return true;
		}
		curr=curr->next;
	}while(curr!=NULL);
	return false;
}
template <typename T>
bool StringMapper<T>::getFirstPair(std::string& from, T& to)
{//Get the first pair in the list (first one entered) - begins/restarts iteration
	m_curr=m_head.next;
	if(m_curr==NULL)return false;

	from=m_curr->pair->key;
	to=m_curr->pair->value;
	return true;

}
template <typename T>
bool StringMapper<T>::getNextPair(std::string& from, T& to)
{//Get the next pair in the list (based off the previous amount of iterations)
	if(m_curr==NULL)return false;
	m_curr=m_curr->next;
	if(m_curr==NULL)return false;

	from=m_curr->pair->key;
	to=m_curr->pair->value;
	return true;
}

//MAP Implementation
/*
template<typename T>
class StringMapper
{
public:
	StringMapper()
		:m_head(NULL),m_tail(&m_head),m_root(NULL),m_curr(NULL){}

    ~StringMapper();
    void insert(std::string from, const T& to);
    bool find(std::string from, T& to) const;
    bool getFirstPair(std::string& from, T& to);
    bool getNextPair(std::string& from, T& to);
    int size() const;

private:

	struct Pair{
	public:
		Pair(std::string newKey, T& newValue):key(newKey),value(newValue),left(NULL),right(NULL){}
		Pair(const Pair& p):key(p.key),value(p.value){}
		
		std::string key;
		T value;

		Pair* left;
		Pair* right;
	};

	struct Node{
	public:
		Node(Pair* newPair,Node* p=NULL, Node* n=NULL):pair(newPair),prev(p),next(n){}
		
		Pair* pair;
		
		Node* prev;
		Node* next;
	};

	Node m_head;
	Node* m_tail;

	Pair* m_root;
};
*/

#endif // _MAPPER_H_

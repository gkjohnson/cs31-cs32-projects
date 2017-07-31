#include <iostream>
#include <string>
using namespace std;

//****************************
//Function Prototypes
//****************************
int setAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int rotateRight(string a[], int n, int pos);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);


void printArr(string a[],int n){
	for(int i=0;i<n;i++)
		cerr<<" : "<< a[i];
	cerr<<endl;
}
void printArr(int n){
	for(int i=0;i<n;i++)
		cerr<<" : "<< i;
	cerr<<endl;
}

int main(){
	string people[8] = {"adam", "jamie", "tory", "kari","grant", "buster", "scottie", "narrator"};
	string peopleSub[5] = {"tory", "kari","grant","Buster","Adam"};
	string num[10] = {"1","2","3","4","5","6","7","8","9","10"};
	string numRand[15]={"5","3","8","2","8","3","3","6","1","1","7","8","4","7","2"};
//string arr[15];

	//***********************
	//setAll - Pass
	//***********************
/*	printArr(num,10);
	cerr<<endl<<"TESTS:"<<endl;
	cerr<<setAll(num,-10,"Test")<<endl;
	printArr(num,10);
	cerr<<setAll(num,0,"zero")<<endl;
	printArr(num,10);
	cerr<<setAll(num,5,"Test")<<endl;
	printArr(num,10);
	cerr<<setAll(num,10,"Test2")<<endl;
	printArr(num,10);*/
	
	//***********************
	//lookup - pass
	//***********************
	/*printArr(people,8);
	cerr<<endl<<"TESTS:"<<endl;
	cerr<<lookup(people,-10,"adam")<<endl;
	cerr<<lookup(people,0,"adam")<<endl;
	cerr<<lookup(people,8,"Adam")<<endl;
	cerr<<lookup(people,8,"0")<<endl;
	cerr<<lookup(people,8,"adam")<<endl;
	cerr<<lookup(people,8,"jamie")<<endl;
	cerr<<lookup(people,8,"scottie")<<endl;
	cerr<<lookup(people,4,"scottie")<<endl;*/
	
	//***********************
	//positionOfMax - pass
	//***********************
	/*printArr(people,8);
	cerr<<endl<<"TESTS:"<<endl;
	cerr<<positionOfMax(people,-10)<<endl;
	cerr<<positionOfMax(people,0)<<endl;
	cerr<<positionOfMax(people,2)<<endl;
	cerr<<positionOfMax(people,8)<<endl;
	printArr(numRand,15);
	cerr<<positionOfMax(numRand,15)<<endl;*/
	
	//***********************
	//rotateLeft  -pass
	//***********************
	/*printArr(num,10);
	cerr<<endl<<"TESTS:"<<endl;
	cerr<<rotateLeft(num,1,0)<<endl;
	printArr(num,10);
	cerr<<rotateLeft(num,-10,1)<<endl;
	printArr(num,10);
	cerr<<rotateLeft(num,10,-5)<<endl;
	printArr(num,10);
	cerr<<rotateLeft(num,10,20)<<endl;
	printArr(num,10);
	cerr<<rotateLeft(num,0,0)<<endl;
	printArr(num,10);
	cerr<<rotateLeft(num,6,3)<<endl;
	printArr(num,10);
	cerr<<rotateLeft(num,10,4)<<endl;
	printArr(num,10);*/
	//***********************
	//rotateRight - pass
	//***********************
	/*printArr(num,10);
	cerr<<endl<<"TESTS:"<<endl;
	cerr<<rotateRight(num,1,0)<<endl;
	printArr(num,10);
	cerr<<rotateRight(num,-10,1)<<endl;
	printArr(num,10);
	cerr<<rotateRight(num,10,-5)<<endl;
	printArr(num,10);
	cerr<<rotateRight(num,10,20)<<endl;
	printArr(num,10);
	cerr<<rotateRight(num,0,0)<<endl;
	printArr(num,10);
	cerr<<rotateRight(num,6,3)<<endl;
	printArr(num,10);
	cerr<<rotateRight(num,10,5)<<endl;
	printArr(num,10);*/
	//***********************
	//flip - pass
	//***********************
/*	printArr(num,10);
	cerr<<endl<<"TESTS:"<<endl;
	cerr<<flip(num,-10)<<endl;
	printArr(num,10);
	cerr<<flip(num,1)<<endl;
	printArr(num,10);
	cerr<<flip(num,0)<<endl;
	printArr(num,10);
	cerr<<flip(num,5)<<endl;
	printArr(num,10);
	cerr<<flip(num,10)<<endl;
	printArr(num,10);*/

	//***********************
	//differ - pass
	//***********************
	/*string people2[]={"adam","jamie","tory","buster"};
	printArr(people,8);
	cerr<<endl<<"TESTS:"<<endl;
	cerr<<differ(people,-10,people,8)<<endl;
	cerr<<differ(people,8,people,-10)<<endl;
	cerr<<differ(people,0,people,8)<<endl;
	cerr<<differ(people,8,people,0)<<endl;
	cerr<<differ(people,5,people,8)<<endl;
	cerr<<differ(people,8,people,5)<<endl;
	cerr<<differ(people,8,people,8)<<endl;
	cerr<<differ(people,8,num,15)<<endl;
	cerr<<differ(people,8,people2,4)<<endl;*/

	//***********************
	//subsequence - pass
	//***********************
	/*printArr(people,8);
	cerr<<endl<<"TESTS:"<<endl;
	cerr<<subsequence(people,-10,people,8)<<endl;
	cerr<<subsequence(people,8,people,-10)<<endl;
	cerr<<subsequence(people,5,people,8)<<endl;
	cerr<<subsequence(people,8,people,5)<<endl;
	cerr<<subsequence(people,0,people,8)<<endl;
	cerr<<subsequence(people,8,people,0)<<endl;
	cerr<<subsequence(people,8,people,8)<<endl;
	cerr<<subsequence(people,8,num,4)<<endl;
	cerr<<subsequence(people,8,peopleSub,5)<<endl;
	cerr<<subsequence(people,8,peopleSub,3)<<endl;*/
	

	//***********************
	//lookupAny - pass
	//***********************
	/*printArr(people,8);
	cerr<<endl<<"TESTS:"<<endl;
	cerr<<lookupAny(people,-10,people,8)<<endl;
	cerr<<lookupAny(people,8,people,-10)<<endl;
	cerr<<lookupAny(people,0,people,8)<<endl;
	cerr<<lookupAny(people,8,people,0)<<endl;
	cerr<<lookupAny(people,4,people,8)<<endl;
	cerr<<lookupAny(people,8,people,2)<<endl;
	cerr<<lookupAny(people,8,peopleSub,3)<<endl;
	cerr<<lookupAny(people,8,peopleSub,5)<<endl;*/
	
	//***********************
	//split
	//***********************
	/*printArr(people,8);
	cerr<<endl<<"TESTS:"<<endl;
	cerr<<split(people,-10,"")<<endl;
	printArr(people,8);
	cerr<<split(people,0,"")<<endl;
	printArr(people,8);
	cerr<<split(people,4,"m")<<endl;
	printArr(people,8);
	cerr<<split(people,8,"m")<<endl;
	printArr(people,8);
	cerr<<split(people,8,"z")<<endl;
	printArr(people,8);
	cerr<<split(people,8,"A")<<endl;
	printArr(people,8);
	cerr<<split(people,0,"A")<<endl;
	printArr(people,8);
	printArr(numRand,15);
	cerr<<split(numRand,15,"3")<<endl;
	printArr(numRand,15);
	cerr<<split(numRand,15,"9")<<endl;
	printArr(numRand,15);
	cerr<<split(numRand,15,"0")<<endl;
	printArr(numRand,15);*/
	
}

int setAll(string a[], int n, string value){ //set each array element equal to the value
	if(n<0){ //if n is negative
		return -1; //return -1
	}
	for(int i=0;i<n;i++){ //cycle through each array element
		a[i]=value; //assign each the value
	}
	return n;
}
//setAll GOOD
int lookup(const string a[], int n, string target){ //check for the position in the array that contains target and return that position
	if(n<0){ //if n is negative
		return -1; //return -1
	}
	for(int i=0;i<n;i++){ //cycle through each array element
		if(a[i]==target){ //if the element's value is equal to target
			return i; //return the position in the array that has the value equal to target
		}
	}
	return -1; //if it does not find the target string in the array and return, then it could not find it so return -1
}

int positionOfMax(const string a[], int n){ //return the position of the element whos 'value' is the greatest
	if(n<=0){ //if there are zero or negative elements in the array
		return -1; //return -1
	}
	int maxPos=0; //keeps track of the element's position whos value is the largest
	for(int i=0;i<n;i++){ //cycle throught each element in the array
		if(a[i]>a[maxPos]){ //if the current element's value is greater than the previously saved element's value
			maxPos=i; //save the position
		}
	}
	return maxPos;
}

int rotateLeft(string a[], int n, int pos){ //remove the element at pos, shift every element after to the left, and put the removed element at the end
	if(n<0||pos<0||pos>=n){ //if n or pos is negative or if pos is greater than or equal to n
		return -1; //return -1
	}
	string temp=a[pos]; //save the value of the element is being removed
	for(int i=pos+1;i<n;i++){ //cycle through elements of the array, starting at the element after pos increasing to the end
		a[i-1]=a[i]; //shift the current element one to the left
	}
	a[n-1]=temp; //place the saved element in the last position of the array
	return pos;
}

int rotateRight(string a[], int n, int pos){ //remove the element at pos, shift every element after to the right, and put the removed element at the beginning
	if(n<0||pos<0||pos>=n){ //if n or pos is negative or if pos is greater than or equal to n
		return -1; //return -1
	}
	string temp=a[pos]; //save the value of the element is being removed
	for(int i=pos;i>0;i--){ //cycle through elements of the array, starting at the element at pos decreasing to the 0
		a[i]=a[i-1]; //shift the element one less than the current one to the right
	}
	a[0]=temp; //place the saved element in the first position of the array
	return pos;
}

int flip(string a[], int n){ //reverse the order of the elements in the array
	if(n<0){ //if n is negative
		return -1; //return -1
	}
	int i=0; //i represents the left side of the array
	int j=n-1; //j represents the right side of the array
	while(j>=i){ //while i is not at the same spot as j AND while i and j are not only one number apart // could have also used "j-i>1"
			string swap=a[i]; //save the left element to swap
			a[i]=a[j]; //insert the value of the right element into the left
			a[j]=swap; //insert the value of the left element into the right
			i++; //move the left element to the right
			j--; //move the right element to the left
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2){ //compare the arrays element by element and return the position at which they differ
	if(n1<0||n2<0){ //if n1 or n2 are negative
		return -1; //return -1
	}
	int smArraySz=n1; //set smArraySz to the smallest amount of elements between the two arrays
	if(n2<n1){
		smArraySz=n2;
	}
	for(int i=0;i<smArraySz;i++){ //cycle through the amount of elements that the smallest array has
		if(a1[i]!=a2[i]){ //if the elements are not equal to eachother
			return i; //return the element position
		}
	}
	return smArraySz; //return size of the smallest array if no differences are found in the loop
}

int subsequence(const string a1[], int n1, const string a2[], int n2){
	if(n1<0||n2<0){ //if n1 or n2 are negative
		return -1; //return -1
	}else if(n2==0){
		return 0;
	}


	int seqStart=0; //store where the sequence starts
	int j=0; //used to cycle through subsequence array
	for(int i=0;i<n1;i++){ //cycle through array
		if(a1[i]==a2[j]){ //checking if the elements are matching
			if(j==0){
				seqStart=i; //save the start of the sequence if the sequence is just starting
			}
			j++;
			if(j==n2){ // if the end of the subsequence array has been reached.
				return seqStart;
			}
			continue;
		}
		j=0; //reset j if a match is not found
	}
	return -1; //return -1 because the sequence does not exist in the array
}

int lookupAny(const string a1[], int n1, const string a2[], int n2){ //compare every element in the second array against element in the first array and return the first time a match is found
	if(n1<0||n2<0){ //if n1 or n2 are negative
		return -1; //return -1
	}
	for(int i=0;i<n1;i++){ //cycle throught every element in the first array
		for(int j=0;j<n2;j++){ //cycle throught every element in the second array
			if(a1[i]==a2[j]){ //compare one element in the first array to every element in the second, then try the next first array element
				return i;
			}
		}
	}
	return -1; //if a match is not found in the arrays, return -1;
}

int split(string a[], int n, string splitter){ //arrange all elements that are <splitter at the beginning of the array, and move the rest to the end
	if(n<0){ //if n is negative
		return -1; //return -1
	}
	int amtLess=0; //save teh amount of elements in the array that are less than splitter
	for(int i=0;i<n;i++){ //count how many elements are smaller than splitter
		if(a[i]<splitter){
			amtLess++;
		}
	}
	for(int i=0;i<n;i++){ //put any elements that are equal to splitter in the middle of the greater than less than split
		if(a[i]==splitter){
			for(int j=amtLess;j<n;j++){
				if(a[j]==splitter){
					continue;
				}
				a[i]=a[j];
				a[j]=splitter;
				break;
			}
		}
	}
	for(int i=0;i<amtLess;i++){ //cycle throught the first half the array (the portion that is supposed to be less than splitter
		if(a[i]>splitter){ 
			for(int j=amtLess;j<n;j++){ //cycle through the second half of the array (the portion that is supposed to be greater than splitter
				if(a[j]<splitter){ //find an element that is less than splitter in the second half
					string temp=a[i]; //swap the element from the first half and the one from the second half
					a[i]=a[j];
					a[j]=temp;
				}
			}
		}
	}
	return amtLess; //return the position of the first element that is greater than splitter
}
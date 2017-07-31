#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOC_LENGTH = 201;

//Prototypes
int standardizeCriteria(int distance[],
                        char word1[][MAX_WORD_LENGTH+1],
                        char word2[][MAX_WORD_LENGTH+1],
                        int nCriteria);
int calculateScore(const int distance[],
                   const char word1[][MAX_WORD_LENGTH+1],
                   const char word2[][MAX_WORD_LENGTH+1],
                   int nCriteria,
                   const char document[]);

void printArr(int d[],char w1[][MAX_WORD_LENGTH+1],char w2[][MAX_WORD_LENGTH+1],int n){
	for(int i=0;i<n;i++){
		cerr<<d[i]<<"\t"<<w1[i]<<"\t"<<w2[i]<<endl;
	}
}

int main(){
	//**********************************
	// Test StandardizeCriteria Function
	//**********************************
	cerr<<"-StandardizeCriteria-"<<endl;
	/*int dist[6]={-1,-10,0,6,7,0};
	char w1[6][21]={"mad","sad","testing","testing","testing","test"};
	char w2[6][21]={"neg","neg","zero","dist","neg","zero"};
	int sz=6;
	*/
/*	int dist[6]={1,10,5,6,7,8};
	char w1[6][21]={"mad","sad","testing","testing","testing","test"};
	char w2[6][21]={"test8","test","hyphen-","spa ces","per.iod","que?stion"};
	int sz=6;
	*/
	/*int dist[6]={1,10,5,6,7,8};
	char w1[6][21]={"mad8","sad","testing-","test ing","test.ing","te?st"};
	char w2[6][21]={"test","test","hyphen","spaces","period","question"};
	int sz=6;
	*/
	/*int dist[6]={1,10,5,6,7,8};
	char w1[6][21]={"mad8","s,ad","testing-","test ing","test.ing","te?st"};
	char w2[6][21]={"test","test","hyphen","spaces","period","question"};
	int sz=6;
	*/
	/*int dist[6]={1,10,5,6,7,8};
	char w1[6][21]={"mad","","testing","testing","testing",""};
	char w2[6][21]={"","test","one","two","","robot"};
	int sz=6;
	*/
	/*int dist[6]={1,10,5,6,7,8};
	char w1[6][21]={"mad","maD","testing","testing","testing","MAD"};
	char w2[6][21]={"robot","Robot","tests","stuff","tests","RoboT"};
	int sz=6;
	*/
	/*int dist[6]={1,1,2,6,7,1};
	char w1[6][21]={"mad","maD","testing","testing","testing","MAD"};
	char w2[6][21]={"robot","Robot","tests","stuff","tests","RoboT"};
	int sz=6;
	*/
	/*
	int dist[6]={1,10,5,6,7,8};
	char w1[6][21]={"Mad","sad","testing","testing","teSTIng","Test"};
	char w2[6][21]={"test","CAPS","LOCKED","CAPS","CAPSLoCk","QUESTION"};
	int sz=6;
	*/

	
	int dist[6]={1,10,5,6,7,8};
	char w1[6][21]={"ReallyReallyLongWord","sad","thisIsA","testing","teSTIng","ReallyReallyLongWord"};
	char w2[6][21]={"ReallyReallyLongWord","CAPS","ReallyReallyLongWord","CAPS","CAPSLoCk","SuperReallyLongWords"};
	int sz=6;
	
	/*
	int dist[1]={1};
	char w1[1][21]={"test"};
	char w2[1][21]={"test"};
	int sz=1;
	*/
	/*
	int dist[1]={1};
	char w1[1][21]={"test"};
	char w2[1][21]={"test"};
	int sz=0;
	*/
	/*
	int dist[1]={1};
	char w1[1][21]={"test"};
	char w2[1][21]={"test"};
	int sz=-10;
	*/
	/*int dist[7]={1,4,1,3,2,1,13};
	char w1[7][21]={"mad","deranged","NEFARIOUS","half-witted","deranged","Nefarious","have"};
	char w2[7][21]={"scientist","robot","PLOT","assistant","robot","plot","mad"};
	int sz=7;
	*/
	printArr(dist,w1,w2,sz);

	cerr<<endl<<endl;

	sz=standardizeCriteria(dist,w1,w2,sz);
	printArr(dist,w1,w2,sz);
	cerr<<"NEW SIZE: " << sz;

	//**********************************
	// Test CalculateScore Function
	//**********************************

	//char doc[MAX_DOC_LENGTH]="Two have mad scientist have deranged-robot fever. nefarious plot";
	char doc[MAX_DOC_LENGTH]="reallyreallylongword isthis. thisisalsoa reallyreallylongword" ;
	
	/*int dist_2[7]={2,	   4,	        1,	     13    };
	char w1_2[7][21]={"mad",      "deranged", "nefarious", "have"};
	char w2_2[7][21]={"scientist", "robot",     "plot",	     "mad" };
	int sz_2=4;
	*/
	int dist_2[7]={2,	               4,	    1,	                    13     };
	char w1_2[7][21]={"thisisa",              "derranged", "thisisalsoa",          "reallyreallylongword"};
	char w2_2[7][21]={"reallyreallylongword", "robot",     "reallyreallylongword", "isthis" };
	int sz_2=4;
	


	sz_2=standardizeCriteria(dist_2,w1_2,w2_2,sz_2);
	cerr<<"\n\n-CalculateScore-"<<endl;
	cerr<<"\nMatches: "<<calculateScore(dist_2, w1_2, w2_2, sz_2, doc)<<endl<<endl;

}

//Function Definitions
int standardizeCriteria(int distance[],
						char word1[][MAX_WORD_LENGTH+1],
						char word2[][MAX_WORD_LENGTH+1],
						int nCriteria){

	if(nCriteria<0){
		return 0;
	}

	int amtOfCriteria=nCriteria;

	for(int i=0;i<nCriteria;i++){ //set the cStrings to lower case
		for(int j=0;j<MAX_WORD_LENGTH||word1[i][j]!='\0';j++){
			word1[i][j]=tolower(word1[i][j]);
		}
		for(int j=0;j<MAX_WORD_LENGTH||word2[i][j]!='\0';j++){
			word2[i][j]=tolower(word2[i][j]);
		}
	}
	for(int i=0;i<nCriteria;i++){ //compare all the criteria
		for(int j=i+1; j<nCriteria; j++){
			if(strcmp(word1[i],word1[j])==0&&strcmp(word2[i],word2[j])==0){
				int smDistCri=i; // sets the criteria with the smaller distance
				if(distance[i]>distance[j]){ //set the distance of the criteria
					smDistCri=j;			 //with a smaller distance to -1
				}							 //so that it's deleted later
				distance[smDistCri]=-1;
			}
		}
	}
	int cycled;  //keeps track of the amount of criteria cycled through in the next array
				 //if this is not used, the loop could run indefinitely if the last
				 //Criteria's distance is negative
				 //Could instead set the excessive element's distances to 0 after shifting
				 //every time
	for(int i=0, cycled=0;i<nCriteria&&cycled<nCriteria;i++,cycled++){ //delete invalid criteria
		bool del=false;
		if(distance[i]<=0||strlen(word1[i])==0||strlen(word2[i])==0){ //mark for deletion if the distance is not positive
			del=true;
		}
		for(int j=0;j<MAX_WORD_LENGTH&&word1[i][j]!='\0';j++){//check ever word in "word1" and
			if(!isalpha(word1[i][j])){						  //make sure every character is 'a' to 'z'
				del=true;									  //if its not, mark for deletion
				break;
			}
		}
		for(int j=0;j<MAX_WORD_LENGTH&&word2[i][j]!='\0';j++){//same as above for "word2"
			if(!isalpha(word2[i][j])){
				del=true;
				break;
			}
		}
		if(del==true){ //delete the criteria from the list
			for(int j=i+1;j<nCriteria;j++){
				distance[j-1]=distance[j];
				strcpy(word1[j-1],word1[j]);
				strcpy(word2[j-1],word2[j]);
			}
			amtOfCriteria--;
			i--;
		}
	}
	return amtOfCriteria;
}





int calculateScore(const int distance[],
                   const char word1[][MAX_WORD_LENGTH+1],
                   const char word2[][MAX_WORD_LENGTH+1],
                   int nCriteria,
                   const char document[]){


	if(nCriteria<0){
		return 0;
	}
	int matches=0;
	const int dist=0;
	const int w1=1;
	const int w2=2;

	char doc[MAX_DOC_LENGTH];
	strcpy(doc,document);
	
	for(int i=0;i<MAX_DOC_LENGTH&&doc[i]!='\0';i++){
		if(isalpha(doc[i])){ //make every character lowercase
			doc[i]=tolower(doc[i]);
		}else if(!isalpha(doc[i])&&doc[i]!=' '&&doc[i]!='\0'){ //delete any nonalphabetical characters
			for(int j=i+1;j<MAX_DOC_LENGTH;j++){
				doc[j-1]=doc[j];
			}
			i--;
		}
	}

	//at this point, only spaces, alphabetical characters, and the zero byte should be in the string
	for(int j=0;j<nCriteria;j++){ //cycle through the criteria
		bool found=false;
		for(int i=0;i<MAX_DOC_LENGTH||doc[i]!='\0';i++){ //cycle through every letter in doc
			if(found)break;
			if(i==0||doc[i-1]==' '){ //if it's at the start of a new word
				int wordsHit=0; //used to check the distance away from word 1
				int w2Offset=0; 
				int checking=w1; //used to indicate which criteria is being checked against
				if(doc[i]==word1[j][0]){ //and check if it matches the first letter in a word 1
					for(int k=0;i+k<MAX_DOC_LENGTH&&doc[i+k-1]!='\0';k++){ //further increment forward in the document
						if(checking==w1){ //check to see if word 1 is found
							if(doc[i+k]==word1[j][k]){ //checking the letters
								continue;
							}else if(doc[i+k]==' '&&word1[j][k]=='\0'){ //if the end of the word is reached, and a space is found in the document at the same time					
								checking=dist;
							}else{ // else if the letters dont match
								break;
							}
						}else if(checking==dist){ //count the words found, and see if they might match word 2
							if(doc[i+k-1]==' '&&isalpha(doc[i+k])){ //if the beginning of a word is found
								wordsHit++;
								if(doc[i+k]==word2[j][0]){ //check if it could be a part of word 2
									checking=w2;
									w2Offset=k;
								}else if(distance[j]==wordsHit){ //if the distance is equal to the amount of words found
									break;
								}

							}
						}
						
						if(checking==w2){ // check to see if word 2 is found
							//cerr<<endl<<word2[j][k-w2Offset]<<" : "<<k+i<<" : "<<doc[i+k];
							if(word2[j][k-w2Offset]=='\0'&&(doc[i+k]==' '||doc[i+k]=='\0')){ // if the end of word 2 is reached and the end of or a space is reached in the doc
								matches++; //increment the amount of matches
								//cerr<<"\nMATCH!!"<<endl;
								found=true;
								break;
							}else if(word2[j][k-w2Offset]==doc[i+k]){ // if the characters match
								continue; 
							}else  if(word2[j][k-w2Offset]!=doc[i+k]){ //if the word does not match
								checking=dist; //start checking the following words again
							}
						}
					}
				}
			}
		}
	}








	/*for(int i=0;i<MAX_DOC_LENGTH||doc[i]!='\0';i++){ //cycle through every letter in doc
		if(i==0||doc[i-1]==' '){ //if it's at the start of a new word
			for(int j=0;j<nCriteria;j++){ //cycle through the criteria
				int wordsHit=0; //used to check the distance away from word 1
				int w2Offset=0; 
				int checking=w1; //used to indicate which criteria is being checked against
				if(doc[i]==word1[j][0]){ //and check if it matches the first letter in a word 1
					for(int k=0;i+k<MAX_DOC_LENGTH&&doc[i+k-1]!='\0';k++){ //further increment forward in the document
						if(checking==w1){ //check to see if word 1 is found
							if(doc[i+k]==word1[j][k]){ //checking the letters
								continue;
							}else if(doc[i+k]==' '&&word1[j][k]=='\0'){ //if the end of the word is reached, and a space is found in the document at the same time					
								checking=dist;
							}else{ // else if the letters dont match
								break;
							}
						}else if(checking==dist){ //count the words found, and see if they might match word 2
							if(doc[i+k-1]==' '&&isalpha(doc[i+k])){ //if the beginning of a word is found
								if(doc[i+k]==word2[j][0]){ //check if it could be a part of word 2
									checking=w2;
									w2Offset=k;
								}else if(distance[j]==wordsHit){ //if the distance is equal to the amount of words found
									break;
								}
								wordsHit++;
							}
						}
						
						if(checking==w2){ // check to see if word 2 is found
							cerr<<endl<<word2[j][k-w2Offset]<<" : "<<k+i<<" : "<<doc[i+k];
							if(word2[j][k-w2Offset]=='\0'&&(doc[i+k]==' '||doc[i+k]=='\0')){ // if the end of word 2 is reached and the end of or a space is reached in the doc
								matches++; //increment the amount of matches
								break;
							}else if(word2[j][k-w2Offset]==doc[i+k]){ // if the characters match
								continue; 
							}else  if(word2[j][k-w2Offset]!=doc[i+k]){ //if the word does not match
								checking=dist; //start checking the following words again
							}
						}
					}
				}
			}
		}

	}*/

	return matches;
}
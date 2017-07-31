#include "provided.h"
#include <string>
#include <set>
#include "Mapper.h"
using namespace std;

const int MIN_CHAR_LENGTH = 4;
const int MIN_WORD_MATCH_LENGTH=3;

class NewsClusterImpl
{
public:
    NewsClusterImpl();
    bool submitKernelStory(string headline, string url);
    bool submitStory(string headline, string url);
    string getIdentifier() const;
    bool getFirstNewsItem(string& headline, string& url);
    bool getNextNewsItem(string& headline, string& url);
    int size() const;
private:
	bool m_kernelSet;
	StringMapper<string> m_stories;
	set<string> m_ordered;
};

NewsClusterImpl::NewsClusterImpl()
	:m_kernelSet(false)
{//Constructor
}

bool NewsClusterImpl::submitKernelStory(string headline, string url)
{//Save the kernel
	//if there has not been a kernel entered, save the kernel and remember that it has been entered
	if(m_kernelSet)return false;

	m_stories.insert(headline,url);
	m_ordered.insert(headline);
	m_kernelSet=true;
    return true;
}

bool NewsClusterImpl::submitStory(string headline, string url)
{
	if(m_stories.find(headline,std::string())||!m_kernelSet)return false; //if there is not kernel or the url is already included, do not submit the story

	//keep track of the matching words
	bool submit=false;


	set<string>submittedWords;
	WordExtractor exHeadline(headline);
	string word;
	while(exHeadline.getNextWord(word))
	{
		if(word.size()>=MIN_CHAR_LENGTH)submittedWords.insert(word);
	}

	//cycle through every word in the submitted headline

	string clusterHeadline,clusterUrl;
	m_stories.getFirstPair(clusterHeadline,clusterUrl);
	do{ //cycle through the headlines in the cluster
		if(submit)break;
		WordExtractor clusterTitleExtract(clusterHeadline);

		int wordsFoundCount=0;
		set<string>wordsFound;

		string clusterWord;
		while(clusterTitleExtract.getNextWord(clusterWord)){ //cycle through every word in the cluster headline
			if(submit)break; //if the headline is already to be submitted
			if(clusterWord.size()<MIN_CHAR_LENGTH||wordsFound.find(clusterWord)!=wordsFound.end())continue; //if the word is too small or has already been matched

			if(submittedWords.find(clusterWord)!=submittedWords.end())
			{
				wordsFound.insert(clusterWord);
				wordsFoundCount++;
				if(wordsFoundCount>=MIN_WORD_MATCH_LENGTH)
				{
					submit=true;
					break;
				}
				continue;
			}
		}
	}while(m_stories.getNextPair(clusterHeadline,clusterUrl));
	//if enough of the words matched, keep the story
	if(submit)
	{
		m_stories.insert(headline,url);
		m_ordered.insert(headline);
		return true;
	}
    return false;
}

string NewsClusterImpl::getIdentifier() const
{//output and identifier for the Cluster by cycling through a set
	if(m_ordered.size()==0)return "";
	string id=m_ordered.begin()->data();

	set<string>::iterator p=m_ordered.begin();
	p++;
	for(;p!=m_ordered.end();p++){
		id+="+";
		id+=p->data();
	}
    return id;
}

bool NewsClusterImpl::getFirstNewsItem(string& headline, string& url)
{	//return the first pair that was inserted (will be the kernel)
	return m_stories.getFirstPair(headline,url);
}

bool NewsClusterImpl::getNextNewsItem(string& headline, string& url)
{	//return the next story in the map
	return m_stories.getNextPair(headline,url);
}

int NewsClusterImpl::size() const
{	//return the amount of stories
	return m_stories.size();
}

//******************** NewsCluster functions **********************************

// These functions simply delegate to NewsClusterImpl's functions.

NewsCluster::NewsCluster()
{
    m_impl = new NewsClusterImpl();
}

NewsCluster::~NewsCluster()
{
    delete m_impl;
}

bool NewsCluster::submitKernelStory(string headline, string url)
{
    return m_impl->submitKernelStory(headline, url);
}

bool NewsCluster::submitStory(string headline, string url)
{
    return m_impl->submitStory(headline, url);
}

string NewsCluster::getIdentifier() const
{
    return m_impl->getIdentifier();
}

bool NewsCluster::getFirstNewsItem(string& headline, string& url)
{
    return m_impl->getFirstNewsItem(headline, url);
}

bool NewsCluster::getNextNewsItem(string& headline, string& url)
{
    return m_impl->getNextNewsItem(headline, url);
}

int NewsCluster::size() const
{
    return m_impl->size();
}

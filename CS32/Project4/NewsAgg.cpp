#include "provided.h"
#include "Mapper.h"
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int MIN_WORD_LENGTH=4;

class NewsAggregatorImpl
{
public:
    NewsAggregatorImpl();
    void addSourceRSSFeed(string feed);
    int getTopStoriesAndKeywords(double thresholdPercentage,
                    vector<Cluster>& topStories, vector<Keyword>& topKeywords);
private:
	vector<string> m_feeds;
};

NewsAggregatorImpl::NewsAggregatorImpl()
	:m_feeds()
{//Constructor
}

void NewsAggregatorImpl::addSourceRSSFeed(string feed)
{//add an RSS feed to be looked at
	m_feeds.push_back(feed);
}

bool compareClusterBySize(NewsCluster* lhs, NewsCluster* rhs){
	if (lhs->size() > rhs->size())
        return true;
    if (lhs->size() < rhs->size())
        return false;

	string lhsKernel;
	string rhsKernel;
	lhs->getFirstNewsItem(lhsKernel,std::string());
	rhs->getFirstNewsItem(rhsKernel,std::string());

    return lhsKernel < rhsKernel;
}
bool compareKeyword(const Keyword& lhs, const Keyword& rhs){
	if (lhs.numUses > rhs.numUses)
        return true;
	if (lhs.numUses < rhs.numUses)
        return false;

	return lhs.keyword < rhs.keyword;
}

int NewsAggregatorImpl::getTopStoriesAndKeywords(double thresholdPercentage,
                    vector<Cluster>& topStories, vector<Keyword>& topKeywords)
{//Gets the top stories and top keywords in the News

	//Get the stories from the rss feeds
	StringMapper<string> stories;

	for(int i=0;i<m_feeds.size();i++){
		RSSProcessor feed(m_feeds[i]);
		feed.getData();

		string url,title;
		if(!feed.getFirstItem(url,title))continue;
		do{
			//and save it to stories - URL is used as key because any story with the same url is to be tossed
			if(stories.find(url,string()))continue;

			stories.insert(url,title);
		}while(feed.getNextItem(url,title));
	}
	//if there are no stories from the feed

	if(stories.size()==0)return 0;

	//create a new cluster for every story
	vector<NewsCluster*> c;
	c.reserve(stories.size());
	for(int i=0;i<stories.size();i++){
		c.push_back(new NewsCluster());
	}

	{//block this in so the variable can be reused
		string url;
		string title;
		stories.getFirstPair(url,title);

		//place every story in its own cluster as a kernel
		int i=0;
		do{
			c[i]->submitKernelStory(title, url);
			i++;
		}while(stories.getNextPair(url,title));
	}

	//////////////////////////////////////////
	//ADD RELEVANT HEADLINES TO EACH CLUSTER//
	//////////////////////////////////////////
	
	//continue making passes, adding stories to the appropriate cluster until nothing has been added
	//save how many stories are in each cluster
	vector<int> storyCount;
	for(int i=0;i<c.size();i++){
		storyCount.push_back(1);
	}

	for(int i=0;i<c.size();i++) //get first story
	{
		if(storyCount[i]==0)continue; //if the story has already been added somewhere
		bool found=true;
		while(found){ //cycle through every story after it again and again until one is not found to enter
			found=false;
			for(int j=i+1;j<c.size();j++) //cycle through every next story
			{

				string headline, url; 
				c[j]->getFirstNewsItem(headline,url);
				if(c[i]->submitStory(headline,url)) //if the story was submitted properly
				{
					found=true; //update that a story was found
					storyCount[j]=0; //and that the other story has been added to a cluster
				}
				if(c[i]->getIdentifier()==c[j]->getIdentifier()){ //if two identifiers are the same, remove it from the running
					storyCount[j]=0;
				}
			}
		}
		storyCount[i]=c[i]->size(); //save story count for the cluster
	}

	//sort the Clusters
	sort(c.begin(),c.end(),compareClusterBySize);
	//FILL THE PASSED VECTORS

	//empty the two vectors
	topStories.clear();
	topKeywords.clear();

	int validClusters=0;
	for(int i=0;i<c.size();i++) //find the amount of valid clusters left (that are not marked as zero)
	{
		if(storyCount[i]>0)validClusters++;
	}
	//cycle through each cluster, and put all the the stories in the 
	for(int i=0; i<validClusters; i++) //go through for every valid cluster
	{
		if((double)c[i]->size()/stories.size()<thresholdPercentage/100)break; //if the stories begin to drop below the threshold, then stop checking (they are in order at this point)

		string title,url;
		c[i]->getFirstNewsItem(title,url);
		topStories.push_back(Cluster(title));
		topStories[topStories.size()-1].addRelatedURL(url);

		while(c[i]->getNextNewsItem(title,url)) //copy each url in
		{
			topStories[topStories.size()-1].addRelatedURL(url);
		}
	}

	////////////////////////////////
	//GET THE AMOUNT OF EVERY WORD//
	////////////////////////////////
	string headline;
	string currWord;
	vector<Keyword> keyWords;
	stories.getFirstPair(string(),headline);
	do{ //cycle through every headline
		WordExtractor w(headline);
		string foundWords="";
		while(w.getNextWord(currWord)) //cycle through every word in the headline
		{
			if(currWord.length()<MIN_WORD_LENGTH||foundWords.find(currWord)!=string::npos)continue; //if the word is too short or has already been found in this headline

			foundWords+=currWord+"+";

			bool found=false;
			for(int i=0; i<keyWords.size(); i++){
				if(currWord==keyWords[i].keyword){ //if the word has been found in a previous headline, increment the amount of times it was found
					keyWords[i].numUses++;
					found=true;
					break;
				}
			}

			if(!found) //if the word had not been found, then add it to the list
			{
				Keyword k;
				k.keyword=currWord;
				k.numUses=1;
				keyWords.push_back(k);
			}
		}
	}while(stories.getNextPair(string(),headline));

	sort(keyWords.begin(),keyWords.end(),compareKeyword); //sort the keywords by number of uses or alphabetical order

	for(int i=0;i<keyWords.size();i++) //copy the keywords into the passed vector
	{
		if((double)keyWords[i].numUses/stories.size()<thresholdPercentage/100)continue;

		topKeywords.push_back(keyWords[i]);
	}


	//clean up
	for(int i=0;i<c.size();i++) delete c[i];
    return 0;
}


//******************** NewsAggregator functions *******************************

// These functions simply delegate to NewsAggregatorImpl's functions.

NewsAggregator::NewsAggregator()
{
    m_impl = new NewsAggregatorImpl();
}

NewsAggregator::~NewsAggregator()
{
    delete m_impl;
}

void NewsAggregator::addSourceRSSFeed(string feed)
{
    m_impl->addSourceRSSFeed(feed);
}

int NewsAggregator::getTopStoriesAndKeywords(double thresholdPercentage,
                    vector<Cluster>& topStories, vector<Keyword>& topKeywords)
{
    return m_impl->getTopStoriesAndKeywords(thresholdPercentage, topStories,
                                                                  topKeywords);
}

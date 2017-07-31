#include "provided.h"
#include "http.h"
#include <vector>
#include <string>
using namespace std;

class RSSProcessorImpl
{
public:
    RSSProcessorImpl(string rssURL);
    bool getData();
    bool getFirstItem(string& link, string& title);
    bool getNextItem(string& link, string& title);
private:
	int getNextItemFromFeed(const string& data,int begin=0);

	string m_rss;
	vector<string> m_url;
	vector<string> m_headline;

	int m_curr;
};

RSSProcessorImpl::RSSProcessorImpl(string rssURL)
	:m_rss(rssURL)
{
}

bool RSSProcessorImpl::getData()
{//Gets the data of from the RSS feed
	string data;
	if(!HTTP().get(m_rss,data))return false;

	//cycle through the XML and find every item and get the headline/link and put it in the map
	int currPos=0;
	while(currPos!=-1){
		currPos=getNextItemFromFeed(data,currPos);
	}
    return true;
}


bool RSSProcessorImpl::getFirstItem(string& link, string& title)
{//Begins an iteration of the stringMapper object
	m_curr=0;
	if(m_curr>=m_url.size())return false;
	link=m_url[0];
	title=m_headline[0];
	return true;
}

bool RSSProcessorImpl::getNextItem(string& link, string& title)
{//Continues iteration of the stringMapper object
	m_curr++;
	if(m_curr>=m_url.size())return false;
	link=m_url[m_curr];
	title=m_headline[m_curr];
	return true;
}

int RSSProcessorImpl::getNextItemFromFeed(const string& data,int begin)
{//save the next item from the RSS feed
	int start=data.find("<item>",begin); //find the first item tag after the "begin" spot
	if(start==string::npos)return -1;
	start+=+string("<item>").size();

	int end=data.find("</item>",start);
	if(end==string::npos)return -1;
	end+=string("</item>").size();

	int titleBegin=data.find("<title>",start);
	if(titleBegin==string::npos||titleBegin>end)return -1;
	titleBegin+=string("<title>").size(); //find the title value after the item tag
	int titleEnd=data.find("</title>",titleBegin);

	int linkBegin=data.find("<link>",start);
	if(linkBegin==string::npos||linkBegin>end)return -1;
	linkBegin+=string("<link>").size(); //find the link value after the item tag
	int linkEnd=data.find("</link>",linkBegin);

	m_url.push_back(data.substr(linkBegin,linkEnd-linkBegin));
	m_headline.push_back(data.substr(titleBegin,titleEnd-titleBegin));

	return end; //return where item that is being looked at ends
}

//******************** RSSProcessor functions **********************************

// These functions simply delegate to RSSProcessorImpl's functions.

RSSProcessor::RSSProcessor(string rssURL)
{
    m_impl = new RSSProcessorImpl(rssURL);
}

RSSProcessor::~RSSProcessor()
{
    delete m_impl;
}

bool RSSProcessor::getData()
{
    return m_impl->getData();
}

bool RSSProcessor::getFirstItem(string& link, string& title)
{
    return m_impl->getFirstItem(link, title);
}

bool RSSProcessor::getNextItem(string& link, string& title)
{
    return m_impl->getNextItem(link, title);
}

#include "provided.h"
#include "Mapper.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main(int argc, char *argv[])
{
	//ensure that the correct number of arguments was passed
	if(argc!=3 ){
		cout<<"usage: proj4.exe RSSlist thresholdPercentage"<<endl;
		exit(0);
	}
	ifstream rssFeeds(argv[1]); //get the stream
	if(!rssFeeds) //if the stream did not work correctly, then inform the user then exit
	{
		cout<<"error: unable to open RSS list file: "<<argv[1]<<endl;
		exit(0);
	}

	NewsAggregator news; //create a newsAggregator for the feeds
	string s;
	while(getline(rssFeeds,s)){ //get each feed for each site and put them in the Aggregator
		news.addSourceRSSFeed(s);
	}
	cout<<"Finding the top news stories and keywords..."<<endl<<endl;
	vector<Cluster> topClusters;
	vector<Keyword> topKeywords;

	news.getTopStoriesAndKeywords(atof(argv[2]),topClusters,topKeywords); //find top stories and keywords

	if(topClusters.size()==0)cout<<"No newsworthy topics were found."<<endl; //if there are no clusters
	else
	{ //print out every cluster and their URLs
		cout<<"There were "<<topClusters.size()<<" newsworthy topics:"<<endl<<endl;

		for(int i=0;i<topClusters.size();i++)
		{
			cout<<"Cluster # "<<i+1<<" has "<<topClusters[i].getNumURLs()<<" stories about: "<<topClusters[i].getTitle()<<endl;
			string url;
			topClusters[i].getFirstURL(url);
			do cout<<" "<<url<<endl;
			while(topClusters[i].getNextURL(url));
			cout<<endl;
		}
	}
	cout<<endl<<endl; //print two more lines
	if(topKeywords.size()==0)cout<<"No important keywords were found."<<endl; //if there are no keywords
	else
	{ //print out every keyword and their amount of uses
		cout<<"There were "<<topKeywords.size()<<" newsworthy keywords:"<<endl;
		for(int i=0;i<topKeywords.size();i++)
		{
			cout<<" "<<topKeywords[i].keyword<<": "<<topKeywords[i].numUses<<" uses"<<endl;

		}
	}
}
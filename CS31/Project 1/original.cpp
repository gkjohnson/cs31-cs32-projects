// Code for Project 1
// Report poll results
	
#include <iostream>
using namespace std;       // see p. 36-37 in Savitch book
	
int main()
{
    int numberSurveyed;
    int forJerry;
    int forMeg;

    cout << "How many registered voters were surveyed? ";
    cin >> numberSurveyed;
    cout << "How many of them say they will vote for Jerry? ";
    cin >> forJerry;
    cout << "How many of them say they will vote for Meg? ";
    cin >> forMeg;

    double pctJerry = 100.0 * forJerry / numberSurveyed;
    double pctMeg = 100.0 * forMeg / numberSurveyed;
	
	cout.setf(ios::fixed);       // see pp. 31-32 in Savitch book
	cout.precision(1);
	
    cout << endl;
	cout << pctJerry << "% say they will vote for Jerry." << endl;
    cout << pctMeg << "% say they will vote for Meg." << endl;

    if (forJerry > forMeg)
        cout << "Jerry is predicted to win the election." << endl;
    else
        cout << "Meg is predicted to win the election." << endl;
}
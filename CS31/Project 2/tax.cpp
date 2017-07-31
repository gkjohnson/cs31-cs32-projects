#include <iostream>
#include <string>

using namespace std;

int main(){
	//set precision for numbers
	cout.setf(ios::fixed);
	cout.precision(2);
	
	//name input
	string name;
	cout<<"Name: ";
	getline(cin,name); //recieve name input from user

	//taxable income input
	double taxInc;
	cout<<"Taxable income: ";
	cin>>taxInc; //recieve taxable income input from user
	cin.ignore(10000,'\n'); //flush the input stream

	//occupation input
	string occupation;
	cout<<"Occupation: ";
	getline(cin,occupation); //recieve occupation input from user

	//children input
	int children;
	cout<<"Number of children: ";
	cin>>children; //recieve children input from the user
	cin.ignore(10000,'\n'); //flush the input stream

	//calculate final tax amount to pay
	double finalTax=0; //initialize the final amount of tax to pay to 0
	double lowTax=.04; //initialize lowest tax amount percent -- less than 50000
	double midTax=.06; //initialize mid tax amount percent -- between 50000 and 70000
	if(occupation=="engineer"||occupation=="scientist")
		midTax=.05; //reassign the mid tax percent if the user is an engineer or scientist
	double highTax=.09; //initialize highest tax amount percent -- greater than 120000
	
	//logic for tax calculation
	if(taxInc<=50000)
		finalTax=taxInc*lowTax;
	else if(taxInc<=120000)
		finalTax=50000*lowTax+(taxInc-50000)*midTax;
	else if(taxInc>120000)
		finalTax=50000*lowTax+(120000-50000)*midTax+(taxInc-120000)*highTax;

	if(taxInc<120000&&children>0)
		finalTax-=children*200;

	if(finalTax<0)
		finalTax=0;


	//result output
	cout<<"---"<<endl;

	if(name=="")
		cout<<"You must enter a name";
	else if(taxInc<0)
		cout<<"The taxable income must be nonnegative";
	else if(occupation=="")
		cout<<"You must enter an occupation";
	else if(children<0)
		cout<<"The number of children must be nonnegative";
	else
		cout<<name<<" would pay $"<< finalTax;

	cout<<endl;
}
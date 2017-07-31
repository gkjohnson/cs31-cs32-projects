////////////////
//Outlet Class//
////////////////
class Outlet{
public:
	Outlet(string id):m_id(id){};
	virtual ~Outlet(){}

	virtual string connect() const =0;
	virtual string transmit(string msg) const{return "text: "+msg;}
	string id() const {return m_id;}
	
private:
	string m_id;
};

////////////////////////
//TwitterAccount Class//
////////////////////////
class TwitterAccount: public Outlet{
public:
	TwitterAccount(string id);
	virtual ~TwitterAccount();

	virtual string connect() const {return "Tweet";}
};
//TwitterAccount Class Function Implementations
TwitterAccount::TwitterAccount(string id)
	:Outlet(id)
{}

TwitterAccount::~TwitterAccount(){
	cout<<"Destroying the Twitter account "<<id()<<"."<<endl;
}

/////////////////////////
//FacebookAccount Class//
/////////////////////////
class FacebookAccount: public Outlet{
public:
	FacebookAccount(string id);
	virtual ~FacebookAccount();
	
	virtual string connect() const {return "Write to wall";}
};
//FacebookAccount Class Function Implementations
FacebookAccount::FacebookAccount(string id)
	:Outlet(id)
{}

FacebookAccount::~FacebookAccount(){
	cout<<"Destroying the Facebook account "<<id()<<"."<<endl;
}

///////////////
//Phone Class//
///////////////
class Phone: public Outlet{
public:
	Phone(string id, CallType type);
	virtual ~Phone();

	virtual string connect() const {return "Call";}
	virtual string transmit(string msg) const;
private:
	CallType m_type;
};
//Phone Class Function Implementations
Phone::Phone(string id, CallType type)
	:Outlet(id),m_type(type)
{}

Phone::~Phone(){
	cout<<"Destroying the Phone "<<id()<<"."<<endl;
}

string Phone::transmit(string msg) const
{
	string s;
	if(m_type==TEXT){
		s="text";
	}else if(m_type==VOICE){
		s="voice";
	}
	s+=": " + msg;
	return s;
}


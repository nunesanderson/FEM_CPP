#include <string>
#include<vector>
using namespace std;
using std::string;

#ifndef _MESSAGES_INCLUDED_
#define _MESSAGES_INCLUDED_

class Messages
{
public:
	void NotImplementedElement(int elemType, string whereHapp);
	~Messages();
	string logMessage(string);



};
#endif
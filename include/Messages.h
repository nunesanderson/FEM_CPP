#include <string>
#include <vector>
using namespace std;
using std::string;

#ifndef _MESSAGES_INCLUDED_
#define _MESSAGES_INCLUDED_

class Messages
{
public:
	/**
 * Prints a message
 * 
 * @param message: message to print
*/
	void logMessage(string message);

	/**
	 * Print a specific message of non-implemented element
	 * 
	 * @param elemType: element type
	 * @param whereHapp: function where it happened
	*/
	void NotImplementedElement(int elemType, string whereHapp);

	// TODO: check whether it is necessary
	~Messages();
};
#endif
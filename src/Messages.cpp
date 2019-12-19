#include <string>
#include<vector>
using namespace std;
using std::string;
#include <iostream>
#include <ctime>
#include <time.h>
#pragma warning(disable : 4996)

/* ------------------------------------------------------------------------
Internal includes
---------------------------------------------------------------------------*/
#include "../include/Messages.h"

void Messages::NotImplementedElement(int elemType, string whereHapp) {

	cout << "Element not implemented: Type: " << std::to_string(elemType) << " - " << whereHapp << endl;
}

Messages::~Messages() {};

void Messages::logMessage(string message) {
	char buff[20];
	struct tm *sTm;

	time_t now = time(0);
	sTm = localtime(&now);

	strftime(buff, sizeof(buff), "%H:%M:%S", sTm);
	cout << "["<< buff << "] " << message<< endl;


}
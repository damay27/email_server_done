#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS

#include <string>
using namespace std;

//These functions are used accross multiple sub programs and as such are
//combined into this "library"

void blankOutPassword(string *password);

long unsigned int myHash(string userName, string password);

bool authUser(string userName, string password);

string cryptString(string msg, string key);

bool findUser(string userName);

#endif
#include "helperFunctions.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include "sodium.h"
using namespace std;


void blankOutPassword(string *password)
{
    //Fill the password memory with pre defined pattern
    int length = (int)password->size();
    for(int i = 0; i < length; i++)
    {
        password->at(i) = 'D';
    }
}

long unsigned int myHash(string userName, string password)
{
    string const_salt = "Iya9bNGTu8XP2ZtQM1sbTspbftV3ffSzqOMVRtKSB9FUQo3yGPGqWF0nKjLd9GOmVFxQS3WdXP6GxVa1";
    
    string userNameRev = userName;
    reverse(userName.begin(), userName.end());
    
    string passwordRev = password;
    reverse(password.begin(), password.end());
    
    string str = userNameRev + const_salt + passwordRev + userName + const_salt + password;
    
    int size = str.size();
    
    int count = size;
    
    long unsigned int hash = 0;
    
    for(int i = size-1; i > -1; i--)
    {
        hash += str.at(i) * count;
        count--;
    }
    
    blankOutPassword(&password);
    
    
    return hash;
    
}




bool authUser(string userName, string password)
{
    
    unsigned long int hashedPassword = myHash(userName, password);
    
    //Open the file
    fstream file;
    
    file.open("./dat/Users");
    
    if(!file.is_open())
    {
        cout<<"Error"<<endl;
        return -1;
    }
    

    //Loop through all the user names and make sure the new username is unique
    bool goodMatch = false;
    //Username file is formated that one line userName next line password
    while(1)
    {
        string userNameLine;
        getline(file, userNameLine);
        string passwordLine;
        getline(file, passwordLine);
        
        
        if(userName == userNameLine && to_string(hashedPassword) == passwordLine)
        {
            goodMatch = true;
            break;
        }
        
        
        
        if(file.eof())
        {
            goodMatch = false;
            break;
        }
        
        
    }
    
    blankOutPassword(&password);
    
    return goodMatch;
    
}



string cryptString(string msg, string key)
{
    const unsigned char NONCE[21] = "1EJzaaK9LVYCGO2XXrQ3";
    
    string output;
    output.resize(msg.size());
    
    crypto_stream_salsa20_xor( (unsigned char*)output.c_str(), (const unsigned char*)msg.c_str(), msg.size(), NONCE, (const unsigned char*)key.c_str());
    
    
    return output;
}


//This function is used to determine if a user is currently registered on the
//server.
bool findUser(string userName)
{
    //Check to make sure the user the message is being sent to exists in it
    //Open the file
    fstream file;
    
    file.open("./dat/Users");
    
    if(!file.is_open())
    {
        cout<<"Error"<<endl;
        return -1;
    }
    
    //This loop run until either the receiveUser user name is found or the
    //end of the file is reached
    while(!file.eof())
    {
        //Username file is formated that one line userName next line password
        string userNameLine;
        getline(file, userNameLine);
        string passwordLine;
        getline(file, passwordLine);
        
        
        if(userName == userNameLine)
        {
            file.close();
            
            return true;
        }
        
    }
    
    file.close();
    
    return false;
}
#include <iostream>
#include <string>
#include <fstream>
#include "helperFunctions.hpp"
#include <ctime>
#include <sodium.h>
#include <exception>
using namespace std;


int main() {
   
    cout << "Content-type: text/plain" << endl;
    cout << endl;
    
    if (sodium_init() == -1) {
      cout<<"Local Error."<<endl;
      return 1;
    }
    
    //Get the username and password from the post request
    //User name => the user name of the person sending the message
    //password => the password of the person sending the message
    //key => the key used to decrypt the message
    //msgNumberStr => the line number of the message in the users message file
    //                to decrypt and return
    string userName, password, key, msgNumberStr;
    getline(cin, userName);
    getline(cin, password);
    getline(cin, key);
    getline(cin, msgNumberStr);
    
    //Detect newline charactes
    if(userName.find('\n') != string::npos || 
        password.find('\n') != string::npos)
    {
        cout<<"Username and password cannot contian return character."<<endl;
    }


    //Make sure the user is who they say they are
    bool authOK = authUser(userName, password);
    
    
    if(authOK)
    {
        string msg;
        
        //Open the users message file
        ifstream file;
        file.open("./dat/msg/" + userName, ios::binary);
        
        int msgNumber;
        
        //Convert the string message number to an int. This needs the try catch
        //since the user could enter a non numeric character
        try {
            msgNumber = stoi(msgNumberStr);
        }
        catch (exception e) {
            cout<<"Invalid input error."<<endl;
            cout<<msgNumberStr<<endl;
            return -1;
        }
        
        //Loop through the file until you have read the line that contains the
        //message you want
        int index = 0;
        while( !(index > msgNumber) )
        {
            getline(file, msg);
            index++;
        }
        
        
        //Only keep the portion of the message that comes after the colon
        int colonIndex = msg.find(":");
        string hexStr = msg.substr(colonIndex+1);
        
        
        msg = "";
        
        
        for(int i = 0; i<hexStr.size(); i+=2)
        {
            string hexChar = "";
            hexChar += hexStr.at(i);
            hexChar+=hexStr.at(i+1);
            msg += (const char)stoi(hexChar, nullptr, 16);
        }
        
        //Decrypt the message
        msg = cryptString(msg, key);
        
        cout<<msg<<endl;
        
        cout.clear();
        
    }
    else
    {
        cout<<"Error loging in."<<endl;
    }
    
    
    //Clear the password from memory
    blankOutPassword(&password);
    

    return 0;
   
   

}



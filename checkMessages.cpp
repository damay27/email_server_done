#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "helperFunctions.hpp"
using namespace std;


int main() {
   
    cout << "Content-type: text/plain" << endl;
    cout << endl;
    
    //Get the username and password from the post request
    //User name => the user name of the person sending the message
    //password => the password of the person sending the message
    //receiveUser => the user name of the person who will receive the message
    //message => the actual text of the message that is being sent
    string userName, password;
    getline(cin, userName);
    getline(cin, password);

    
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
        cout<<"Login OK."<<endl;
        
            ifstream file;
            file.open("./dat/msg/" + userName, ios::binary);
            
            int lineNumber = 0;
            
            while(!file.eof())
            {
                string line;
                getline(file, line);
                
                if(line.find(":") != string::npos)
                {
                    int colonIndex = line.find(":");
                    cout<<lineNumber<<". "<<line.substr(0, colonIndex)<<endl;
                    lineNumber++;
                }
            }

        
    }
    else
    {
        cout<<"Error loging in."<<endl;
    }
    
    
    blankOutPassword(&password);
    

    return 0;
   
   

}



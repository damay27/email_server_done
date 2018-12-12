#include <iostream>
#include <string>
#include <fstream>
#include "helperFunctions.hpp"
#include <ctime>
#include <sstream>
using namespace std;

/*

    This program recieves a message from the client with the additional
    information needed to determine where to store it and how to encrypt it.
    
    As user input the program needs:
        *user name
        *password
        *user to receive the message
        *the key to encrypt the message with
        *the message contents

*/

int main() {
   
    cout << "Content-type: text/plain" << endl;
    cout << endl;
    
    //Get the username and password from the post request
    //User name => the user name of the person sending the message
    //password => the password of the person sending the message
    //receiveUser => the user name of the person who will receive the message
    //key => the key used to encrypt the message
    //message => the actual text of the message that is being sent
    string userName, password, receiveUser, key, message;
    getline(cin, userName);
    getline(cin, password);
    getline(cin, receiveUser);
    getline(cin, key);
    getline(cin, message);
    
    //Detect newline charactes
    if(userName.find('\n') != string::npos || 
        password.find('\n') != string::npos ||
        receiveUser.find('\n') != string::npos ||
        message.find('\n') != string::npos)
    {
        cout<<"Username and password cannot contian return character."<<endl;
    }


    if(key.size()>=message.size())
    {
        cout<<"Key must be shorter than message."<<endl;
        return -1;
    }

    //Make sure the user is who they say they are
    bool authOK = authUser(userName, password);
    
    
    //Check authentication
    if(authOK)
    {
        cout<<"Login OK."<<endl;
        
        //Look for the receiving user in the list of users 
        bool foundUser = findUser(receiveUser);
        
        //If the user being sent the message was found
        if(foundUser)
        {
            //Open the receiving users message file
            ofstream outFile;
            outFile.open("./dat/msg/" + receiveUser, ios::app | ios::binary);
            
            //Encrypt the message
            message = cryptString(message, key);
            
            stringstream stream;
            for(int i = 0; i<message.size(); i++)
            {
                stringstream tmp;
                tmp << hex << (int)message.at(i);

                if(tmp.str().length()>2)
                {
                    stream<<tmp.str().substr( tmp.str().length() - 2 );
                }
                else if(tmp.str().length()==1)
                {
                    stream<<"0"+tmp.str();
                }
                else
                {
                    stream<<tmp.str();
                }

            }
            
            
            message = stream.str();
            
            
            //Add who the message is from and what time it was sent to the front
            //of the message. This is seperated from the encrypted message by 
            //a ':' character
            message = "From " + userName + " at Unix time stamp " + to_string(time(NULL)) + ":" + message + '\n';
            outFile << message;

            // cout<<message<<endl;

            cout<<"Message sent."<<endl;
        }
        else
        {
            cout<<"User name being sent to not found."<<endl;
        }
        
    }
    else
    {
        cout<<"Error loging in."<<endl;
    }
    
    //Blank out the password in memory
    blankOutPassword(&password);
    
    return 0;
   
   

}


#include <iostream>
#include <string>
#include <fstream>
#include "helperFunctions.hpp"
using namespace std;

int main() {
   
    cout << "Content-type: application/json" << endl;
    cout << endl;
    
    //Get the username and password from the post request
    string userName, password;
    getline(cin, userName);
    getline(cin, password);
    
    //Detect newline charactes
    if(userName.find('\n') != string::npos || 
        password.find('\n') != string::npos)
    {
        cout<<"Username and password cannot contian return."<<endl;
    }

    
    //Hash the password
    long unsigned int hashedPassword = myHash(userName, password);
    
    //Open the file
    fstream file;
    
    file.open("./dat/Users");
    
    if(!file.is_open())
    {
        cout<<"Error"<<endl;
        return -1;
    }
    

    //Loop through all the user names and make sure the new username is unique
    bool userNameUnique = true;
    //Username file is formated that one line userName next line password
    while(!file.eof())
    {
        string userNameLine;
        getline(file, userNameLine);
        string passwordLine;
        getline(file, passwordLine);
        
        
        if(userName == userNameLine)
        {
            userNameUnique = false;
            break;
        }
        
    }
    
    //Since the end of file bit may have been set by the loop clear all error 
    //bits. Otherwise you may not be able to write to the file.
    file.clear();
    
    if(userNameUnique)
    {
        file<<userName<<endl;
        file<<hashedPassword<<endl;
        
        //Make a new file to hold the users messages
        
        ofstream newFile;
        newFile.open("./dat/msg/" + userName);
        newFile.close();
        
        
        cout<< "Created user  " << userName << endl;
    }
    else
    {
        cout<<"Username is already in use."<<endl;
    }
    
    
    file.close();

    return 0;
   
   

}
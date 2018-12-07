#include <iostream>
#include <string>
#include <fstream>
#include "helperFunctions.hpp"
using namespace std;

/*

    This program prints out a list of users who are registered on the server
    This program needs no additional input from the user beyond calling the
    end point. 

*/

int main() {
   
    cout << "Content-type: text/plain" << endl;
    cout << endl;
    
    //Open the file
    ifstream file;
    
    file.open("./dat/Users");
    
    if(!file.is_open())
    {
        cout<<"Error"<<endl;
        return -1;
    }
    

    //Username file is formated that one line userName next line password
    while(!file.eof())
    {
        string userNameLine;
        getline(file, userNameLine);
        
        //The password line is not used but still needs to be read so that
        //we move down a line in the file
        string passwordLine;
        getline(file, passwordLine);
        
        cout<<userNameLine<<endl;
        
    }
    
    file.close();
    
    return 0;
   
   

}
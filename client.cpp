#include <iostream>
#include <string>
#include "curl/curl.h"
#include "helperFunctions.hpp"
#include <fstream>

using namespace std;

//These functions are used for calling the cgi endpoints
bool addUser();
bool sendMsg();
bool printUsers();
bool readMsgs();
bool ckeckMsgs();

string baseURL;

 
int main()
{
  
  ifstream baseURLFile;
  baseURLFile.open("baseURL");
  getline(baseURLFile, baseURL);
  baseURLFile.close();
  
  curl_global_init(CURL_GLOBAL_ALL);
  
  string command;
  
  cout<<"Type 'help' to see command options."<<endl;
  
  //Used to get the return status of each endpoint
  bool OK;
  
  while(command != "exit")
  {
    cout<<"What do you want to do?"<<endl;
    
    cin>>command;
    
    
    //Each of these if statments is used for handling specific user commands
    if(command == "help")
    {
      cout<<"Command options are:"<<endl;
      cout<<"    addUser"<<endl;
      cout<<"    send"<<endl;
      cout<<"    read"<<endl;
      cout<<"    printUsers"<<endl;
      cout<<"    checkMsgs"<<endl;
      cout<<"    exit"<<endl;
    }
    else if(command == "addUser")
    {
       OK = addUser();
      
      if(!OK)
      {
        cout<<"Problem running command addUser."<<endl;
      }
      
    }
    else if(command == "send")
    {
      OK = sendMsg();
      
      if(!OK)
      {
        cout<<"Problem running command send."<<endl;
      }
    }
    else if(command == "printUsers")
    {
      OK = printUsers();
      
      if(!OK)
      {
        cout<<"Problem running command printUsers."<<endl;
      }
    }
    else if(command == "read")
    {
      OK = readMsgs();
      
      if(!OK)
      {
        cout<<"Problem running command read."<<endl;
      }
    }
    else if(command == "checkMsgs")
    {
      OK = ckeckMsgs();
      
      if(!OK)
      {
        cout<<"Problem running command checkMsgs."<<endl;
      }
    }
    
  }
  
  
  curl_global_cleanup();
  
  
}



//This function adds a new user to the email server
bool addUser()
{
  
  //These strings hold the user entered data
  string userName, password, data;
  
  //Get user input
  cout<<"Enter a new username: "<<endl;
  cin>>userName;
  cout<<"Enter your password: "<<endl;
  cin>>password;
  
  //Format the data into a single string seperated by newline characters
  data = userName + "\n" + password;
  
  //Setup curl
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  
  //Check if curl is OK
  if(curl)
  {
    //Point the the end point
    curl_easy_setopt(curl, CURLOPT_URL, (baseURL+"addUser.cgi").c_str());
    
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());    
    
    //This causes the response to be printed to the terminal
    res = curl_easy_perform(curl);
  }
  else
  {
    return false;
  }
  
  
  curl_easy_cleanup(curl);
  
  return true;
  
  
}



//This function sends a message to a particular user on the email server
bool sendMsg()
{
  
  //These strings hold the user entered data
  string userName, password, message, receiveUser, data, key;
  
  //Get all needed data from the user
  cout<<"Enter your username: "<<endl;
  cin>>userName;
  cout<<"Enter your password: "<<endl;
  cin>>password;
  cout<<"Enter who you want to send to: "<<endl;
  cin>>receiveUser;
  cout<<"Enter your key (must be a single word): "<<endl;
  cin>>key;
  cout<<"Enter your message: "<<endl;
  
  //This is needed to get rid of the newline after the the cin that is still in the buffer
  //If you don't do this getline will end immediatly without letting you type anything.
  cin.ignore(256,'\n');
  getline(cin, message);
  
  //Format the data into a single string seperated by newline characters
  data = userName + '\n' + password + '\n' + receiveUser + '\n' + key + '\n' + message;
  
  //Setup curl
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  
  //If curl was setup correctly send the POST request and wait for a response
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, (baseURL+"receiveMessage.cgi").c_str());
    
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());    
    
    res = curl_easy_perform(curl);
    
  }
  else
  {
    return false;
  }
  
  
  curl_easy_cleanup(curl);
  
  return true;
}



//This function sends the request to show a list of registered users
//This one does not need user input
bool printUsers()
{
  
  //Setup curl
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  
  //If curl was setup correctly send the POST request and wait for a response
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, (baseURL+"printUsers.cgi").c_str());
    
    res = curl_easy_perform(curl);
    
  }
  else
  {
    return false;
  }
  
  
  curl_easy_cleanup(curl);
  
  return true;
}



//This functions allows the user to read a message that has been sent to them
bool readMsgs()
{
  
  //These strings hold the user entered data
  string userName, password, key, msgNumber, data, returnVal;
  
  //Get all needed data from the user
  cout<<"Enter your username: "<<endl;
  cin>>userName;
  cout<<"Enter your password: "<<endl;
  cin>>password;
  cout<<"Enter your key (must be a single word): "<<endl;
  cin>>key;
  cout<<"Enter the number of the message you want to read: "<<endl;
  cin>>msgNumber;
  cout.clear();


  //Combine all the user input into one data string
  data = userName + '\n' + password + '\n' + key + '\n' + msgNumber + '\n';
  
  
  //Setup curl
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  
  //If curl was setup correctly send the POST request and wait for a response
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, (baseURL+"returnMessages.cgi").c_str());
    
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());  

    res = curl_easy_perform(curl);
    
  }
  else
  {
    return false;
  }
  
  curl_easy_cleanup(curl);
  
  return true;
  
}



//Get a list of who has sent messages and when they sent them
bool ckeckMsgs()
{
  
  //These strings hold the user entered data
  string userName, password, data;
  
  //Get all needed data from the user
  cout<<"Enter your username: "<<endl;
  cin>>userName;
  cout<<"Enter your password: "<<endl;
  cin>>password;
  cout.clear();

  //Combine all user input into one string
  data = userName + '\n' + password + '\n';
  
  //Setup curl
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  
  //If curl was setup correctly send the POST request and wait for a response
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, (baseURL+"checkMessages.cgi").c_str());
    
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());  

    res = curl_easy_perform(curl);
    
  }
  else
  {
    return false;
  }
  
  
  curl_easy_cleanup(curl);
  
  return true;
  
}

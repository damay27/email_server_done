ARGS = -Wall -Wextra -std=c++11

all: client addUser receiveMessage printUsers returnMessages checkMessages





client: client.o helperFunctions.o
	#The client uses curl so don't forget the -l
	g++ client.o helperFunctions.o $(ARGS) -o client -l curl -l sodium

addUser: addUser.o helperFunctions.o
	g++ addUser.o helperFunctions.o $(ARGS) -o addUser.cgi -l sodium
	chmod +x addUser.cgi

receiveMessage: receiveMessage.o helperFunctions.o
	g++ receiveMessage.o helperFunctions.o $(ARGS) -o receiveMessage.cgi -l sodium
	chmod +x receiveMessage.cgi
	
printUsers: printUsers.o
	g++ printUsers.o $(ARGS) -o printUsers.cgi
	chmod +x printUsers.cgi
	
returnMessages: returnMessages.o helperFunctions.o
	g++ returnMessages.o helperFunctions.o $(ARGS) -o returnMessages.cgi -l sodium
	chmod +x returnMessages.cgi
	
checkMessages: checkMessages.o
	g++ checkMessages.o helperFunctions.o  $(ARGS) -o checkMessages.cgi -l sodium
	chmod +x checkMessages.cgi





client.o: client.cpp
	g++ -c client.cpp $(ARGS)

addUser.o: addUser.cpp
	g++ -c addUser.cpp $(ARGS)
	
receiveMessage.o: receiveMessage.cpp
	g++ -c receiveMessage.cpp $(ARGS)
	
helperFunctions.o: helperFunctions.cpp
	g++ -c helperFunctions.cpp $(ARGS)
	
printUsers.o: printUsers.cpp
	g++ -c printUsers.cpp $(ARGS)
	
returnMessages.o: returnMessages.cpp
	g++ -c returnMessages.cpp $(ARGS)
	
checkMessages.o: checkMessages.cpp
	g++ -c checkMessages.cpp $(ARGS)	






clean:
	rm client.o client helperFunctions.o receiveMessage.o receiveMessage.cgi \
	addUser.o addUser.cgi printUsers.cgi printUsers.o returnMessages.o returnMessages.cgi \
	checkMessages.cgi checkMessages.o
	
	
folders:
	mkdir dat
	mkdir dat/msg

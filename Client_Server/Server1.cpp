#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{

 if(argc != 2)
    {
        cerr << "Error in parsing arguments" << endl;
        exit(0);
    }

     int port = atoi(argv[1]);
    
   
     char msg[1500];

    sockaddr_in servAddr;


    servAddr.sin_family = AF_INET;

    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

   servAddr.sin_port = htons(port);
 

    int serverSd = socket(AF_INET, SOCK_STREAM, 0);

    if(serverSd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }

    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, 
        sizeof(servAddr));
   

 if(bindStatus < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }

    cout << "Waiting for a client to connect..." << endl;
    

    listen(serverSd, 5);


    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

   
    int newSd = accept(serverSd, (sockaddr *)&client, &clientSize);

   
if(newSd < 0)
    {
        cerr << "Error accepting request from client!" << endl;
        exit(1);
    }


    cout << "Connected with client!" << endl;

 while(1)
    {
 
        cout << "Awaiting client response..." << endl;

         memset(&msg, 0, sizeof(msg)); 

        recv(newSd, (char*)&msg, sizeof(msg), 0);

        if(!strcmp(msg, "exit"))
        {
            cout << "Client has quit the session" << endl;
            break;
        }
  
        cout << "Message from Client: " << msg << endl;
        cout << "Server, now is your turn : >";


        string data;
        getline(cin, data); 

        memset(&msg, 0, sizeof(msg)); 

        strcpy(msg, data.c_str());

       
        send(newSd, (char*)&msg, strlen(msg), 0);
     
    }
     
    close(newSd);
    close(serverSd);

    return 0;   
}

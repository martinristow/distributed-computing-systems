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

int main(int argc, char *argv[]){

char msg[1500]; 


if(argc != 3)
{
cerr<<"error in the number of parsed arguments"<<endl;
exit(0);
}

unsigned long int serverIP=atoi(argv[1]); 
int portNb=atoi(argv[2]);


sockaddr_in serverAddress;
serverAddress.sin_family=AF_INET;
serverAddress.sin_port=htons(portNb);
serverAddress.sin_addr.s_addr=htonl(serverIP);


int clientSd=socket(AF_INET,SOCK_STREAM, 0);


int status=connect(clientSd, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr));

 if(status < 0)
    {
        cout<<"Error connecting to socket!"<<endl;
        exit(0);
    }

    cout << "Connected to the server!" << endl;

    while(1)
    {
        cout << "Client, now is your turn : >";
       
        string data;
        getline(cin, data);
     
        memset(&msg, 0, sizeof(msg));
       
        strcpy(msg, data.c_str());
       
        send(clientSd, (char*)&msg, strlen(msg), 0);
        cout << "Awaiting server response..." << endl;
      
        memset(&msg, 0, sizeof(msg));
       
        recv(clientSd, (char*)&msg, sizeof(msg), 0);
      
        if(!strcmp(msg, "exit"))
        {
            cout << "Server has quit the session" << endl;
            break;
        }
        cout << "Message from Server: " << msg << endl;
    }
        
    close(clientSd);
return 0;
}

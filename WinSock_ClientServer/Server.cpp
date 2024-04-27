// Server.cpp : Defines the entry point for the console application.
//

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
using namespace std;

int main(void)
{
	//WinSock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 2);
	if (WSAStartup(DllVersion, &wsaData) != 0) //If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	{
		MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	SOCKADDR_IN addr; //Address that we will bind our listening socket to
	int addrlen = sizeof(addr); //length of the address (required for accept call)
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Broadcast locally
	addr.sin_port = htons(53555); //Port
	addr.sin_family = AF_INET; //IPv4 Socket

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); //Create socket to listen for new connections
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //Bind the address to the socket
	listen(sListen, SOMAXCONN); //Places sListen socket in a state in which it is listening for an incoming connection. Note:SOMAXCONN = Socket Oustanding Max Connections

	SOCKET newConnection; //Socket to hold the client's connection
	newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); //Accept a new connection
	if (newConnection == 0) //If accepting the client connection failed
	{
		cout << "Failed to accept the client's connection." << endl;
	}
	else //If client connection properly accepted
	{
		cout << "Klientot e povrzan!" << endl;
		char PorakaSK[256] = "Poraka od serverot do klientot"; //Create buffer with message of the day
		char PorakaKS[256];
		send(newConnection, PorakaSK, sizeof(PorakaSK), NULL); //Send MOTD buffer
		recv(newConnection, PorakaKS, sizeof(PorakaKS), NULL); //Receive Message of the Day buffer into MOTD array
		cout << "PorakaKS:" << PorakaKS << endl;
	}
	closesocket(sListen);
	closesocket(newConnection);
	system("pause");
	return 0;
}

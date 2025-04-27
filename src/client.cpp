#include <iostream>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;


void winsock_init(){
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
}

void winsock_cleanup(){
    WSACleanup();
}

void Create_Socket(SOCKET* client_socket){
    *client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void connect_socket(SOCKET* client_socket, string ip_address, int port){
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(ip_address.c_str());
    server_address.sin_port = htons(port);
    if(connect(*client_socket, (struct sockaddr*)&server_address,sizeof(server_address)) == SOCKET_ERROR){
	    cout << "Error:" << WSAGetLastError() << "\n" << "Error in connecting to server \n";
        closesocket(*client_socket);
        return;
    }
    else{
	    cout << "Socket opened successfully " << '\n';
    }
}

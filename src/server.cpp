#include <iostream>
#include <string>
#include <cstring>
#ifdef _WIN32
#include <winsock2.h>
typedef SOCKET socket_t;
#include <ws2tcpip.h>
#else
typedef int socket_t;

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <cstdint>
using namespace std;

void winsock_init() {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
}

void winsock_cleanup(){
#ifdef _WIN32
    WSACleanup();
#endif
}

void create_socket(socket_t* server_socket){
    *server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

}
int Bind_socket(socket_t* server_socket, int port, string& ip_address){
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    #ifdef _WIN32
    uint32_t bin_ip_address = static_cast<uint32_t>(inet_addr(ip_address.c_str()));
    server_address.sin_addr.s_addr = bin_ip_address;
    #else
    if (inet_pton(AF_INET, ip_address.c_str(), &server_address.sin_addr) <= 0) {
        cerr << "Invalid address\n";
        return 0;
    }
    #endif
    server_address.sin_port = htons(port);
    if(bind(*server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0){
	    return 0;
    }
    return 1;
}

void listen_socket(socket_t* server_socket, int max_connections){
    listen(*server_socket, max_connections);
}

void accept_socket(socket_t* server_socket, socket_t* client_socket){
    sockaddr_in client_address;
    socklen_t client_address_size = sizeof(client_address);
    *client_socket = accept(*server_socket, (struct sockaddr*)&client_address, &client_address_size);
}




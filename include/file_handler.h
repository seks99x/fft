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
#include <fstream>
using namespace std;

int open_file(string file_name);
void recv_file(string filename,socket_t* client_socket,bool is_binary);

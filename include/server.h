#include <string>
#include <cstring>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET socket_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef int socket_t;
#endif
#include <cstdint>
using namespace std;

void winsock_init();
void winsock_cleanup();
void create_socket(socket_t* server_socket);
void Bind_socket(socket_t* server_socket,int port,string& ip_address);
void listen_socket(socket_t* server_socket, int max_connections);
void accept_socket(socket_t* server_socket, socket_t* client_socket);

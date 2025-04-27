#include <winsock2.h>
#include <string>
#include <cstring>
using namespace std;

void winsock_init();
void winsock_cleanup();
void Create_Socket(SOCKET* client_socket);
void connect_socket(SOCKET* client_socket, string ip_address, int port);
	

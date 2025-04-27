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





int open_file(string file_name){
    ifstream file(file_name);
    return file.is_open();
}


void recv_file(string filename,socket_t* client_socket,bool is_binary){
	size_t bytesToWrite = 0;
	char buffer[4096];
	int totalReceived = 0;
 // Track total bytes received

	FILE* file = is_binary ? fopen(filename.c_str(), "wb") : fopen(filename.c_str(), "w");
	int file_len = 0;
	int recvlenbuffer_bytes = recv(*client_socket,(char*)&file_len,sizeof(file_len), 0);
	file_len = ntohl(file_len); // convert back from network byte order
	if (recvlenbuffer_bytes <= 0) {
		cerr << "Failed to receive file length\n";
		return;
	}
	if(file_len > 1000 * 1000 * 100) {
		cout << file_len << '\n';
		cerr << "File too large, Cannot receive it\n";
		return;
	}
	
	while((bytesToWrite = recv(*client_socket, buffer, sizeof(buffer), 0)) > 0){
		if (bytesToWrite < 0) {
			cerr << "Error in receiving file \n";
			fclose(file);
			return;
		}
		fwrite(buffer, 1, bytesToWrite, file);
		totalReceived += bytesToWrite; // Update total received bytes

		int percentage = (totalReceived * 100) / file_len;
		cout << "Progress: " << percentage << "%\r" << flush;
	}
	if (bytesToWrite == 0) {
        // Connection closed by client
        cout << "File transfer complete." << endl;
    }

    fclose(file);
	cout << "File size: " << file_len << '\n';
	cout << "File name: " << filename << '\n';
	cout << "File type: " << (is_binary ? "binary" : "text");

}






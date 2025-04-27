#include <iostream>
#include <string>
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
#include <regex>
#include <vector>
#include "../include/server.h"
#include "../include/file_handler.h"
#include <string>
using namespace std;

// Function to validate the IP address
bool isValidIP(const string& ip) {
    regex ipRegex(R"(^(\d{1,3}\.){3}\d{1,3}$)");
    return regex_match(ip, ipRegex);
}



string extract_filename(const std::string& filepath) {
    size_t pos = filepath.find_last_of("/\\");
    if (pos == std::string::npos) return filepath;
    return filepath.substr(pos + 1);
}


// Function to validate the port number
bool isValidPort(const string& port) {
    if (port.length() > 5) return false; // Max "65535" (5 chars)
    for (char c : port) if (!isdigit(c)) return false;

    int portNum = stoi(port);
    return portNum >= 1 && portNum <= 65535;
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Missing arguments ip/port\n";
        cout << "Usage: ./server <ip> <port>\n";
        return 0;
    }

    if (argc > 6) {
        cerr << "Too many arguments\n";
        return 0;
    }

    string ip_address = argv[1];
    string sport = argv[2];

    if (!isValidIP(ip_address) || !isValidPort(sport)) {
        cerr << "Invalid IP/Port\n";
        return 0;
    }

    socket_t server_socket = -1;
    int port = stoi(sport);
    winsock_init();
    create_socket(&server_socket);
    cout << "Creating socket........\n";

    if (server_socket < 0) {
        cerr << "Error in creating socket....\n";
        return 0;
    }

    cout << "Binding socket... \n";
    Bind_socket(&server_socket, port, ip_address);
    if (server_socket < 0) {
        cerr << "Error in binding socket...\n";
        return 0;
    }

    listen(server_socket, 10);
    cout << "Listening on " << ip_address << ":" << port << '\n';

    socket_t client_socket = -1;
    accept_socket(&server_socket, &client_socket);


	bool is_bin = false;
	char flag = 0;
	recv(client_socket, &flag, 1, 0);
    if (flag == 'Y') {
        is_bin = true;
    }

	int file_name_len = 0;
	if (recv(client_socket, (char*)&file_name_len, sizeof(file_name_len), 0) <= 0) {
		cout << file_name_len << '\n';
		cerr << "Failed to receive filename length\n";
		return 1;
	}
	cout << file_name_len; // convert back from network byte order
  // Increased buffer size to 32

    std::vector<char> filename(file_name_len + 1); // +1 for null termination

	if (recv(client_socket, filename.data(), file_name_len, 0) <= 0) {
		cerr << "Failed to receive filename\n";
		return 1;
	}
	filename[file_name_len] = '\0';
	// Null terminate the filename
        string splited_filename = extract_filename(filename.data());
    // Receive the file data into the buffer
	recv_file(splited_filename, &client_socket, is_bin);

	#ifdef _WIN32
    winsock_cleanup();
	#endif

    return 0;
}

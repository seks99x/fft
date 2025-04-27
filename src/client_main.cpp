#include <iostream>
#include <string>
#include <regex>
#include "../include/client.h"
#include "../include/client_file_handler.h"
#include <winsock2.h>
using namespace std;


bool isValidIP(const string& ip) {
    regex ipRegex(R"(^(\d{1,3}\.){3}\d{1,3}$)");
    return regex_match(ip, ipRegex);
}


bool isValidPort(const string& port) {
    if (port.length() > 5) return false; // Max "65535" (5 chars)
    for (char c : port) if (!isdigit(c)) return false;

    int portNum = stoi(port);
    return portNum >= 1 && portNum <= 65535;
}


int main(int argc,char* argv[]){
    if(argc != 4){
        cout << "Must include all essential flags\nUsage: ./fft {ip} {port} {file}";
        return 0;
    }
    string ip = argv[1];
    int port = stoi(argv[2]);
    string filename = argv[3];
    int length = 0;
    if(!isValidIP(ip)){
        cerr << "Error: Invalid IP address\n";
        return 1;
    }
    if(!isValidPort(argv[2])){
        cerr << "Error: Invalid port number\n";
        return 1;
    }
    if(!open_file(filename)){
        cerr << "Error: Can't open the file\n";
        return 1;
    }
    winsock_init();
    SOCKET client_socket = INVALID_SOCKET;
    Create_Socket(&client_socket);
    if(client_socket == INVALID_SOCKET){
        cout << "Error: Can't create socket\n";
        return 1;
    }
    connect_socket(&client_socket, ip, port);
    if(client_socket == INVALID_SOCKET){
        cout << "Error: Can't connect to server\n";
        return 1;
    }
    
    

    send(client_socket,(is_binary_file(filename) ? "Y":"N"), 1, 0);
    int file_name_len = filename.length();
    send(client_socket, (char*)&file_name_len, sizeof(file_name_len), 0);
    
    send(client_socket, filename.c_str(), filename.length(), 0);
    if(open_file(filename) == 0){
         cout << "File does not exist \n";
         return 1;
    }


    send_file(filename, &client_socket, is_binary_file(filename));
             
    closesocket(client_socket);
    WSACleanup();
    return 0;


    }




    






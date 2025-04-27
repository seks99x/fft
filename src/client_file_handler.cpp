#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <winsock2.h>
using namespace std;

int open_file(string file_name){
    ifstream file(file_name);
    return file.is_open();
}

bool is_binary_file(string file_name) {
    ifstream file(file_name, std::ios::binary); 
    char ch;
    int byte_count = 0;
    int non_printable_count = 0;
    
    // Read up to 1024 bytes
    while (file.get(ch) && byte_count < 1024) {
        if (!std::isprint(static_cast<unsigned char>(ch)) && ch != '\n' && ch != '\r' && ch != '\t') {
            non_printable_count++;
        }
        byte_count++;
    }
    return (non_printable_count > byte_count * 0.3);
}

void send_file(string file_name,SOCKET* client_socket,bool is_binary) {
        size_t readbytes;
        char buffer[4096];
        int length = 0;
        FILE* file = is_binary ? fopen(file_name.c_str(), "rb") : fopen(file_name.c_str(), "r");
        if (file == nullptr) {
            cerr << "Failed to open file: " << file_name << "\n";
            return;
        }
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);

        if(length > 100*1000*1000){
            cerr << "File size is too large, Cant read file \n";
            return;
        }
        if(length == 0){
            cerr << "File is empty \n";
            return;
        }
        if(length < 0){
            cerr << "Error in reading file \n";
            return;
        }
        length = htonl(length);
        send(*client_socket, (char*)&length, sizeof(length), 0);

        while((readbytes = fread(buffer, 1, sizeof(buffer), file)) > 0){
            if(send(*client_socket, buffer, readbytes, 0) != readbytes){
                cerr << "Error in sending file \n";
                fclose(file);
                return;
            }
        }
        fclose(file);
        cout << "File sent successfully \n";
}







    



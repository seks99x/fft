#include <string>
#include <cstring>
#include <fstream>
using namespace std;

int open_file(string file_name);
bool is_binary_file(string file_name);
void send_file(string file_name,SOCKET* client_socket,bool is_binary);


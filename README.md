# fft
A fast file transfer application built using C++ and sockets, supporting both server and client functionalities for quick and efficient file transmission over a network 
i made this because i always face issues when i try to transfer a file from windows to my linux box , specially in CTFS where i try to open a smb share and make a whole big process,
which could be dangerous sometimes if you try to close the server or for example you make a GUEST LOGIN ENABLED thats why i created this lightweight console application

USAGE:

./server 127.0.0.1 443

./client 127.0.0.1 443 /path/to/your/file.txt










---

### Key Points:

- **Installation**: Explains what dependencies are required and provides platform-specific build instructions.
- **Usage**: Describes how to start the server and send files using the client, with example commands.
- **Contributing**: Encourages others to contribute to the project.
- **License**: It's always a good idea to include licensing information (you can specify MIT or whichever license you prefer).

### Additional Notes:
- You can replace `127.0.0.1` with your server’s local or external IP in the usage examples.
- Update the repository URL with your actual GitHub link.

This layout gives users all the necessary information in an easy-to-read format. You can further improve it based on additional features or instructions you might want to include!

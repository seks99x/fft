# fft
A fast file transfer application built using C++ and sockets, supporting both server and client functionalities for quick and efficient file transmission over a network 
i made this because i always face issues when i try to transfer a file from windows to my linux box , specially in CTFS where i try to open a smb share and make a whole big process,
which could be dangerous sometimes if you try to close the server or for example you make a GUEST LOGIN ENABLED thats why i created this lightweight console application








---

### Key Points:

- **Installation**: open your terminal and type: git clone **https://github.com/seks99x/fft.git** , you can compile it through the make or used the compiled versions in the releases folder
- **Usage**:
-       **compiled**:     ./server 127.0.0.1 443
                          ./client 127.0.0.1 443 /path/to/your/file.txt
        **non-compiled**:
                               Run **make** to compile both the server and client executables.

                               To clean up the generated executables, use **make clean**.

         

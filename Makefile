# Directories
SRC_DIR = src
INCLUDE_DIR = include

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -I$(INCLUDE_DIR)

# Source files
SERVER_SRC = $(SRC_DIR)/server.cpp $(SRC_DIR)/file_handler.cpp $(SRC_DIR)/main.cpp
CLIENT_SRC = $(SRC_DIR)/client.cpp $(SRC_DIR)/client_file_handler.cpp $(SRC_DIR)/client_main.cpp

# Output executables
SERVER_EXEC = server.exe
CLIENT_EXEC = client.exe

# Targets
all: $(SERVER_EXEC) $(CLIENT_EXEC)

$(SERVER_EXEC): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) $(SERVER_SRC) -o $(SERVER_EXEC)

$(CLIENT_EXEC): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) $(CLIENT_SRC) -o $(CLIENT_EXEC)

clean:
	rm -f $(SERVER_EXEC) $(CLIENT_EXEC)

.PHONY: all clean

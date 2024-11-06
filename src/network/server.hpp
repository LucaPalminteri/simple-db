#pragma once
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <vector>

using namespace std;

class DatabaseServer {
private:
    int server_fd;
    int port;
    bool running;
    vector<thread> client_threads;

    void handleClient(int client_socket);
    string processQuery(const string& query);
    void logMessage(const string& message, bool isError = false);
    bool processExit(const string& query); // Check for exit/quit commands

public:
    DatabaseServer(int port);
    ~DatabaseServer();

    void start();
    void stop();
};

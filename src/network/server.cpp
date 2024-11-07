#include "server.hpp"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

DatabaseServer::DatabaseServer(int port) : port(port), running(false) {}

DatabaseServer::~DatabaseServer() {
    stop();
}

void DatabaseServer::start() {
    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        throw runtime_error("Socket creation failed");
    }

    // Set socket options
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        throw runtime_error("setsockopt failed");
    }

    // Bind socket
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Use :: to specify global namespace bind function, not std::bind
    if (::bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        throw runtime_error("Bind failed");
    }

    // Listen for connections
    if (::listen(server_fd, 3) < 0) {
        throw runtime_error("Listen failed");
    }

    running = true;
    cout << "Server listening on port " << port << endl;

    // Accept connections
    while (running) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_socket = ::accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            if (running) {
                cerr << "Accept failed" << endl;
            }
            continue;
        }

        // Get client IP address
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
        cout << "New connection from " << client_ip << endl;

        // Create new thread for client
        client_threads.emplace_back(&DatabaseServer::handleClient, this, client_socket);
    }
}

void DatabaseServer::stop() {
    logMessage("Shutting down server...");
    running = false;
    ::close(server_fd);

    // for (auto& thread : client_threads) {
    //     if (thread.joinable()) {
    //         thread.join();
    //     }
    // }
    client_threads.clear();
    logMessage("Server shutdown complete");
}

void DatabaseServer::handleClient(int client_socket) {
    char buffer[1024] = {0};

    try {
        while (running) {
            memset(buffer, 0, sizeof(buffer));
            ssize_t valread = ::read(client_socket, buffer, 1024);

            if (valread <= 0) {
                break;
            }

            string query(buffer);
            query = query.substr(0, query.find('\n')); // Remove newline
            logMessage("Received query: " + query);

            if (processExit(query)) {
                logMessage("Client requested disconnect");
                break;
            }

            string response = processQuery(query);
            ::send(client_socket, response.c_str(), response.length(), 0);
        }
    }
    catch (const exception& e) {
        logMessage("Error handling client: " + string(e.what()), true);
    }

    ::close(client_socket);
    logMessage("Client disconnected");
}

string DatabaseServer::processQuery(const string& query) {
    // Basic query processor
    string lowerQuery = query;
    transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    // Remove extra spaces
    lowerQuery.erase(0, lowerQuery.find_first_not_of(" "));
    lowerQuery.erase(lowerQuery.find_last_not_of(" ") + 1);

    string response;

    if (lowerQuery.empty()) {
        response = "Empty query";
    }
    // Handle SELECT
    else if (lowerQuery.substr(0, 6) == "select") {
        response = "SELECT operation not implemented yet\n";
    }
    // Handle CREATE
    else if (lowerQuery.substr(0, 6) == "create") {
        response = "CREATE operation not implemented yet\n";
    }
    // Handle INSERT
    else if (lowerQuery.substr(0, 6) == "insert") {
        response = "INSERT operation not implemented yet\n";
    }
    // Handle simple commands
    else if (lowerQuery == "help") {
        response = "Available commands:\n"
                  "  SELECT - Query data\n"
                  "  CREATE - Create table\n"
                  "  INSERT - Insert data\n"
                  "  HELP   - Show this help\n"
                  "  \\q     - Quit\n";
    }
    else {
        response = "Unknown command. Type 'help' for available commands.\n";
    }

    logMessage("Sending response: " + response);
    return response;
}

void DatabaseServer::logMessage(const string& message, bool isError) {
    auto& stream = isError ? cerr : cout;
    stream << "[Server] " << message << endl;
}

bool DatabaseServer::processExit(const string& query) {
    string lowerQuery = query;
    transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
    return (lowerQuery == "exit" || lowerQuery == "quit" || lowerQuery == "\\q");
}

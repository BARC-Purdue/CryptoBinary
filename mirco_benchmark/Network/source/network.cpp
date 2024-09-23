#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Server details
    const char* server_ip = "93.184.216.34"; // Example IP for example.com
    const int server_port = 80;

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed!" << std::endl;
        return 1;
    }

    // Server address setup
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_address.sin_addr);

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Connection to server failed!" << std::endl;
        close(sock);
        return 1;
    }

    // Prepare the HTTP GET request
    std::string request = "GET / HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";

    // Send the request
    if (send(sock, request.c_str(), request.size(), 0) < 0) {
        std::cerr << "Failed to send request!" << std::endl;
        close(sock);
        return 1;
    }

    // Buffer to hold the response
    char buffer[4096];
    std::string response;

    // Receive the response
    int bytes_received;
    while ((bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        response += buffer;
    }

    if (bytes_received < 0) {
        std::cerr << "Error while receiving response!" << std::endl;
    } else {
        // Print the response
        std::cout << response << std::endl;
    }

    // Close the socket
    close(sock);

    return 0;
}

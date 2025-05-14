#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
  // 1. Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
      std::cerr << "Socket creation failed!\n";
      return 1;
    }
  // 2. Define server address
    struct sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Convert port number to network byte order
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost IP
  // 3. Connect to the server
    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
      std::cerr << "Connection to server failed.\n";
      close(sockfd);
      return 1;
    }
  // 4. Data to send
    const char* message = "Hello from C++ client!";
  // 5. Use send() to send the message
    ssize_t bytesSent = send(sockfd, message, strlen(message), 0);
    if (bytesSent < 0) {
      std::cerr << "Failed to send message.\n";
    }
    else {
      std::cout << "Sent " << bytesSent << " bytes: " << message << std::endl;
    }
  // 6. Close the socket
    close(sockfd);
    return 0;
}
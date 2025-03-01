#include "mweb/network.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

namespace mywebserver
{
  TcpConnection::TcpConnection(int socketFd)
      : fd_(socketFd)
  {}

  TcpConnection::~TcpConnection()
  {
    if (fd_ >= 0)
      close(fd_);
  }

  std::string TcpConnection::readData()
  {
    char buffer[4096];

    memset(buffer, 0, sizeof(buffer));
    ssize_t bytes = ::read(fd_, buffer, sizeof(buffer));
    
    if (bytes <= 0)
      return std::string();

    return std::string(buffer, bytes);
  }

  void TcpConnection::sendData(const std::string& data)
  {
    ::send(fd_, data.c_str(), data.size(), 0);
  }

  NetworkListener::NetworkListener()
      : serverFd_(-1)
  {}

  NetworkListener::~NetworkListener()
  {
    if (serverFd_ >= 0)
      close(serverFd_);
  }

  bool NetworkListener::open(int port)
  {
    serverFd_ = ::socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd_ < 0)
      {
        std::cerr << "Error creating socket\n";
        return false;
      }

    int opt = 1;
    if (setsockopt(serverFd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
      {
        std::cerr << "Error setsockopt\n";
        return false;
      }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    memset(&(serverAddr.sin_zero), '\0', 8);

    if (bind(serverFd_, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
      {
        std::cerr << "Error bind\n";
        return false;
      }

    if (listen(serverFd_, 10) < 0)
      {
        std::cerr << "Error listen\n";
        return false;
      }

    return true;
  }

  int NetworkListener::acceptConnection() {
      sockaddr_in clientAddr;
      socklen_t clientSize = sizeof(clientAddr);
      int clientFd = accept(serverFd_, (struct sockaddr*)&clientAddr, &clientSize);
      if (clientFd < 0) {
          return -1;
      }
      return clientFd;
  }
}

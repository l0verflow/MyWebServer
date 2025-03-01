#ifndef MYWEBSERVER_NETWORK_HPP
#define MYWEBSERVER_NETWORK_HPP

#include <string>

namespace mywebserver
{
  class TcpConnection
  {
  public:
    TcpConnection(int socketFd);
    ~TcpConnection();

    std::string readData();

    void sendData(const std::string& data);

  private:
      int fd_;
  };

  class NetworkListener
  {
  public:
    NetworkListener();
    ~NetworkListener();

    bool open(int port);

    int acceptConnection();

  private:
      int serverFd_;
  };
}

#endif

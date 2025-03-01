#include "mweb/core.hpp"

#include <iostream>

namespace mywebserver
{
  Server::Server()
  {
      // Construtor
  }

  Server::~Server()
  {
      // Destrutor
  }

  void Server::setPort(int port)
  {
    port_ = port;
  }

  Router& Server::router()
  {
    return router_;
  }

  void Server::run()
  {
    if (!listener_.open(port_))
      {
        std::cerr << "Failed to open door " << port_ << ".\n";
        return;
      }

    std::cout << "Server listening on the port " << port_ << "...\n";

    while (true)
      {
        int clientFd = listener_.acceptConnection();
        if (clientFd < 0)
          continue;

        TcpConnection conn(clientFd);

        std::string requestData = conn.readData();
        if (!requestData.empty())
          {
            HttpRequest request = parser_.parse(requestData);

            HttpResponse response = router_.route(request);

            conn.sendData(response.toString());
          }
      }
  }
}

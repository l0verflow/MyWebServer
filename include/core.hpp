#ifndef MYWEBSERVER_CORE_HPP
#define MYWEBSERVER_CORE_HPP

#include "network.hpp"
#include "http.hpp"
#include "router.hpp"

namespace mywebserver
{
  class Server
  {
    public:
      Server();
      ~Server();

      void setPort(int port);

      Router& router();

      void run();

    private:
      int port_{8080};
      NetworkListener listener_;
      Router router_;
      HttpParser parser_;
  };
}

#endif

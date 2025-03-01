#ifndef MYWEBSERVER_ROUTER_HPP
#define MYWEBSERVER_ROUTER_HPP

#include "http.hpp"
#include <functional>
#include <map>
#include <string>
#include <utility>

namespace mywebserver
{
  using HandlerFunc = std::function<HttpResponse(const HttpRequest&)>;

  class Router
  {
  public:
    void get(const std::string& path, HandlerFunc handler);

    void post(const std::string& path, HandlerFunc handler);

    HttpResponse route(const HttpRequest& req);

  private:
    std::map<std::pair<std::string, std::string>, HandlerFunc> routes_;
  };
}

#endif

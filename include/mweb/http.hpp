#ifndef MYWEBSERVER_HTTP_HPP
#define MYWEBSERVER_HTTP_HPP

#include <string>
#include <unordered_map>

namespace mywebserver
{
  class HttpRequest
  {
  public:
    std::string method;
    std::string path;
    std::unordered_map<std::string, std::string> headers;
    std::string body;
  };

  class HttpResponse
  {
  public:
    int statusCode{200};
    std::unordered_map<std::string, std::string> headers;
    std::string body;

    std::string toString() const;
  };

  class HttpParser
  {
  public:
    HttpRequest parse(const std::string& rawData);
  };
}

#endif

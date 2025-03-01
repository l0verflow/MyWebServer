#include "mweb/http.hpp"
#include <sstream>

namespace mywebserver
{
  std::string HttpResponse::toString() const
  {
    std::ostringstream oss;
    oss << "HTTP/1.1 " << statusCode << " OK\r\n";
    for (const auto& kv : headers)
      {
        oss << kv.first << ": " << kv.second << "\r\n";
      }
    oss << "\r\n";
    oss << body;

    return oss.str();
  }

  HttpRequest HttpParser::parse(const std::string& rawData)
  {
    HttpRequest request;

    std::istringstream iss(rawData);
    std::string line;
    if (std::getline(iss, line))
      {
        if (!line.empty() && line.back() == '\r')
          line.pop_back();

        std::istringstream lineStream(line);
        lineStream >> request.method;
        lineStream >> request.path;
      }

    while (std::getline(iss, line))
      {
        if (!line.empty() && line.back() == '\r') 
          {
            line.pop_back();
          }
        if (line.empty())
          {
            std::string body;
            while (std::getline(iss, line))
              body += line + "\n";

            request.body = body;
            break;
          }
        else
          {
            auto sepPos = line.find(":");
            if (sepPos != std::string::npos)
              {
                std::string key = line.substr(0, sepPos);
                std::string value = line.substr(sepPos + 1);

                if (!value.empty() && value.front() == ' ')
                  value.erase(0, 1);

                request.headers[key] = value;
              }
          }
      }

    return request;
  }
}

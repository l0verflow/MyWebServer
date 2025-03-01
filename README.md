![image](https://github.com/user-attachments/assets/42fa468c-2f90-4333-8136-2a572c5b4e1c)

MyWebServer
---
MyWebServer is an C++ library that provides a modular framework for building basic HTTP servers, emphasizing design clarity, separation of responsibilities, and extensibility.

The library follows a layered architecture:
```
+---------------+
|  Core Engine  |
+-------+-------+
        |
+-------v-------+
|     Router    |
+-------+-------+
        |
+-------v-------+
|  HTTP Parser  |
+-------+-------+
        |
+-------v-------+
|  Network I/O  |
+---------------+
```

Example
---
<img src="https://i.pinimg.com/736x/b3/ee/1c/b3ee1cadb45f6e56f9113eff4ffcde0f.jpg" width="25%" align="right" />

```cpp
#include "mweb/core.hpp"
#include "mweb/router.hpp"

#include <iostream>

int
main()
{
  mywebserver::Server server;
  server.setPort(8080);

  server.router().get("/ping", [](const mywebserver::HttpRequest& req)
    {
      mywebserver::HttpResponse resp;
      resp.statusCode = 200;
      resp.body = "pong";
      
      return resp;
    });

  server.run();

  return 0;
}
```
<br>

General flow:
```
Server.run()
listener_.acceptConnection()
TcpConnection::readData()
HttpParser::parse(...)
Router::route(...)
TcpConnection::sendData(...)
```

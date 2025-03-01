MyWebServer
---

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

General flow:

```
Server.run()
listener_.acceptConnection()
TcpConnection::readData()
HttpParser::parse(...)
Router::route(...)
TcpConnection::sendData(...)
```

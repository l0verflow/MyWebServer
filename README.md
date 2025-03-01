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
<img src="https://github.com/user-attachments/assets/1fa25087-b539-41af-b451-428cb3e801aa" width="25%" align="right" />

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

To do
---

- [ ] Request logging
- [ ] Static file serving
- [ ] Middleware support

#include "mweb/router.hpp"

namespace mywebserver
{
  void Router::get(const std::string& path, HandlerFunc handler)
  {
    routes_[{"GET", path}] = handler;
  }

  void Router::post(const std::string& path, HandlerFunc handler)
  {
    routes_[{"POST", path}] = handler;
  }

  HttpResponse Router::route(const HttpRequest& req)
  {
    auto it = routes_.find({req.method, req.path});
    if (it != routes_.end())
      return it->second(req);

    HttpResponse resp;
    resp.statusCode = 404;
    resp.body = "Route not found\n";
    return resp;
  }
}

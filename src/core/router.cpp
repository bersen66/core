#include "core/http/server/routes/router.hpp"

namespace http {
namespace server {

Router::RouterEasyInit::RouterEasyInit(Router *router_ptr)
    : router_ptr(router_ptr) {}

Router::RouterEasyInit &
Router::RouterEasyInit::operator()(METHOD method, const std::string &route,
                                   RouteHandler handler) {
  router_ptr->InsertRoute(method, route, handler);
  return *this;
}

Router::RouterEasyInit Router::SetupRoutes() {
  return Router::RouterEasyInit(this);
}

bool Router::Contains(const std::string &route) {
  for (const auto &[method, handlers_map] : method_map) {
    if (handlers_map.CanHandle(route)) {
      return true;
    }
  }
  return false;
}

const HandlersMap &Router::operator[](METHOD method) const {
  return method_map.at(method);
}

void Router::InsertRoute(METHOD method, const std::string &route,
                         RouteHandler handler) {
  method_map[method].Handle(route, handler);
}

boost::asio::awaitable<http::Response>
DefaultHandler(const http::Request &req) {
  Response result = {};
  result.result(boost::beast::http::status::ok);
  result.set(boost::beast::http::field::server, "BEOBOBA");
  result.set(boost::beast::http::field::content_type, "text/html");
  result.body() = "<h1>Hello, world!<\h1>";
  result.prepare_payload();
  co_return result;
}

RouterPtr DefaultRouter() {
  RouterPtr result = std::make_shared<Router>();
  result->SetupRoutes()(http::METHOD::GET, "/", DefaultHandler);
  return result;
}

} // namespace server
} // namespace http
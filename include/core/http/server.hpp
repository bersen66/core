#pragma once

#include "core/http/server/config.hpp"
#include "core/http/server/listener.hpp"
#include "core/http/server/routes/routes.hpp"
#include "core/http/server/session/session.hpp"
#include "core/task_processor.hpp"

namespace core
{
namespace http
{
namespace server
{

class Server
{
public:
  explicit Server(const ConfigPtr& config = http::server::DefaultConfig(),
                  const RouterPtr& router = http::server::EmptyRouter());

  Router::RouterEasyInit RegisterHandlers();

  void Serve();

private:
  //boost::asio::io_context io_context_;
  TaskProcessor session_processor_;
  Listener listener_;
  RouterPtr router_ptr_;
  ConfigPtr config_ptr_;
};

} // namespace server
} // namespace http
} // namespace core



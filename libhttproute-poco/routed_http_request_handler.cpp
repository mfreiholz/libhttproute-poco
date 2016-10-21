#include "routed_http_request_handler.h"
#include "request.h"

/****************** RoutedHTTPRequestHandler *********************************/

RoutedHTTPRequestHandler::RoutedHTTPRequestHandler(std::tuple<std::shared_ptr<HR_NS::Route>, HR_NS::RouteMatch> rm) :
	_rm(rm)
{}

RoutedHTTPRequestHandler::~RoutedHTTPRequestHandler()
{}

const HR_NS::RouteMatch&
RoutedHTTPRequestHandler::routeMatch() const
{
	return std::get<1>(_rm);
}

/****************** RoutedHTTPRequestHandler *********************************/

Poco::Net::HTTPRequestHandler*
RoutedHTTPRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
	const PocoHttpServerRequestImpl r(request);
	const auto t = _router.findFirstRoute(r);
	const auto& route = std::get<0>(t);
	if (route && route->object())
	{
		auto factory = static_cast<RoutedAbstractHandlerFactory*>(route->object());
		return factory->create(std::move(t));
	}
	return NULL;
}

HR_NS::Router&
RoutedHTTPRequestHandlerFactory::router()
{
	return _router;
}
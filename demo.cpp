#include "request.h"

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/ServerSocket.h"

#include "Poco/Util/ServerApplication.h"

#include "libhttproute/router.h"
#include "libhttproute/route.h"
#include "libhttproute/route_matcher.h"
#include "libhttproute/route_matcher_impl.h"

#include "libhttproute-poco/routed_http_request_handler.h"

#include <stdio.h>
#include <functional>

using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;


class DemoHelloHandler : public RoutedHTTPRequestHandler
{
public:
	DemoHelloHandler(std::tuple<std::shared_ptr<HR_NS::Route>, HR_NS::RouteMatch> t) :
		RoutedHTTPRequestHandler(t)
	{}
	virtual void handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
	{
		const auto& rm = routeMatch();

		resp.setStatus(HTTPResponse::HTTP_OK);
		resp.setContentType("text/plain");

		std::ostream& out = resp.send();
		out << "Hello ";
		out << rm.vars.at("name");
		out << "!";
		out.flush();
	}
};
ROUTED_HANDLER_FACTORY(DemoHelloHandler);


class FooHandler :
	public RoutedHTTPRequestHandler
{
public:
	FooHandler(std::tuple<std::shared_ptr<HR_NS::Route>, HR_NS::RouteMatch> t) :
		RoutedHTTPRequestHandler(t)
	{}
	virtual void handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
	{
		resp.setStatus(HTTPResponse::HTTP_OK);
		resp.setContentType("text/plain");

		std::ostream& out = resp.send();
		out << "FOO!";
		out.flush();
	}
};
ROUTED_HANDLER_FACTORY(FooHandler);


class BarHandler :
	public RoutedHTTPRequestHandler
{
public:
	BarHandler(std::tuple<std::shared_ptr<HR_NS::Route>, HR_NS::RouteMatch> t) :
		RoutedHTTPRequestHandler(t)
	{}
	virtual void handleRequest(HTTPServerRequest& req, HTTPServerResponse& resp)
	{
		resp.setStatus(HTTPResponse::HTTP_OK);
		resp.setContentType("text/plain");

		std::ostream& out = resp.send();
		out << "BAR!";
		out.flush();
	}
};
ROUTED_HANDLER_FACTORY(BarHandler);


class DemoRequestHandlerFactory : public RoutedHTTPRequestHandlerFactory
{
	DemoHelloHandlerFactory _routeHello;
	FooHandlerFactory _routeFoo;
	BarHandlerFactory _routeBar;

public:
	DemoRequestHandlerFactory()
	{
		router().newRoute()
		.byMatcher(std::make_shared<HR_NS::RoutePathMatcher>("/hello/{name:[a-z]+}/"))
		.withObject(&_routeHello);

		router().newRoute()
		.byMatcher(std::make_shared<HR_NS::RoutePathPrefixMatcher>("/foo"))
		.byMatcher(std::make_shared<HR_NS::RouteMethodMatcher>("GET"))
		.withObject(&_routeFoo);

		router().newRoute()
		.byMatcher(std::make_shared<HR_NS::RoutePathPrefixMatcher>("/bar"))
		.byMatcher(std::make_shared<HR_NS::RouteMethodMatcher>("GET"))
		.withObject(&_routeBar);
	}
};


class MyDemoApp : public ServerApplication
{
public:
	int main(const std::vector<std::string>&)
	{
		HTTPServer server(new DemoRequestHandlerFactory(), 1337);
		server.start();
		waitForTerminationRequest();
		server.stop();
		return 0;
	}
};


int main(int argc, char** argv)
{
	MyDemoApp app;
	return app.run(argc, argv);
}
#pragma once

#include <string>
#include <vector>
#include <memory>
#include <tuple>

#include "libhttproute/request.h"
#include "libhttproute/router.h"
#include "libhttproute/route.h"
#include "libhttproute/route_match.h"

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

/*
	Implements the `HR_NS::HttpServerRequest` for the use with the Poco::Net framework.
*/
class PocoHttpServerRequestImpl :
	public HR_NS::HttpServerRequest
{
public:
	PocoHttpServerRequestImpl(const Poco::Net::HTTPServerRequest& req);
	virtual ~PocoHttpServerRequestImpl();

	virtual std::string getMethod() const;
	virtual std::string getPath() const;
	virtual std::string getHost() const;
	virtual std::string getScheme() const;

	virtual bool hasHeader(const std::string& key) const;
	virtual std::string getHeader(const std::string& key, const std::string& defaultValue = std::string());
	virtual std::vector<std::string> getHeaders(const std::string& key) const;

	virtual bool hasParameter(const std::string& key) const;
	virtual std::string getParameter(const std::string& name, const std::string& defaultValue = std::string()) const;
	virtual std::vector<std::string> getParameters(const std::string& name) const;

private:
	const Poco::Net::HTTPServerRequest& _r;
};

/*
	RoutedHTTPRequestHandler merges the routing data with
	Poco's Net HTTP handler logic.

	Instead of sub-classing `Poco::Net::HTTPRequestHandler` directly,
	it is required to extend from this class and implement the
	`Poco::Net::HTTPRequestHandler::handleRequest(...)`.

	Matched variables by the `Router` can be accessed with a call to `routeMatch()`.
*/
class RoutedHTTPRequestHandler :
	public Poco::Net::HTTPRequestHandler
{
public:
	RoutedHTTPRequestHandler(std::tuple<std::shared_ptr<HR_NS::Route>, HR_NS::RouteMatch> t);
	virtual ~RoutedHTTPRequestHandler();

	const HR_NS::RouteMatch&
	routeMatch() const;

private:
	std::tuple<std::shared_ptr<HR_NS::Route>, HR_NS::RouteMatch> _rm;
};

/*
	Instead of sub-classing `Poco::Net::HTTPRequestHandlerFactory` directly,
	it is required to extend from this class and register all routes in the constructor.
*/
class RoutedHTTPRequestHandlerFactory :
	public Poco::Net::HTTPRequestHandlerFactory
{
public:
	virtual Poco::Net::HTTPRequestHandler*
	createRequestHandler(const Poco::Net::HTTPServerRequest& request);

	HR_NS::Router&
	router();

protected:
	HR_NS::Router _router;
};


class RoutedAbstractHandlerFactory
{
public:
	virtual Poco::Net::HTTPRequestHandler*
	create(std::tuple<std::shared_ptr<HR_NS::Route>, HR_NS::RouteMatch> t) const = 0;
};


#define ROUTED_HANDLER_FACTORY(clazz) \
	class clazz##Factory : \
		public RoutedAbstractHandlerFactory \
	{ \
	public: \
		virtual Poco::Net::HTTPRequestHandler* \
		create(std::tuple<std::shared_ptr<HR_NS::Route>, HR_NS::RouteMatch> t) const \
		{ \
			return new clazz(t); \
		} \
	}

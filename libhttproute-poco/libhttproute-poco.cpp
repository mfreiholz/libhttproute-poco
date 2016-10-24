#include "libhttproute-poco.h"

#include "Poco/URI.h"

/****************** PocoHttpServerRequestImpl ********************************/

PocoHttpServerRequestImpl::PocoHttpServerRequestImpl(const Poco::Net::HTTPServerRequest& req) :
	_r(req)
{}

PocoHttpServerRequestImpl::~PocoHttpServerRequestImpl()
{}

std::string
PocoHttpServerRequestImpl::getMethod() const
{
	return _r.getMethod();
}

std::string
PocoHttpServerRequestImpl::getPath() const
{
	auto uri = _r.getURI();
	size_t pos = std::string::npos;
	if ((pos = uri.find('?')) != std::string::npos)
	{
		uri = uri.substr(0, pos);
	}
	return uri;
}

std::string
PocoHttpServerRequestImpl::getHost() const
{
	return _r.getHost();
}

std::string
PocoHttpServerRequestImpl::getScheme() const
{
	return "http";
}

bool
PocoHttpServerRequestImpl::hasHeader(const std::string& key) const
{
	return _r.has(key);
}

std::string
PocoHttpServerRequestImpl::getHeader(const std::string& key, const std::string& defaultValue)
{
	auto itr = _r.find(key);
	if (itr != _r.end())
	{
		return itr->second;
	}
	return defaultValue;
}

std::vector<std::string>
PocoHttpServerRequestImpl::getHeaders(const std::string& key) const
{
	std::vector<std::string> v;
	for (auto itr = _r.find(key); itr != _r.end(); ++itr)
	{
		v.push_back(itr->second);
	}
	return std::move(v);
}

bool
PocoHttpServerRequestImpl::hasParameter(const std::string& key) const
{
	const Poco::URI uri(_r.getURI());
	const auto vec = uri.getQueryParameters();
	for (auto itr = vec.begin(); itr != vec.end(); itr++)
	{
		if (itr->first == key)
			return true;
	}
	return false;
}

std::string
PocoHttpServerRequestImpl::getParameter(const std::string& name, const std::string& defaultValue) const
{
	const Poco::URI uri(_r.getURI());
	const auto vec = uri.getQueryParameters();
	for (auto itr = vec.begin(); itr != vec.end(); itr++)
	{
		if (itr->first == name)
		{
			return itr->second;
		}
	}
	return defaultValue;
}

std::vector<std::string>
PocoHttpServerRequestImpl::getParameters(const std::string& name) const
{
	std::vector<std::string> v;
	const Poco::URI uri(_r.getURI());
	const auto vec = uri.getQueryParameters();
	for (auto itr = vec.begin(); itr != vec.end(); itr++)
	{
		if (itr->first == name)
		{
			v.push_back(std::move(itr->second));
		}
	}
	return v;
}

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
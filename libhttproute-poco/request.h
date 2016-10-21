#pragma once

#include <map>
#include <vector>
#include <string>

#include "libhttproute/request.h"

#include "Poco/Net/HTTPServerRequest.h"

class PocoHttpServerRequestImpl : public HR_NS::HttpServerRequest
{
	const Poco::Net::HTTPServerRequest& _r;

public:
	PocoHttpServerRequestImpl(const Poco::Net::HTTPServerRequest& req);
	virtual ~PocoHttpServerRequestImpl();

	virtual std::string getMethod() const;
	virtual std::string getPath() const;
	virtual std::string getHost() const;
	virtual std::string getScheme() const;

	virtual bool hasHeader(const std::string& key) const
	{
		return _headers.find(key) != _headers.end();
	}
	virtual std::string getHeader(const std::string& key, const std::string& defaultValue = std::string())
	{
		auto itr = _headers.find(key);
		if (itr != _headers.end() && itr->second.size() > 0)
		{
			return itr->second[0];
		}
		return defaultValue;
	}
	virtual std::vector<std::string> getHeaders(const std::string& key) const
	{
		auto itr = _headers.find(key);
		if (itr != _headers.end())
		{
			return itr->second;
		}
		return std::vector<std::string>();
	}
	virtual bool hasParameter(const std::string& key) const
	{
		return _params.find(key) != _params.end();
	}
	virtual std::string getParameter(const std::string& name, const std::string& defaultValue = std::string()) const
	{
		auto itr = _params.find(name);
		if (itr != _params.end() && itr->second.size() > 0)
		{
			return itr->second[0];
		}
		return defaultValue;
	}
	virtual std::vector<std::string> getParameters(const std::string& name) const
	{
		auto itr = _params.find(name);
		if (itr != _params.end())
		{
			return itr->second;
		}
		return std::vector<std::string>();
	}

public:
	std::map<std::string, std::vector<std::string> > _headers;
	std::map<std::string, std::vector<std::string> > _params;
};
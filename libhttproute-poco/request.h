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

	virtual bool hasHeader(const std::string& key) const;
	virtual std::string getHeader(const std::string& key, const std::string& defaultValue = std::string());
	virtual std::vector<std::string> getHeaders(const std::string& key) const;

	virtual bool hasParameter(const std::string& key) const;
	virtual std::string getParameter(const std::string& name, const std::string& defaultValue = std::string()) const;
	virtual std::vector<std::string> getParameters(const std::string& name) const;

public:
	//std::map<std::string, std::vector<std::string> > _headers;
	//std::map<std::string, std::vector<std::string> > _params;
};
#include "request.h"

#include <regex>

PocoHttpServerRequestImpl::PocoHttpServerRequestImpl(const Poco::Net::HTTPServerRequest& req) :
	_r(req)
{
	// extract parts from URI
	// src: ([^:]+):\/\/([^\/]+)(.*)
	/*  const std::regex rx("([^:]+):\\/\\/([^\\/]+)(.*)");
	    const std::string& uri = _r.getURI();

	    std::smatch sm;
	    if (!std::regex_match(uri, sm, rx))
		throw HR_NS::Exception("Invalid URI");

	    if (sm.size() >= 1)
		_scheme = sm.str(1);
	    if (sm.size() >= 2)
		_host = sm.str(2);
	    if (sm.size() >= 3)
		_path = sm.str(3);*/
}

PocoHttpServerRequestImpl::~PocoHttpServerRequestImpl()
{
}

std::string PocoHttpServerRequestImpl::getMethod() const
{
	return _r.getMethod();
}

std::string PocoHttpServerRequestImpl::getPath() const
{
	return _r.getURI();
}

std::string PocoHttpServerRequestImpl::getHost() const
{
	return _r.getHost();
}

std::string PocoHttpServerRequestImpl::getScheme() const
{
	return "http";
}

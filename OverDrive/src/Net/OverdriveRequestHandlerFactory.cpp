#include "OverdriveRequestHandlerFactory.hpp"
#include "testTransfer.hpp"
#include <cstring>

namespace Overdrive {
namespace Net {
	Poco::Net::HTTPRequestHandler *OverdriveRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
		///Add different handlers for different URI
		//if (request.getURI() == "/")
		if (request.getURI() == "/hello") return new myRequestHandler;
		//change this myRequestHandler when u remove testTransfer.hpp
		else if (strstr(request.getURI().c_str(), "/data/")) {
			return new generalResourceHandler();
		}
		else if (request.getURI() == "/test") return new FormRequestHandler;
		return new RootHandler();
	}
}
}
#include "OverdriveRequestHandlerFactory.hpp"
#include "testTransfer.hpp"

namespace Overdrive {
namespace Net {
	Poco::Net::HTTPRequestHandler *OverdriveRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
		///Add different handlers for different URI
		//if (request.getURI() == "/")
		if (request.getURI() == "/hello") return new myRequestHandler;
		else if (request.getURI() == "/test") return new FormRequestHandler;
		return new RootHandler();
	}
}
}
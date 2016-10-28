#include "OverdriveRequestHandlerFactory.hpp"

namespace Overdrive {
namespace Net {
	Poco::Net::HTTPRequestHandler *OverdriveRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
		///Add different handlers for different URI
		//if (request.getURI() == "/")
		return new RootHandler();
	}
}
}
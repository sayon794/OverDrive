#include "OverdriveRequestHandlerFactory.hpp"
#include "Handlers.hpp"

namespace Overdrive {
namespace Net {
	Poco::Net::HTTPRequestHandler *OverdriveRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
		std::string requestURI = request.getURI();

		//std::cout << requestURI << std::endl;

		///Add different handlers for different URI
		//if (request.getURI() == "/")
		if (requestURI == "/hello") return new myRequestHandler;
		//change this myRequestHandler when u remove testTransfer.hpp
		else if (requestURI.find("/img/") != std::string::npos) {
			return new generalResourceHandler();
		}
		else if (requestURI.find("/css/") != std::string::npos) {
			return new CSSHandler();
		}
		else if (requestURI.find("/userAuthenticate") != std::string::npos) {
			return new userAuthHandler();
		}
		else if (requestURI == "/test") return new FormRequestHandler;

		else if (requestURI == "/login") return new LoginRequestHandler;

		else if (requestURI.length() > 1 && requestURI[requestURI.length() - 1] == '/')
			return new DirectoryHandler();

		else if (requestURI.length() > 1)
			//return new FileHandler();
			return new generalResourceHandler();

		return new RootHandler();
	}
}
}
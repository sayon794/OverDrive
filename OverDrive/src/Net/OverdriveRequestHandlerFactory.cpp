#include "OverdriveRequestHandlerFactory.hpp"
#include "Handlers.hpp"
#include "Poco/URI.h"
#include "Filesystem\FileHandler.hpp"

namespace Overdrive {
namespace Net {
	Poco::Net::HTTPRequestHandler *OverdriveRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
		Poco::URI uri(request.getURI());
		std::string requestURI = uri.getPath();

		//std::cout << requestURI << std::endl;

		///Add different handlers for different URI
		//if (requestURI == "/")

		if (requestURI == "/hello") return new myRequestHandler;
		
		else if (requestURI.find("/img/") != std::string::npos) {
			return new generalResourceHandler();
		}
		else if (requestURI.find("/css/") != std::string::npos) {
			return new CSSHandler();
		}
		else if (requestURI.find("/userAuthenticate") != std::string::npos) {
			return new userAuthHandler(map);
		}
		else if (requestURI == "/test") return new FormRequestHandler;

		else if (requestURI == "/login") return new LoginRequestHandler;

		else if (requestURI.length() > 1 && requestURI[requestURI.length() - 1] == '/')
			return new DirectoryHandler();

		else if (requestURI.length() > 1)
			return new FileHandler();

		return new RootHandler();
	}
}
}
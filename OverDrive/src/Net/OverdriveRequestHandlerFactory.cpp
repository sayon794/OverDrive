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
		
		if (requestURI.find("/img/") != std::string::npos) {
			return new generalResourceHandler();
		}
		if (requestURI.find("/css/") != std::string::npos) {
			return new CSSHandler();
		}
		if (requestURI.find("/userAuthenticate") != std::string::npos) {
			return new userAuthHandler(map);
		}
		if (requestURI == "/test") return new FormRequestHandler;

		if (requestURI == "/login") return new LoginRequestHandler;

		if (requestURI.length() > 1 && requestURI[requestURI.length() - 1] == '/')
			return new DirectoryHandler();

<<<<<<< HEAD
		if (requestURI.length() > 1)
			return new generalResourceHandler();
=======
		else if (requestURI.length() > 1)
			return new FileHandler();
>>>>>>> c677be32bca690c71e10a48a2b9605fa510e076f


		return new RootHandler();
	}
}
}
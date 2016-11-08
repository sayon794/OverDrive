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
			return new userAuthHandler(map, states);
		}
		if (requestURI == "/test") return new FormRequestHandler;

		if (requestURI == "/login") return new LoginRequestHandler;

		if (requestURI.length() > 1 && requestURI[requestURI.length() - 1] == '/')
			return new DirectoryHandler();

		if (requestURI.length() > 1)
			return new FileHandler();

		if (CheckLoggedInStatus(request)) {
			return new redirectToRootHandler(rootAdd);
		}
		return new RootHandler();
	}
	bool OverdriveRequestHandlerFactory::CheckLoggedInStatus(const Poco::Net::HTTPServerRequest& request) {
		Poco::Net::NameValueCollection cookies;

		request.getCookies(cookies);

		Poco::Net::NameValueCollection::ConstIterator it = cookies.begin();
		Poco::Net::NameValueCollection::ConstIterator end = cookies.end();

		for (; it != end; it++) {
			if (states.find(it->first) != states.end()) {
				if (states[it->first].getState()) {
					
					rootAdd = it->second;
					return true;
				}
			}
		}
		return false;
	}
}
}
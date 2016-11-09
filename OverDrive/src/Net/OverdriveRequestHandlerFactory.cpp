#include "OverdriveRequestHandlerFactory.hpp"
#include "Handlers.hpp"
#include "Poco/URI.h"
#include "Filesystem\FileHandler.hpp"

namespace Overdrive {
namespace Net {
	Poco::Net::HTTPRequestHandler *OverdriveRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
		Poco::URI uri(request.getURI());
		std::string requestURI = uri.getPath();

		///std::cout << requestURI << std::endl;

		///Add different handlers for different URI
		//if (requestURI == "/")
		if (requestURI.find("/img/") != std::string::npos) {
			return new generalResourceHandler();
		}
		if (requestURI.find("/css/") != std::string::npos) {
			return new CSSHandler();
		}
		
		if (requestURI == "/login") {
			if(!CheckLoggedInStatus(request)) return new LoginRequestHandler;
			else return new redirectToRootHandler(rootAdd);
		}
		if (requestURI.find("/userAuthenticate") != std::string::npos) {
			if (!CheckLoggedInStatus(request)) return new userAuthHandler(map, states);
			else return new redirectToRootHandler(rootAdd);
		}
		

		if (requestURI.length() > 1 && requestURI[requestURI.length() - 1] == '/') {
			if (CheckLoggedInStatus(request)) {
				std::cout << "after checking" << std::endl;
				if(!strncmp(requestURI.c_str(), rootAdd.c_str(), rootAdd.length()))
					return new DirectoryHandler();
				//add 401 or whatever restriction here.
				return new redirectToError();
			}
			
		}
		if (requestURI.length() > 1) {
			if (CheckLoggedInStatus(request)) {
				if (!strncmp(requestURI.c_str(), rootAdd.c_str(), rootAdd.length()))
					return new FileHandler();
				//add 401 or whatever restriction here.
				return new redirectToError();
			}
		}
			

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
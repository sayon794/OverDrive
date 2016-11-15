#include "OverdriveRequestHandlerFactory.hpp"
#include "Handlers.hpp"
#include "Poco/URI.h"
#include "Filesystem\FileHandler.hpp"

namespace Overdrive {
namespace Net {
	Poco::Net::HTTPRequestHandler *OverdriveRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
		Poco::URI uri(request.getURI());
		std::string requestURI = uri.getPath();

		//std::cout << "requested URI " << requestURI << std::endl;

		///Add different handlers for different URI
		//if (requestURI == "/")
		if (requestURI.find("/img/") != std::string::npos) {
			return new generalResourceHandler();
		}
		if (requestURI.find(".html") != std::string::npos) {
			return new generalResourceHandler();
		}
		if (requestURI.find("/css/") != std::string::npos) {
			return new CSSHandler();
		}
		
		bool loggedIn = CheckLoggedInStatus(request);

		if (requestURI.find("/userAuthenticate") == 0) {
			if (!loggedIn) return new userAuthHandler(map, states);
			else return new redirectToRootHandler(rootAdd);
		}

		if (loggedIn && requestURI.find("/logout") == 0) {
			return new logoutHandler(map, states, sessionID);
		}

		if (!loggedIn)
			return new LoginRequestHandler;

		/*if (requestURI == "/login") {
			if(!loggedIn) return new LoginRequestHandler;
			else return new redirectToRootHandler(rootAdd);
		}*/

		
		std::string name = "." + rootAdd + uri.getPath();		//create the relative path
		
		Poco::File file(name);

		if (!file.exists()) return new redirectToError();

		if (requestURI.length() == 0 || requestURI[requestURI.length() - 1] == '/') {
			return new DirectoryHandler(rootAdd,username);
		}

		if (requestURI.length() > 1) {
			return new FileHandler(rootAdd);
		}

		//if (CheckLoggedInStatus(request)) {
		return new redirectToRootHandler("/");
		//}
		//return new redirectToError();
	}

	bool OverdriveRequestHandlerFactory::CheckLoggedInStatus(const Poco::Net::HTTPServerRequest& request) {
		Poco::Net::NameValueCollection cookies;

		request.getCookies(cookies);

		Poco::Net::NameValueCollection::ConstIterator it = cookies.begin();
		Poco::Net::NameValueCollection::ConstIterator end = cookies.end();

		for (; it != end; it++) {
			if (states.find(it->first) != states.end()) {
				if (states[it->first].getState()) {
					sessionID = it->first;
					rootAdd = it->second;
					username = map[sessionID].getUserName();
					return true;
				}
			}
		}
		return false;
	}
}
}
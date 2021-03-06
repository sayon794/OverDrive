#pragma once

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "RootHandler.hpp"
#include "DirectoryHandler.hpp"
#include "SharedRequestHandler.hpp"
#include "UserIDMapper.hpp"
#include <string>
#include <algorithm>
#include <map>
#include "StatePattern.hpp"


namespace Overdrive {
namespace Net {
	class OverdriveRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
	public:
		OverdriveRequestHandlerFactory() {}

		Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest& request);

		bool CheckLoggedInStatus(const Poco::Net::HTTPServerRequest& request);

	private:
		std::map<std::string, UserIDMapper> map;
		std::map<std::string, Context> states;
		std::map<std::string, std::string> sharelinks;
		std::string rootAdd = "";
		std::string sessionID = "";
		std::string username = "";
	};


}
}
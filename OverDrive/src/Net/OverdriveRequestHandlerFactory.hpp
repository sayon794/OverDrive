#pragma once

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "RootHandler.hpp"
#include "DirectoryHandler.hpp"
#include "UserIDMapper.h"
#include <string>
#include <algorithm>
#include <map>


namespace Overdrive {
namespace Net {
	class OverdriveRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
	public:
		OverdriveRequestHandlerFactory() {}

		Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest& request);

	private:
		std::map<std::string, UserIDMapper> map;
	};


}
}
#pragma once

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/URI.h"

namespace Overdrive {
	namespace Filesystem {
		class DirectoryZipper {
		public:
			DirectoryZipper(Poco::URI& uri, Poco::Net::HTTPServerRequest& request, std::string &root, Poco::Net::HTTPServerResponse& response);
		};
	}
}
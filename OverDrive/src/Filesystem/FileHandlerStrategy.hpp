#pragma once

#include <string>
#include <Poco/URI.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/File.h>
#include <Poco/Path.h>
#include <ostream>

namespace Overdrive {
namespace Filesystem {
	class FileHandlerStrategy {
	public:
		virtual void handle(Poco::URI& uri, std::string &root, Poco::Net::HTTPServerResponse& response) = 0;
	};
}
}
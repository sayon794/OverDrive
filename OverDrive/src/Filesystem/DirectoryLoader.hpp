#pragma once

#include "Filesystem/FileHandlerStrategy.hpp"
#include "Filesystem/FileBrowser.hpp"
#include "Poco/FileStream.h"
#include "Poco/Exception.h"

namespace Overdrive {
namespace Filesystem {
	class DirectoryLoader : public FileHandlerStrategy {
		// Inherited via FileHandlerStrategy
	public:
		DirectoryLoader(const std::string &_name) : username(_name) {}
		virtual void handle(Poco::URI & uri, std::string & root, Poco::Net::HTTPServerResponse & response) override;
	private:
		std::string username;
	};
}
}
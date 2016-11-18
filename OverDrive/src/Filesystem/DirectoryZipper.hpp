#pragma once

#include "Filesystem/FileHandlerStrategy.hpp"

namespace Overdrive {
	namespace Filesystem {
		class DirectoryZipper : public FileHandlerStrategy {
		public:
			virtual void handle(Poco::URI& uri, std::string &root, Poco::Net::HTTPServerResponse& response) override;
		};
	}
}
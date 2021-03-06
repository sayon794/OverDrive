#pragma once

#include "Filesystem/FileHandlerStrategy.hpp"

namespace Overdrive {
	namespace Filesystem {
		class AddFolder : public FileHandlerStrategy {
			// Inherited via FileHandlerStrategy
			virtual void handle(Poco::URI& uri, std::string &root, Poco::Net::HTTPServerResponse& response) override;
		};
	}
}
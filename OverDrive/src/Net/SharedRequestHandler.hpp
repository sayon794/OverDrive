#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Net/Handlers.hpp"
#include "Filesystem/DirectoryZipper.hpp"
#include <iostream>

namespace Overdrive {
	namespace Net {
		class SharedRequestHandler : public Poco::Net::HTTPRequestHandler {
		public:
			SharedRequestHandler(const std::string &_root) : path(_root) {}

			void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

		private:
			std::string path;
		};
	}
}
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Net/Handlers.hpp"

namespace Overdrive {
	namespace Net {
		class DirectoryHandler : public Poco::Net::HTTPRequestHandler {
		public:
			DirectoryHandler(std::string &root) { this->root = root; }

			void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

		private:
			std::string root;
		};
	}
}
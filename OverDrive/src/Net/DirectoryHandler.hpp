#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Net/Handlers.hpp"

namespace Overdrive {
	namespace Net {
		class DirectoryHandler : public Poco::Net::HTTPRequestHandler {
		public:
			DirectoryHandler(const std::string &_root, const std::string &_name) : root(_root),username(_name) {}

			void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

		private:
			std::string root;
			std::string username;
		};
	}
}
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

namespace Overdrive {
	namespace Net {
		class FileHandler : public Poco::Net::HTTPRequestHandler {
		public:
			FileHandler(std::string &root) { this->root = root; }

			void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

		private:
			std::string root;
		};
	}
}
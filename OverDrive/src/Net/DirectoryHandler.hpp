#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

namespace Overdrive {
	namespace Net {
		class DirectoryHandler : public Poco::Net::HTTPRequestHandler {
		public:
			DirectoryHandler() {}

			void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

		};
	}
}
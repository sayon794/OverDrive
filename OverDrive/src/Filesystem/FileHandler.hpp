#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

namespace Overdrive {
	namespace Net {
		class FileHandler : public Poco::Net::HTTPRequestHandler {
		public:
			FileHandler() {}

			void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

		};
	}
}
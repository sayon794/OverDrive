#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"

namespace Overdrive {
namespace Net {
	class RootHandler : public Poco::Net::HTTPRequestHandler {
	public:
		RootHandler() {}

		void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

	};
}
}
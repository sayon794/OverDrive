#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include <string>
#include <map>

namespace Overdrive {
	namespace Net {
		class FileHandler : public Poco::Net::HTTPRequestHandler {
		public:
			FileHandler(std::string &_root) : root(_root) {}
			FileHandler(std::string &_root,std::map<std::string,std::string> *m) : root(_root), sharelinks(m) {}

			void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

		private:
			std::string root;
			std::map<std::string, std::string> *sharelinks;
		};
	}
}
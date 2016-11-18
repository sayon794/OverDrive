#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Net/Handlers.hpp"
#include "Filesystem/FileMapper.hpp"

namespace Overdrive {
	namespace Net {
		class DirectoryHandler : public Poco::Net::HTTPRequestHandler {
		public:
			DirectoryHandler(const std::string &_root, const std::string &_name) : root(_root),username(_name) {}
			DirectoryHandler(const std::string &_root, const std::string &_name, std::map<std::string, std::string> *m) 
				: root(_root), username(_name), sharelinks(m) {}

			void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

		private:
			std::string root;
			std::string username;
			std::map<std::string, std::string> *sharelinks;
		};
	}
}
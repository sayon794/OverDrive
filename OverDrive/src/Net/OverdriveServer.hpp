#pragma once

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Exception.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "OverdriveRequestHandlerFactory.hpp"
#include "UserIDMapper.hpp"
#include <cstdlib>
#include <ctime>


namespace Overdrive {
namespace Net {
	class OverdriveServer : public Poco::Util::ServerApplication {
		static OverdriveServer *server;
		
		OverdriveServer() {}
		
		OverdriveServer(const OverdriveServer&) = delete;
		OverdriveServer operator=(const OverdriveServer&) = delete;
		
		void initialize(Poco::Util::Application& self);
		void uninitialize();
		
		int main(const std::vector<std::string>& args);

	public:
		~OverdriveServer() {};

		static OverdriveServer *getInstance();
	};
}
}
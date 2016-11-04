#include"OverdriveServer.hpp"


namespace Overdrive {
namespace Net {
	OverdriveServer* OverdriveServer::server = nullptr;
	
	void OverdriveServer::initialize(Poco::Util::Application& self) {
		loadConfiguration();
		ServerApplication::initialize(self);
	}

	void OverdriveServer::uninitialize() {
		ServerApplication::uninitialize();
	}

	int OverdriveServer::main(const std::vector<std::string>& args) {
		Poco::Net::ServerSocket socket(9980);
		
		Poco::Net::HTTPServer server(new OverdriveRequestHandlerFactory(), socket,
			new Poco::Net::HTTPServerParams);
		server.start();
		waitForTerminationRequest();
		server.stop();
		return Poco::Util::Application::EXIT_OK;
	}

	OverdriveServer *OverdriveServer::getInstance() {
		if (server == nullptr)
			server = new OverdriveServer();
		return server;
	}
}
}
#include <iostream>
#include "Net\OverdriveServer.hpp"

int main(int argc, char** argv) {
	Overdrive::Net::OverdriveServer *server = Overdrive::Net::OverdriveServer::getInstance();
	int ret = server->run(argc,argv);
	delete server;
	return ret;
}
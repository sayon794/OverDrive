#include "SharedRequestHandler.hpp"

void Overdrive::Net::SharedRequestHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response) {
	response.sendFile(path, "Binary Data");
}

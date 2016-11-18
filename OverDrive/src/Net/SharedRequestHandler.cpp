#include "SharedRequestHandler.hpp"

void Overdrive::Net::SharedRequestHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response) {
	if (path[path.length() - 1] != '/') {
		std::string inside = path.substr(path.find_last_of('/') + 1, path.length());
		response.set("Content-Disposition", "attachment; filename=\"" + inside  + "\"");
		response.sendFile(path, "Binary Data");
	}
	else {
		Overdrive::Filesystem::DirectoryZipper dz;
		dz.handle(Poco::URI(path), std::string(""), response);
	}
}

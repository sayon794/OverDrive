#include "FileDelete.hpp"

void Overdrive::Filesystem::FileDelete::handle(Poco::URI& uri, std::string &root, Poco::Net::HTTPServerResponse& response) {
	std::string tempPath = uri.getPath();
	if (tempPath[tempPath.length()] == '/') tempPath.erase(tempPath.length() - 1, 1);
	std::string name = Poco::Path::current() + root + tempPath;
	Poco::File file(name);
	file.remove(true);		//recursive delete = true
	response.redirect(tempPath.substr(0,tempPath.find_last_of('/')+1));
}

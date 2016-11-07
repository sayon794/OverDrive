#include "Filesystem\AddFolder.hpp"
#include <iostream>

void Overdrive::Filesystem::AddFolder::handle(Poco::URI& uri, std::string &root, Poco::Net::HTTPServerResponse& response) {
	std::string tempPath = uri.getPath();
	std::string newName = uri.getQuery().substr(12);

	std::cout << newName << std::endl;

	//if (tempPath[tempPath.length() - 1] == '/') tempPath.erase(tempPath.length() - 1, 1);	// a '/' was added to the end of directories, get rid of that
																							//std::cout << tempPath << std::endl;
	std::string name = "." + root + tempPath+newName+'/';		//create the relative path
	std::cout << name << std::endl;		//std::cout << name << std::endl;

	Poco::File file(name);
	file.createDirectory();
	response.redirect(tempPath );	//redirect to the new link

}

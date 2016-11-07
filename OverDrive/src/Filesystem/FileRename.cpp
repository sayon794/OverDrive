#include "FileRename.hpp"
#include <iostream>

void Overdrive::Filesystem::FileRename::handle(Poco::URI& uri, std::string &root, Poco::Net::HTTPServerResponse& response) {
	std::string tempPath = uri.getPath();

	printf("%s\n", tempPath);
	if (tempPath[tempPath.length() - 1] == '/') tempPath.erase(tempPath.length() - 1, 1);	// a '/' was added to the end of directories, get rid of that
																							//std::cout << tempPath << std::endl;
	std::string name = "." + root + tempPath;		//create the relative path
													//std::cout << name << std::endl;
	Poco::File file(name);	//Possible file creation from 
	//file.renameTo(newName);
	response.redirect(tempPath.substr(0, tempPath.find_last_of('/') + 1));	//redirect to the parent link
}

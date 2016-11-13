#include "Filesystem\DirectoryZipper.hpp"
#include <iostream>
#include <fstream>
#include "Net/Handlers.hpp"
#include <Poco/Zip/Compress.h>
#include <Poco/Zip/ZipCommon.h>
#include <Poco/StreamCopier.h>
#include <Poco/FileStream.h>

Overdrive::Filesystem::DirectoryZipper::DirectoryZipper(Poco::URI& uri, Poco::Net::HTTPServerRequest& request,std::string &root, Poco::Net::HTTPServerResponse& response) {
	std::string directoryName = uri.getPath();
	if (directoryName[directoryName.length() - 1] == '/')
	{
		directoryName.erase(directoryName.length() - 1, 1);	// a '/' was added to the end of directories, get rid of that
		directoryName.erase(0, 1);
		std::cout << "Directory Name " << directoryName << std::endl;	//Ziptest 
	}

	std::string path = "." + root + "/"+directoryName;		//create the relative path
	//std::cout << "Path "<< path << std::endl;				// ./52/ZipTest

	std::ofstream outZip(path+".zip", std::ios::binary);	//Name of The Zip
	Poco::Zip::Compress c(outZip,true);
	Poco::Path data(path);
	data.makeDirectory();
	//std::cout << "Made Directory " << std::endl;

	std::string insideZip = directoryName.substr(directoryName.find_last_of('/') + 1,directoryName.length());

	c.addRecursive(data, Poco::Zip::ZipCommon::CL_NORMAL,true, insideZip);
	c.close(); // MUST be done to finalize the Zip file
	outZip.flush();
	outZip.close();
<<<<<<< HEAD
	//std::cout << "should send file " << path << ".zip" << std::endl;
	//response.sendFile(path + ".zip", "application/zip");	
	//std::cout << "Finished Zipping " << std::endl;
=======
	//response.sendFile(path + ".zip", "application/zip");	
	std::cout << "Finished Zipping " << std::endl ;

	//std::cout << "Path " << path.substr(1, path.length()) <<  std::endl;

	Net::generalResourceHandler g;
	request.setURI(path.substr(1,path.length()) + ".zip");
	g.handleRequest(request, response);
>>>>>>> origin/master

	response.setContentType("Binary Data");
	std::ostream& ostr = response.send();
	Poco::FileInputStream istr(path + ".zip");
	Poco::StreamCopier::copyStream(istr, ostr);

	//Poco::File file(path + ".zip");
	//file.remove();

}

#include "DirectoryLoader.hpp"
#include <iomanip>
#include <sstream>

void Overdrive::Filesystem::DirectoryLoader::handle(Poco::URI & uri, std::string & root, Poco::Net::HTTPServerResponse & response) {
	std::ostream& ostr = response.send();
	Poco::FileInputStream fstr;
	try {
		fstr.open("root.html", std::ios::in);
	}
	catch (Poco::FileException &e) {
		std::cout << "Poco::FileException " << e.message() << std::endl;
	}
	std::string buffer;
	while (std::getline(fstr, buffer)) {
		if (buffer.find("</body>") != std::string::npos) {
			//std::cout << request.getURI() << std::endl;
			//std::cout << "path " << root + uri.getPath().substr(0, uri.getPath().length() - 1) << std::endl;
			Overdrive::Filesystem::FileBrowser filebrowser(root.substr(1,root.length()) + uri.getPath().substr(0, uri.getPath().length() - 1));
			ostr << filebrowser.createScript();
			
			Overdrive::Filesystem::FileBrowser rootbrowser(root.substr(1, root.length()));
			double size = ((double)rootbrowser.getTotalSize())/(1024.0*1024.0);
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << size;
			std::string sizeStr = ss.str();

			ostr << "<script>display_storage(" << sizeStr << ", " << SIZELIMIT << ");";
			ostr << "display_user(\"" << username << "\");</script>";
		}
		ostr << buffer << "\n";
	}
}

#include "DirectoryLoader.hpp"

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
		}
		ostr << buffer << "\n";
	}
}

#include "RootHandler.hpp"
#include "Poco/FileStream.h"
#include "Poco/Exception.h"
#include "../Filesystem/FileBrowser.hpp"
#include <iostream>

namespace Overdrive {
namespace Net {
	
	void RootHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response) {
		response.setChunkedTransferEncoding(true);
		response.setContentType("text/html");

		std::ostream& ostr = response.send();
		Poco::FileInputStream fstr;
		try {
			fstr.open("root.html", std::ios::in);
		}
		catch (Poco::FileException &e) {
			std::cout << e.message() << "\n";
		}
		std::string buffer;
		while (std::getline(fstr,buffer)) {
			if (buffer.find("</body>") != std::string::npos) {
				Overdrive::Filesystem::FileBrowser filebrowser;
				ostr << filebrowser.createScript();
			}
			ostr << buffer << "\n";
		}
	}

}
}

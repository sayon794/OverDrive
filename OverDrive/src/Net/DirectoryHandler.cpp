#include "DirectoryHandler.hpp"
#include "Poco/FileStream.h"
#include "Poco/Exception.h"
#include "Filesystem/FileBrowser.hpp"
#include <iostream>

namespace Overdrive {
	namespace Net {

		void DirectoryHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response) {
			response.setChunkedTransferEncoding(true);
			response.setContentType("text/html");

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
					Overdrive::Filesystem::FileBrowser filebrowser(request.getURI().substr(1,request.getURI().length()-2));
					ostr << filebrowser.createScript();
				}
				ostr << buffer << "\n";
			}
		}

	}
}

#include "DirectoryHandler.hpp"
#include "Poco/FileStream.h"
#include "Poco/Exception.h"
#include "Filesystem/DirectoryLoader.hpp"
#include "Filesystem/DirectoryZipper.hpp"
#include "Filesystem/FileDelete.hpp"
#include "Filesystem/FileRename.hpp"
#include "Filesystem/AddFolder.hpp"
#include "Poco/URI.h"
#include <iostream>

namespace Overdrive {
	namespace Net {
		
		void DirectoryHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response) {

			MyPartHandler partHandler("." + root.substr(0,root.length()-1) + request.getURI());
			Poco::Net::HTMLForm form(request, request.stream(), partHandler);

			response.setChunkedTransferEncoding(true);
			response.setContentType("text/html");

			Poco::Net::NameValueCollection cookies;

			request.getCookies(cookies);

			Poco::Net::NameValueCollection::ConstIterator it = cookies.begin();
			Poco::Net::NameValueCollection::ConstIterator end = cookies.end();

			for (; it != end; it++) {
				std::cout << it->first << " " << it->second << std::endl;
			}

			Poco::URI uri(request.getURI());

			//std::cout << uri.getPath() << " " << uri.getQuery() << std::endl;

			Overdrive::Filesystem::FileHandlerStrategy* filestrat;

			if (uri.getQuery().find("delete") != std::string::npos)
				filestrat = new Overdrive::Filesystem::FileDelete();
			else if (uri.getQuery().find("rename") != std::string::npos)
				filestrat = new Overdrive::Filesystem::FileRename();
			else if (uri.getQuery().find("folder-name") != std::string::npos)
			{
				filestrat = new Overdrive::Filesystem::AddFolder();
			}
			else if (uri.getQuery().find("download") != std::string::npos)
			{
				new Overdrive::Filesystem::DirectoryZipper(uri,request,root,response);
				return;
			}
			else
				filestrat = new Overdrive::Filesystem::DirectoryLoader();

			//std::cout << "root: " << root << std::endl;
			filestrat->handle(uri, root.substr(0,root.length()-1), response);		//add root here later instead of empty string

			delete filestrat;
		}

	}
}

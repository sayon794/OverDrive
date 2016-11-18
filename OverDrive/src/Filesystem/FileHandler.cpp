#include "FileHandler.hpp"
#include "Poco/FileStream.h"
#include "Poco/Exception.h"
#include "Filesystem/DirectoryLoader.hpp"
#include "Filesystem/FileDelete.hpp"
#include "Filesystem/FileRename.hpp"
#include "Filesystem/AddFolder.hpp"
#include "Filesystem/FileMapper.hpp"
#include "Net\Handlers.hpp"

#include "Poco/URI.h"
#include <iostream>

namespace Overdrive {
	namespace Net {

		void FileHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response) {
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
			else if (uri.getQuery().find("map") != std::string::npos)
			{
				filestrat = new Overdrive::Filesystem::FileMapper(sharelinks);
			}
			else /*if (uri.getQuery().find("download") != std::string::npos)*/
			{
				//std::cout << uri.getPath() << " " << uri.getQuery() << " New Download" << std::endl;
				generalResourceHandler g;
				request.setURI(root + request.getURI());
				g.handleRequest(request, response);
				return;
			}
			/*else
				return;*/
			filestrat->handle(uri, root.substr(0, root.length() - 1), response);		//add root here later instead of empty string

			delete filestrat;
		}

	}
}

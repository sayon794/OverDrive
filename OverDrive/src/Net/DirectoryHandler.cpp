#include "DirectoryHandler.hpp"
#include "Poco/FileStream.h"
#include "Poco/Exception.h"
#include "Filesystem/DirectoryLoader.hpp"
#include "Filesystem/FileDelete.hpp"
#include "Poco/URI.h"
#include <iostream>

namespace Overdrive {
	namespace Net {

		void DirectoryHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response) {
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

			Overdrive::Filesystem::FileHandlerStrategy* filestrat;
			
			if (uri.getQuery() == "?delete")
				filestrat = new Overdrive::Filesystem::FileDelete();
			else
				filestrat = new Overdrive::Filesystem::DirectoryLoader();

			filestrat->handle(uri, std::string(""), response);		//add root here later instead of empty string

			delete filestrat;
		}

	}
}

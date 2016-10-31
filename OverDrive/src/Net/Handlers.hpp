#pragma once

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/MessageHeader.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/CountingStream.h"
#include "Poco/NullStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Exception.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/FileStream.h"
#include <iostream>
#include <string>

namespace Overdrive {
	namespace Net {

		class MyPartHandler : public Poco::Net::PartHandler
		{
		public:
			MyPartHandler() :
				_length(0)
			{
			}

			void handlePart(const Poco::Net::MessageHeader& header, std::istream& stream);
			int length() const { return _length; }

			const std::string& name() const { return _name; }

			const std::string& fileName() const { return _fileName; }

			const std::string& contentType() const { return _type; }

		private:
			int _length;
			std::string _type;
			std::string _name;
			std::string _fileName;
		};


		class CSSHandler : public Poco::Net::HTTPRequestHandler {
		public:
			CSSHandler() {  }
			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		};


		class generalResourceHandler : public Poco::Net::HTTPRequestHandler {
		public:
			generalResourceHandler() {  }
			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		};


		class myRequestHandler : public Poco::Net::HTTPRequestHandler {
		public:
			myRequestHandler() {}
			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		};

		class FormRequestHandler : public Poco::Net::HTTPRequestHandler
			/// Return a HTML document with the current date and time.
		{
		public:
			FormRequestHandler() {}

			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		};
	}
}
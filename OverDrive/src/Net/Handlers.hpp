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
#include "Poco/URI.h"
#include "Filesystem\FileBrowser.hpp"
#include <iostream>
#include <string>
#include "UserIDMapper.hpp"
#include "StatePattern.hpp"

#define SIZELIMIT 10

namespace Overdrive {
	namespace Net {

		class MyPartHandler : public Poco::Net::PartHandler
		{
		public:
			MyPartHandler() : _length(0), path("") {}

			MyPartHandler(const std::string& path) : _length(0), path(path) {}

			MyPartHandler(const std::string& path, const std::string& root) : _length(0), path(path), root(root) {}

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
			std::string path;
			std::string root;
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

		class userAuthHandler : public Poco::Net::HTTPRequestHandler {
		public:
			userAuthHandler(std::map<std::string, UserIDMapper> &map, 
				std::map<std::string, Context> &states) {
				m = &map; s = &states; 
			}
			void loadMap(std::string name , std::string pw, Poco::Net::HTTPServerResponse& response);
			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		private:
			std::map<std::string, UserIDMapper> *m;
			std::map<std::string, Context> *s;
			logged_in lin;
		};

		class setAccountHandler : public Poco::Net::HTTPRequestHandler {
		public:
			setAccountHandler(std::map<std::string, UserIDMapper> &map,
				std::map<std::string, Context> &states) {
				m = &map; s = &states;
			}
			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		private:
			std::map<std::string, UserIDMapper> *m;
			std::map<std::string, Context> *s;
			logged_in lin;
		};


		
		class LoginRequestHandler : public Poco::Net::HTTPRequestHandler
			
		{
		public:
			LoginRequestHandler() {}

			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		};

		class signupHandler : public Poco::Net::HTTPRequestHandler

		{
		public:
			signupHandler() {}

			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		};

		class redirectToRootHandler : public Poco::Net::HTTPRequestHandler {
		public:
			redirectToRootHandler(std::string rootAdd) {
				root = rootAdd;
			}
			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		private:
			std::string root;
		};
		class redirectToError : public Poco::Net::HTTPRequestHandler {
		public:
			redirectToError() {	}
			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		};
		class logoutHandler : public Poco::Net::HTTPRequestHandler {
		public:
			logoutHandler(std::map<std::string, UserIDMapper> &map,
				std::map<std::string, Context> &states, std::string SID) {
				m = &map; s = &states; sessionID = SID;
			}
			void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
		private:
			std::map<std::string, UserIDMapper> *m;
			std::map<std::string, Context> *s;
			std::string sessionID;
			not_logged_in lout;
		};
	}
}
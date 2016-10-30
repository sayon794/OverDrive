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


using Poco::Net::ServerSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Net::MessageHeader;
using Poco::Net::HTMLForm;
using Poco::Net::NameValueCollection;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::CountingInputStream;
using Poco::NullOutputStream;
using Poco::StreamCopier;

class MyPartHandler : public Poco::Net::PartHandler
{
public:
	MyPartHandler() :
		_length(0)
	{
	}

	void handlePart(const MessageHeader& header, std::istream& stream);
	int length() const{return _length;}

	const std::string& name() const{return _name;}

	const std::string& fileName() const{return _fileName;}

	const std::string& contentType() const{return _type;}

private:
	int _length;
	std::string _type;
	std::string _name;
	std::string _fileName;
};


class CSSHandler : public HTTPRequestHandler {
public:
	CSSHandler() {  }
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
};


class generalResourceHandler : public HTTPRequestHandler {
public:
	generalResourceHandler() {  }
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
};


class myRequestHandler : public HTTPRequestHandler {
public:
	myRequestHandler() {}
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
};

class FormRequestHandler : public HTTPRequestHandler
	/// Return a HTML document with the current date and time.
{
public:
	FormRequestHandler(){}

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);
};


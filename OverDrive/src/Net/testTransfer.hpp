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

	void handlePart(const MessageHeader& header, std::istream& stream)
	{
		_type = header.get("Content-Type", "(unspecified)");
		if (header.has("Content-Disposition"))
		{
			std::string disp;
			NameValueCollection params;
			MessageHeader::splitParameters(header["Content-Disposition"], disp, params);
			_name = params.get("name", "(unnamed)");
			_fileName = params.get("filename", "(unnamed)");
		}

		CountingInputStream istr(stream);

		//NullOutputStream ostr;
		Poco::FileOutputStream ostr(fileName());
		StreamCopier::copyStream(istr, ostr);
		_length = istr.chars();
	}

	int length() const
	{
		return _length;
	}

	const std::string& name() const
	{
		return _name;
	}

	const std::string& fileName() const
	{
		return _fileName;
	}

	const std::string& contentType() const
	{
		return _type;
	}

private:
	int _length;
	std::string _type;
	std::string _name;
	std::string _fileName;
};
class generalResourceHandler : public HTTPRequestHandler {
public:
	generalResourceHandler() {  }
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		response.setChunkedTransferEncoding(true);
		response.setContentType("Binary Data");

		std::ostream& ostr = response.send();

		char req[100];

		strcpy(req, request.getURI().c_str());
		Poco::FileInputStream istr(req + 1);
		StreamCopier::copyStream(istr, ostr);
	}
};
class myRequestHandler : public HTTPRequestHandler {
public:
	myRequestHandler() {}
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		Application& app = Application::instance();
		app.logger().information("Request from " + request.clientAddress().toString());

		HTMLForm form(request, request.stream());

		response.setChunkedTransferEncoding(true);
		response.setContentType("Binary Data");

		std::ostream& ostr = response.send();


		Poco::FileInputStream istr("data/logo.png");
		StreamCopier::copyStream(istr, ostr);

	}
};

class FormRequestHandler : public HTTPRequestHandler
	/// Return a HTML document with the current date and time.
{
public:
	FormRequestHandler()
	{
	}

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
	{
		Application& app = Application::instance();
		app.logger().information("Request from " + request.clientAddress().toString());

		MyPartHandler partHandler;
		HTMLForm form(request, request.stream(), partHandler);

		response.setChunkedTransferEncoding(true);
		response.setContentType("text/html");

		std::ostream& ostr = response.send();

		ostr <<
			"<html>\n"
			"<head>\n"
			"<title>POCO Form Server Sample</title>\n"
			"</head>\n"
			"<body>\n"
			"<h1>POCO Form Server Sample</h1>\n"
			"<h2>File Upload</h2>\n"
			"<form method=\"POST\" action=\"/test\" enctype=\"multipart/form-data\">\n"
			"<input type=\"file\" name=\"file\" size=\"31\"> \n"
			"<input type=\"submit\" value=\"Upload\">\n"
			"</form>\n"
			"<a href=\"/hello\"> click here </a>";

		ostr << "<h2>Request</h2><p>\n";
		ostr << "Method: " << request.getMethod() << "<br>\n";
		ostr << "URI: " << request.getURI() << "<br>\n";
		NameValueCollection::ConstIterator it = request.begin();
		NameValueCollection::ConstIterator end = request.end();
		for (; it != end; ++it)
		{
			ostr << it->first << ": " << it->second << "<br>\n";
		}
		ostr << "</p>";

		if (!form.empty())
		{
			ostr << "<h2>Form</h2><p>\n";
			it = form.begin();
			end = form.end();
			for (; it != end; ++it)
			{
				ostr << it->first << ": " << it->second << "<br>\n";
			}
			ostr << "</p>";
		}

		if (!partHandler.name().empty())
		{
			ostr << "<h2>Upload</h2><p>\n";
			ostr << "Name: " << partHandler.name() << "<br>\n";
			ostr << "File Name: " << partHandler.fileName() << "<br>\n";
			ostr << "Type: " << partHandler.contentType() << "<br>\n";
			ostr << "Size: " << partHandler.length() << "<br>\n";
			ostr << "</p>";
		}
		ostr << "</body>\n";
	}
};


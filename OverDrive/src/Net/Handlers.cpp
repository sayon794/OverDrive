#include "Handlers.hpp"

namespace Overdrive {
	namespace Net {
		void MyPartHandler::handlePart(const Poco::Net::MessageHeader& header, std::istream& stream)
		{
			_type = header.get("Content-Type", "(unspecified)");
			if (header.has("Content-Disposition"))
			{
				std::string disp;
				Poco::Net::NameValueCollection params;
				Poco::Net::MessageHeader::splitParameters(header["Content-Disposition"], disp, params);
				_name = params.get("name", "(unnamed)");
				_fileName = params.get("filename", "(unnamed)");
			}

			Poco::CountingInputStream istr(stream);

			Poco::FileOutputStream ostr(fileName());
			Poco::StreamCopier::copyStream(istr, ostr);
			_length = istr.chars();
		}

		void authPartHandler::handlePart(const Poco::Net::MessageHeader& header, std::istream& stream)
		{
			_type = header.get("Content-Type", "(unspecified)");
			if (header.has("Content-Disposition"))
			{
				std::string disp;
				Poco::Net::NameValueCollection params;
				Poco::Net::MessageHeader::splitParameters(header["Content-Disposition"], disp, params);
				_name = params.get("name", "(unnamed)");
				_fileName = params.get("filename", "(unnamed)");
			}

			Poco::CountingInputStream istr(stream);

			Poco::FileOutputStream ostr(fileName());
			Poco::StreamCopier::copyStream(istr, ostr);
			_length = istr.chars();
		}

		void CSSHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
			response.setChunkedTransferEncoding(true);
			response.setContentType("text/css");

			std::ostream& ostr = response.send();

			char req[100];

			strcpy(req, request.getURI().c_str());
			Poco::FileInputStream istr(req + 1);
			Poco::StreamCopier::copyStream(istr, ostr);
		}

		void generalResourceHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
			response.setChunkedTransferEncoding(true);
			response.setContentType("Binary Data");

			std::ostream& ostr = response.send();

			char req[100];

			strcpy(req, request.getURI().c_str());
			Poco::FileInputStream istr(req + 1);
			Poco::StreamCopier::copyStream(istr, ostr);
		}

		void  myRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
			Poco::Util::Application& app = Poco::Util::Application::instance();
			app.logger().information("Request from " + request.clientAddress().toString());

			Poco::Net::HTMLForm form(request, request.stream());

			response.setChunkedTransferEncoding(true);
			response.setContentType("Binary Data");

			std::ostream& ostr = response.send();


			Poco::FileInputStream istr("data/logo.png");
			Poco::StreamCopier::copyStream(istr, ostr);

		}

		void  userAuthHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
			
			Poco::Net::HTMLForm form(request, request.stream());
			
			NameValueCollection::ConstIterator it;
			NameValueCollection::ConstIterator end;
			if (!form.empty())
			{
				it = form.begin();
				end = form.end();
				for (; it != end; ++it)
				{
					std::cout << it->first << ": " << it->second << std::endl;
				}
			}

			response.redirect("/52");
			
		}

		void LoginRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
			Poco::Util::Application& app = Poco::Util::Application::instance();
			app.logger().information("Request from " + request.clientAddress().toString());

			Poco::Net::HTMLForm form(request, request.stream());

			response.setChunkedTransferEncoding(true);
			response.setContentType("text/html");

			std::ostream& ostr = response.send();
			
			Poco::FileInputStream istr("login.html");
			Poco::StreamCopier::copyStream(istr, ostr);

		}


		void FormRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
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
				"<h2>GET Form</h2>\n"
				"<form method=\"GET\" action=\"/form\">\n"
				"<input type=\"text\" name=\"text\" size=\"31\">\n"
				"<input type=\"submit\" value=\"GET\">\n"
				"</form>\n"
				"<h2>POST Form</h2>\n"
				"<form method=\"POST\" action=\"/test\">\n"
				"<input type=\"text\" name=\"text\" size=\"31\">\n"
				"<input type=\"submit\" value=\"POST\">\n"
				"</form>\n"
				"<h2>File Upload</h2>\n"
				"<form method=\"POST\" action=\"/form\" enctype=\"multipart/form-data\">\n"
				"<input type=\"file\" name=\"file\" size=\"31\"> \n"
				"<input type=\"submit\" value=\"Upload\">\n"
				"</form>\n";

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
	}
}
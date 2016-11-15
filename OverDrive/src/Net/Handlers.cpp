#include "Handlers.hpp"
#include "UserIDMapper.hpp"

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

			Poco::FileOutputStream ostr(path + fileName());
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
			//std::cout << request.getURI() << std::endl;
			response.setChunkedTransferEncoding(true);
			response.setContentType("Binary Data");

			std::ostream& ostr = response.send();

			//char req[100];

			Poco::URI req(request.getURI());
			//strcpy(req, request.getURI().c_str());
			//Poco::FileInputStream istr(req + 1);
			//std::cout << "Handlers.cpp" << req.getPath().substr(1, req.getPath().length() - 1) << std::endl;
			Poco::FileInputStream istr(req.getPath().substr(1,req.getPath().length()-1));
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
		void userAuthHandler::loadMap(std::string name, std::string pw, Poco::Net::HTTPServerResponse& response) {
			FILE* fp;
			fp = fopen("mapping.txt", "r");
			char tempName[100];
			char tempRName[100];
			char tempPw[100];
			char tempRoot[100];
			while (fscanf(fp, "%s%s%s", tempName, tempPw, tempRoot) == 3) {
				fgets(tempRName, 32, fp);
				tempRName[strlen(tempRName) - 1] = 0;
				printf("%s %s %s %s\n", tempName, tempRName, tempPw, tempRoot);
				if (std::string(tempName) == name && std::string(tempPw) == pw) {
					fclose(fp);

					std::string sessionID = std::string(tempName) + std::string(tempPw);
					
					(*m)[sessionID] = UserIDMapper(tempName,tempPw,tempRoot,tempRName);
					(*s)[sessionID] = Context();

					lin.doAction((*s)[sessionID]);

					response.addCookie(Poco::Net::HTTPCookie(sessionID, tempRoot));
					//response.redirect(tempRoot);
					response.redirect("/");
					fclose(fp);
					return;
				}
			}
			fclose(fp);
			response.redirect("/login");
		}
		void  userAuthHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
			
			Poco::Net::HTMLForm form(request, request.stream());
			
			Poco::Net::NameValueCollection::ConstIterator it;
			Poco::Net::NameValueCollection::ConstIterator end;
			if (!form.empty())
			{
				it = form.begin();
				end = form.begin();
				end++;
				loadMap(it->second, end->second, response);
			}
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


		/*void FormRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
		{
			Poco::Util::Application& app = Poco::Util::Application::instance();
			app.logger().information("Request from " + request.clientAddress().toString());

			MyPartHandler partHandler;
			Poco::Net::HTMLForm form(request, request.stream(), partHandler);

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
			Poco::Net::NameValueCollection::ConstIterator it = request.begin();
			Poco::Net::NameValueCollection::ConstIterator end = request.end();
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
		}*/
		void redirectToRootHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
		{
			response.redirect(root);
		}
		void redirectToError::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
		{
			Poco::Net::HTMLForm form(request, request.stream());

			response.setChunkedTransferEncoding(true);
			response.setContentType("text/html");

			std::ostream& ostr = response.send();

			Poco::FileInputStream istr("error.html");
			Poco::StreamCopier::copyStream(istr, ostr);

		}
		
		void logoutHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response){
			lout.doAction((*s)[sessionID]);
			response.redirect("/");	
		}
		void signupHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
		{
			Poco::Net::HTMLForm form(request, request.stream());

			response.setChunkedTransferEncoding(true);
			response.setContentType("text/html");

			std::ostream& ostr = response.send();

			Poco::FileInputStream istr("signup.html");
			Poco::StreamCopier::copyStream(istr, ostr);
		}
		void setAccountHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
		{
			Poco::Net::HTMLForm form(request, request.stream());

			Poco::Net::NameValueCollection::ConstIterator it;
			Poco::Net::NameValueCollection::ConstIterator end;

			std::string name;
			std::string roll;
			std::string batch;
			std::string password;
			std::string username;
			std::string root;
			if (!form.empty())
			{
				it = form.begin();
				
				name = it->second; it++;
				batch = it->second; it++;
				roll = it->second; it++;
				password = it->second; it++;

				username = roll + "_" + batch;

				root = "/" + username + "/";

				FILE *fp = fopen("mapping.txt", "a");

				fprintf(fp, "%s %s /%s/ %s\n", username.c_str(), password.c_str(), username.c_str(), name.c_str());
				fclose(fp);

				std::string sessionID = std::string(username) + std::string(password);

				(*m)[sessionID] = UserIDMapper(username, password, root, name);
				(*s)[sessionID] = Context();

				lin.doAction((*s)[sessionID]);

				response.addCookie(Poco::Net::HTTPCookie(sessionID, root));

				Poco::File file(username);
				file.createDirectory();
			}
			response.redirect("/");
		}
}
}
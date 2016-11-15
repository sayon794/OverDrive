#include "FileBrowser.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <Poco/DateTimeFormatter.h>
#include <Poco/LocalDateTime.h>
namespace Overdrive {
namespace Filesystem {
	
	FileBrowser::FileBrowser() : currdir("") {
		Poco::File dir(Poco::Path::current());
		dir.list(dirlist);
	}

	FileBrowser::FileBrowser(const std::string &path) : currdir(path) {
		Poco::File dir(currdir);
		dir.list(dirlist);
		//std::cout << Poco::Path::current() << std::endl;
	}

	std::string FileBrowser::createScript() {
		std::string res;
		
		for (auto filename : dirlist) {
			Poco::File file;
			if (currdir == "")
				file = Poco::File(filename);
			else
				file = Poco::File(currdir + "/" + filename);

			res += "<script>addRow(\"" + filename + "\", \"";
			if (currdir == "") res += filename;
			else res += /*currdir + "/" +*/ filename;
			res += "\", ";
			if (file.isDirectory())
				res += "1, ";
			else
				res += "0, ";

			std::string details = std::to_string(file.getSize()) + createFileDescription(file);
			res += details;
			std::cout << res << std::endl;
		}

		return res;
	}

	std::string FileBrowser::createFileDescription(Poco::File file)
	{
		std::string output="";
		double size = (double)file.getSize();
		std::string unit = "B";
		if (size > 1024 * 1024)
		{
			size = size / (1024 * 1024);
			unit = "MB";
		}
		else if (size > 1024)
		{
			size = size / 1024;
			unit = "KB";
		}
		std::stringstream ss;
		ss << std::fixed << std::setprecision(2) << size;
		std::string sizeStr = ss.str();

		output += ", \"" + sizeStr+" ";
		output += unit+"\", ";

		Poco::Timestamp modifiedtime = file.getLastModified();
		Poco::LocalDateTime localtime = Poco::LocalDateTime(modifiedtime);
		//std::string s = Poco::DateTimeFormatter::format(modifiedtime, "%dd %H:%M:%S", 65535);
		std::string s = Poco::DateTimeFormatter::format(localtime, "%b %f, %Y %h:%M:%S %A");

		output += std::to_string(modifiedtime.epochTime())+", \" "+ s+"\"); </script>\n";

		return output;
	}
}
}
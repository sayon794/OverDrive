#include "FileBrowser.hpp"
#include <iostream>

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
			res += std::to_string(file.getSize()) + ", \"" + std::to_string(file.getSize());
			res += " B\", 0, \"\"); </script>\n";
		}

		return res;
	}
}
}
#pragma once

#include "Poco/File.h"
#include "Poco/Path.h"
#include "Net/Handlers.hpp"
#include <vector>
#include <string>
#include <memory>

namespace Overdrive {
namespace Filesystem {
	//Browse the current working directory. For adding the script to html.
	class FileBrowser {
	public:
		FileBrowser();
		FileBrowser(const std::string &path);
		~FileBrowser() {}

		std::string createScript();
		std::string createFileDescription(Poco::File file);
		long long int getTotalSize();
		long long int getSize(Poco::File file);
	private:
		std::vector<std::string> dirlist;
		std::string currdir;	//working directory relative to server root

	};

}
}
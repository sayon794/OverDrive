#pragma once

#include "Poco\File.h"
#include "Poco\Path.h"
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

	private:
		std::vector<std::string> dirlist;
		std::string currdir;	//working directory relative to server root

	};

}
}
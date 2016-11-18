#include "Filesystem/FileHandlerStrategy.hpp"
#include <map>
#include <cstdlib>

namespace Overdrive {
	namespace Filesystem {
		class FileMapper : public FileHandlerStrategy {
		public:
			FileMapper(std::map < std::string, std::string> *m) : sharelinks(m) {}
			~FileMapper() { sharelinks = nullptr; }
			virtual void handle(Poco::URI & uri, std::string & root, Poco::Net::HTTPServerResponse & response) override;
		
		private:
			std::string randstring();

			std::map<std::string, std::string> *sharelinks;
			const std::string alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		};
	}
}
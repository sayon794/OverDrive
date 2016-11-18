#include "FileMapper.hpp"

void Overdrive::Filesystem::FileMapper::handle(Poco::URI & uri, std::string & root, Poco::Net::HTTPServerResponse & response) {
	std::string tempPath = uri.getPath();
	//if (tempPath[tempPath.length() - 1] == '/') tempPath.erase(tempPath.length() - 1, 1);	// a '/' was added to the end of directories, get rid of that
	std::string name = "." + root + tempPath;		//create the relative path
													//std::cout << name << std::endl;
	if (sharelinks->size() > 500)
		for (int i = 0; i < 50; i++) 
			sharelinks->erase(sharelinks->begin());

	std::string key;
	while (1) {
		key = randstring();
		if (sharelinks->find(key) == sharelinks->end())
			break;
	}
	(*sharelinks)[key] = name;
	std::ostream& ostr = response.send();
	ostr << "?share=" << key;
}

std::string Overdrive::Filesystem::FileMapper::randstring() {
	int slen = alphanum.size();
	int rlen = std::rand()%10 + 6;
	std::string result("");
	
	for (int i = 0; i < rlen; i++)
		result += alphanum[std::rand() % slen];

	return result;
}

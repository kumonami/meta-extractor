#ifndef EXTRACTOR_HPP
#define EXTRACTOR_HPP

#include <string>

class Extractor {
	public:
		static std::string extractMetadata(const std::string& filePath);
};

#endif // EXTRACTOR_HPP
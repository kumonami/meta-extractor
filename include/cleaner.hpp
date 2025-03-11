#ifndef CLEANER_HPP
#define CLEANER_HPP

#include <string>
#include <vector>

class Cleaner {
public:
	static bool removeMetadata(const std::string& filePath, const std::vector<std::string>& tags);
	static bool osRemoveMetadata(const std::string& filePath);
	static std::string join(const std::vector<std::string>& parts, const std::string& delimiter);
};

#endif // CLEANER_HPP

#include "../include/cleaner.hpp"
#include <sstream>


bool Cleaner::removeMetadata(const std::string& filePath, const std::vector<std::string>& tags) {
	std::vector<std::string> commandParts = {"exiftool", "-overwrite_original"};

	if (tags.empty() || tags[0] == "all") {
		commandParts.insert(commandParts.end(), {"-all=", "-XMP:All=", "-IPTC:All=", "-EXIF:All=", "-Comment="});
	} else {
		for (const auto& tag : tags) {
			commandParts.push_back("-" + tag + "=");
		}
	}
	commandParts.push_back(filePath);

	if (system(join(commandParts, " ").c_str()) != 0) {
		return false;
	}

	return (tags.empty() || tags[0] == "all") ? osRemoveMetadata(filePath) : true;
}

bool Cleaner::osRemoveMetadata(const std::string& filePath) {
	std::vector<std::string> commands = {
		"chmod u+rw " + filePath,
		"touch -r /dev/null " + filePath,
		"magick " + filePath + " -strip " + filePath
	};

	for (const auto& cmd : commands) {
		if (system(cmd.c_str()) != 0) {
			return false;
		}
	}
	return true;
}

std::string Cleaner::join(const std::vector<std::string>& parts, const std::string& delimiter) {
	std::ostringstream joined;
	for (size_t i = 0; i < parts.size(); ++i) {
		if (i > 0) joined << delimiter;
		joined << parts[i];
	}
	return joined.str();
}

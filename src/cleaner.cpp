#include "../include/cleaner.hpp"
#include <sstream>

bool Cleaner::removeMetadata(const std::string& filePath, const std::vector<std::string>& tags) {
	std::ostringstream command;
	command << "exiftool -overwrite_original ";
	if (tags.empty() || tags[0] == "all") {
		command << "-all= -XMP:All= -IPTC:All= -EXIF:All= -Comment= ";
	} else {
		for (const auto& tag : tags) { 
			command << "-" << tag << "= ";
		}
	}
	command << " " << filePath;
	if (system(command.str().c_str()) != 0) {
        return false;
    }
	return osRemoveMetadata(filePath);
}

bool Cleaner::osRemoveMetadata(const std::string& filePath) {
	std::ostringstream chmodCommand;
    chmodCommand << "chmod u+rx " << filePath;
    if (system(chmodCommand.str().c_str()) != 0) {
        return false;
    }
	std::ostringstream touchCommand;
    touchCommand << "touch -r /dev/null " << filePath;
    if (system(touchCommand.str().c_str()) != 0) {
        return false;
    }
	std::ostringstream convertCommand;
	convertCommand << "magick " << filePath << " -strip " << filePath;
	if (system(convertCommand.str().c_str()) != 0) {
		return false;
	}
    return true;
}
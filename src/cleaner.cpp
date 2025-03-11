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
	std::ostringstream chmodCommand, touchCommand, convertCommand;

    chmodCommand << "chmod u+rx " << filePath;
    touchCommand << "touch -r /dev/null " << filePath;
	convertCommand << "magick " << filePath << " -strip " << filePath;

    int chmodResult = system(chmodCommand.str().c_str());
	int touchResult = system(touchCommand.str().c_str());
	int convertResult = system(convertCommand.str().c_str());

	if (chmodResult != 0 || touchResult != 0 || convertResult != 0) {
		return false;
	}

    return true;
}
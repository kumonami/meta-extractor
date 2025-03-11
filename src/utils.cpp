#include "../include/utils.hpp"
#include <filesystem>
#include <sstream>
#include <fstream>
#include <iostream>
// #include <libexif/exif-data.h>
#include <vector>


std::string Utils::getFileExtension(const std::string& filePath) {
    return std::filesystem::path(filePath).extension().string().substr(1);
}

std::string Utils::extractVideoMetadata(const std::string& filePath) { return ""; }
std::string Utils::extractDocumentMetadata(const std::string& filePath) { return ""; }
std::string Utils::extractAudioMetadata(const std::string& filePath) { return ""; }

std::string Utils::extractImageMetadata(const std::string& filePath) {
	std::array<char, 128> buffer;
	std::ostringstream result;
	std::string command = "exiftool -j " + filePath;
	FILE *pipe = popen(command.c_str(), "r");
	if (!pipe || pipe == nullptr) {
		std::cerr << "Failed to execute command: " << command << std::endl;
		return "";
	}

	while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
		result << buffer.data();
	}
	pclose(pipe);
	return result.str();
}


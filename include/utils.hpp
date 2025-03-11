#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

class Utils {
public:
    static std::string getFileExtension(const std::string& filePath);

	static std::string extractImageMetadata(const std::string& filePath); // jpeg, png
    static std::string extractVideoMetadata(const std::string& filePath); // mp4, mkv
    static std::string extractDocumentMetadata(const std::string& filePath); // pdf, docx
    static std::string extractAudioMetadata(const std::string& filePath); // mp3, wav
};

#endif 
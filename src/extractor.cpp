#include "../include/extractor.hpp"
#include "../include/utils.hpp"
#include "../include/geo.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>


std::string Extractor::extractMetadata(const std::string& filePath) {
	if (!std::filesystem::exists(filePath)) {
		return "File not found: " + filePath;
	}

    std::cout << "Extracting metadata..." << std::endl;

    std::string metadata;

	std::string extension = Utils::getFileExtension(filePath);
	if (extension == "jpg" || extension == "png") {
        metadata = Utils::extractImageMetadata(filePath);
    } else if (extension == "mp4" || extension == "mkv") {
        metadata = Utils::extractVideoMetadata(filePath);
    } else if (extension == "pdf" || extension == "docx") {
        metadata = Utils::extractDocumentMetadata(filePath);
    } else if (extension == "mp3" || extension == "wav") {
        metadata = Utils::extractAudioMetadata(filePath);
    } else {
        return "Unsupported file type: " + extension;
    }

    std::cout << "...metadata received" << std::endl;

    auto coordinates = Geo::extractCoordinates(metadata);
    if (coordinates) {
        std::string location = Geo::getLocation(coordinates->first, coordinates->second);
        metadata += "\nLocation: " + location;
    }

    return metadata;
}
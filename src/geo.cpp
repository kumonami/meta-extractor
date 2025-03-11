#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include "../include/geo.hpp"
#include <iostream>
#include <sstream>

using json = nlohmann::json;

std::optional<std::pair<double, double>> Geo::extractCoordinates(const std::string& metadataJson) {
	if (metadataJson.empty()) {
        std::cerr << "Error: Empty metadata JSON string." << std::endl;
        return std::nullopt;
    }

    try {
        json metadata = json::parse(metadataJson);
        
        if (metadata.contains("GPSLatitude") && metadata.contains("GPSLongitude")) {
            double latitude = metadata["GPSLatitude"];
            double longitude = metadata["GPSLongitude"];
            return std::make_pair(latitude, longitude);
        }
    } catch (const json::parse_error& e) {
        std::cerr << "Error: Failed to parse metadata JSON. " << e.what() << std::endl;
    }

	return std::nullopt;
}

const std::string openmapurl = "https://nominatim.openstreetmap.org/reverse?format=json";

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string Geo::getLocation(double latitude, double longitude) {
	std::ostringstream url;
	url << openmapurl <<  "&lat=" << latitude << "&lon=" << longitude;

	CURL* curl = curl_easy_init();
	if (!curl || curl == nullptr) return "Error: curl_easy_init failed";

	curl_easy_setopt(curl, CURLOPT_URL, url.str().c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "MyApp/1.0 (no-website-available)");
	curl_easy_setopt(curl, CURLOPT_REFERER, "no-website-available");

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

	std::string response;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

	CURLcode res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
    if (res != CURLE_OK) {
        std::cout << "Error: " << curl_easy_strerror(res) << std::endl;
        return "Error: Request failed";
    }

    if (response.empty()) {
		std::string errMsg = "Error: Empty response";
        std::cout << errMsg << std::endl;
        return errMsg;
    }

    try {
        json data = json::parse(response);
        return data.contains("display_name") ? data["display_name"] : "Unknown location";
    } catch (const json::parse_error& e) {
        std::cout << "JSON parse error: " << e.what() << std::endl;
        return "Error: Failed to parse response";
    }
}
#ifndef GEO_HPP
#define GEO_HPP

#include <string>
#include <optional>

class Geo {
public:
	static std::optional<std::pair<double, double>> extractCoordinates(const std::string& metadataJson);
	static std::string getLocation(double latitude, double longitude);
};

#endif // GEO_HPP

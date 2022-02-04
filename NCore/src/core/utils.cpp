#include "ncpch.h"
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;

json LoadJson(const std::string& filename) {

	json j;

	while (true) {

		std::ifstream ifs(filename.c_str());
		if (!ifs.is_open()) {
			nc_assert(false, fmt::format("Failed to open json file {}", filename));
			continue;
		}

#ifndef NC_DEBUG

		j = json::parse(ifs, nullptr, false);
		if (j.is_discarded()) {
			ifs.close();
			log_critical("Failed to parse json file {}", filename);
			continue;
		}

#else

		try
		{
			// parsing input with a syntax error
			j = json::parse(ifs);
		}
		catch (json::parse_error& e)
		{
			ifs.close();
			// output exception information
			log_critical("Failed to parse json file {}\n{}\nAt offset: {}", filename.c_str(), e.what(), e.byte);

			continue;
		}

#endif

		// The json is correct, we can leave the while loop
		break;
	}

	return j;
}

json Merge(const json& a, const json& b)
{
	json result = a.flatten();
	json tmp = b.flatten();
	for (auto it = tmp.begin(); it != tmp.end(); ++it)
		result[it.key()] = it.value();
	return result.unflatten();
}

void GenerateDefaultAssets() {
	fs::create_directories("assets/input");
	fs::create_directories("assets/shaders");
}

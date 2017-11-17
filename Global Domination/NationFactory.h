#pragma once

#include <vector>

#include "Nation.h"

#include "json.hpp"

namespace global_domination
{
	class NationFactory
	{
	public:
		std::vector<Nation> createNations(std::string file_path);
		void createJSONFile(std::vector<Nation> nations);
	};

	void to_json(nlohmann::json& j, const Nation& p);
	void from_json(const nlohmann::json& j, Nation& p);
}
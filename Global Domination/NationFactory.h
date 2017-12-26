#pragma once

#include <vector>

#include "Nation.h"

#include "json.hpp"

namespace global_domination
{
	class NationFactory
	{
	public:
		void createNations(std::string file_path);
		void createJSONFile(std::vector<Nation> nations);
		Nation* getNation(std::string name);
		std::vector<Nation> getNations();
	private:
		std::vector<Nation> nations_;
	};

	std::map<TradeResource, int> getTradeResources(const nlohmann::json& j);
	void to_json(nlohmann::json& j, const Nation& p);
	void from_json(const nlohmann::json& j, Nation& p);
}
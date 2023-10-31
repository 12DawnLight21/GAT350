#pragma once
#include <string>

namespace nc
{
	class StringUtils
	{
	public:
		std::string toUpper(const std::string& input);
		std::string toLower(const std::string& input);
		bool isEqualIgnoreCase(const std::string& s1, const std::string& s2);
		std::string createUnique(const std::string& input);
	};
}
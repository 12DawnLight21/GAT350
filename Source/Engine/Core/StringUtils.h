#pragma once
#include <string>

namespace nc
{
	class StringUtils
	{
	public:
		static std::string toUpper(const std::string& input);
		static std::string toLower(const std::string& input);
		static bool isEqualIgnoreCase(const std::string& s1, const std::string& s2);
		static std::string createUnique(const std::string& input);
	};
}
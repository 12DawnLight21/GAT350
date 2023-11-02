#include "StringUtils.h"
#include <algorithm>

namespace nc
{
	std::string StringUtils::toUpper(const std::string& input)
	{
		if (input.empty()) return "Input is empty";

		//copies input string
		std::string newInput = input;

		//converts string to uppercase
		for (char& c : newInput)
		{
			c = std::toupper(c);
		}

		//returns the uppercase string
		return newInput;
	}

	std::string StringUtils::toLower(const std::string& input) 
	{
		if (input.empty()) return "Input is empty";

		//copies input string
		std::string newInput = input;

		//converts string to lowercase
		for (char& c : newInput)
		{
			c = std::tolower(c);
		}

		//returns the lowercase string
		return newInput;
	}

	bool StringUtils::isEqualIgnoreCase(const std::string& str1, const std::string& str2)
	{
		if (str1.length() != str2.length()) {
			return false;
		}
		return std::equal(str1.begin(), str1.end(), str2.begin(),
			[](char a, char b) {
				return tolower(a) == tolower(b);
			});

	}

	std::string CreateUnique(const std::string& input)
	{
		static uint32_t unique = 0;

		return input + std::to_string(unique++);
	}
}
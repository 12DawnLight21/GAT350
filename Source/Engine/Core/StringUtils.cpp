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

	bool StringUtils::isEqualIgnoreCase(const std::string& s1, const std::string& s2)
	{
		//if there's no strings to compare, dont do it
		if (s1.empty() || s2.empty()) return "Input 1 or 2 is empty";

		//copies both strings
		std::string s1Copy = s1;
		std::string s2Copy = s2;

		//compares two strings IGNORING CASE
		if (s1Copy.length() == s2Copy.length())
		{
			for (char& c : s1Copy)
			{
				c = std::tolower(c);
			}

			for (char& c : s2Copy)
			{
				c = std::tolower(c);
			}

			//returns bool if they're equal
			if (s1Copy.compare(s2Copy) == 0)
			{
				return true;
			}
		}

		return false;
	}

	std::string CreateUnique(const std::string& input)
	{
		static uint32_t unique = 0;

		return input + std::to_string(unique++);
	}
}
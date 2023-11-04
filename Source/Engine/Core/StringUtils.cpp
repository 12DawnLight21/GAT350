#include "StringUtils.h"
#include <cctype>

namespace nc
{
    unsigned int StringUtils::uniqueCounter = 0;

    string StringUtils::ToUpper(const string& input) {
        string result = input;
        for (char& u : result) { 
            u = toupper(u); 
        }
        return result;
    }

    string StringUtils::ToLower(const string& input) {
        string result = input;
        for (char& l : result) {
            l = tolower(l);
        }
        return result;
    }

    bool StringUtils::IsEqualIgnoreCase(const string& str1, const string& str2) {
        if (str1.length() != str2.length()) {
            return false;
        }

        for (size_t i = 0; i < str1.length(); ++i) {
            if (tolower(str1[i]) != tolower(str2[i])) {
                return false;
            }
        }

        return true;
    }

    string StringUtils::CreateUnique(const string& input) {
        string uniqueString = input + to_string(uniqueCounter++);
        return uniqueString;
    }
}

#pragma once

#include <vector>
#include <string>

namespace Utils
{
    std::string GetFileName(std::string path);

    std::vector<std::string> Split(std::string input, std::string pat);

    std::string Replace(std::string& source_string, std::string sub_string, const std::string new_string);

    std::string Replace(std::string& source_string, char target_char, const char new_char);

    std::string ToUpper(std::string& source_string);

} // namespace Utils

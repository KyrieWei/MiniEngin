#include "MetaUtils.h"
#include "Common/Precompiled.h"

namespace Utils
{
    std::string GetFileName(std::string path)
    {
        if(path.size() < 1)
        {
            return std::string();
        }

        std::vector<std::string> result = Split(path, "/");
        if(result.size() < 1)
        {
            return std::string();
        }

        return result[result.size() - 1];
    }

    std::vector<std::string> Split(std::string input, std::string pat)
    {
        std::vector<std::string> ret_list;
        while (true)
        {
            size_t index = input.find(pat);
            std::string sub_list = input.substr(0, index);
            if(!sub_list.empty())
            {
                ret_list.push_back(sub_list);
            }
            input.erase(0, index + pat.size());
            if(index == -1)
            {
                break;
            }
        }
        return ret_list;
    }

    std::string Replace(std::string& source_string, std::string sub_string, const std::string new_string)
    {
        std::string::size_type pos = 0;
        while ((pos = source_string.find(sub_string)) != std::string::npos)
        {
            source_string.replace(pos, sub_string.length(), new_string);
        }

        return source_string;
    }

    std::string Replace(std::string& source_string, char target_char, const char new_char)
    {
        std::replace(source_string.begin(), source_string.end(), target_char, new_char);
        return source_string;
    }

    std::string ToUpper(std::string& source_string)
    {
        std::transform(source_string.begin(), source_string.end(), source_string.begin(), ::toupper);
        return source_string;
    }

}
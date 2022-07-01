#include "MetaUtils.h"

namespace Utils
{
    std::vector<std::string> split(std::string input, std::string pat)
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
}
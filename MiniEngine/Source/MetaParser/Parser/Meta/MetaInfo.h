#pragma once

#include "Cursor/Cursor.h"


class MetaInfo
{
public:
    MetaInfo(const Cursor& cursor);
    MetaInfo(){}

    std::string GetProperty(const std::string& key) const;

    bool GetFlag(const std::string& key) const;

private:

    typedef std::pair<std::string, std::string> Property;

    std::unordered_map<std::string, std::string> m_properties;

private:
    std::vector<Property> ExtractProperties(const Cursor& cursor) const;
};
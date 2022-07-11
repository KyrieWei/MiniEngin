#pragma once

#include "Cursor/Cursor.h"

#include "Meta/MetaInfo.h"
#include "Parser/Parser.h"

class TypeInfo
{
public:
    TypeInfo(const Cursor& cursor, const std::vector<std::string>& current_namespace);
    virtual ~TypeInfo() {}

    const MetaInfo& GetMetaData() const;

    std::string GetSourceFile() const;
                
    std::vector<std::string> GetCurrentNamespace() const;

    Cursor& GetCursor();

protected:
    MetaInfo m_meta_data;

    bool m_enabled;

    std::string m_alias_cn;

    std::vector<std::string> m_namespace;

private:
    Cursor m_root_cursor;
};
#pragma once

#include "TypeInfo.h"

class Class;

class Field : public TypeInfo
{
public:
    Field(const Cursor& cursor, const std::vector<std::string>& current_namespace, Class* parent = nullptr);

    virtual ~Field() {}

    bool ShouldCompile() const;

public:
    bool m_is_const;

    Class* m_parent;

    std::string m_name;
    std::string m_display_name;
    std::string m_type;

    std::string m_default;

    bool IsAccessible() const;
};
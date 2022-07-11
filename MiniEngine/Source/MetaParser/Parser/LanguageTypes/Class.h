#pragma once

#include "TypeInfo.h"
#include "Field.h"

struct BaseClass
{
    BaseClass(const Cursor& cursor);

    std::string name;
};

class Class : public TypeInfo
{
    // to access m_qualifiedName
    friend class Field;
    friend class MetaParser;

public:
    Class(const Cursor& cursor, const std::vector<std::string>& current_namespace);

    virtual bool ShouldCompile() const;

    bool ShouldCompileFields() const;

    template<typename T>
    using SharedPtrVector = std::vector<std::shared_ptr<T>>;

    std::string GetClassName();

    SharedPtrVector<BaseClass> m_base_classes;

public:
    std::string m_name;

    std::string m_qualified_name;

    SharedPtrVector<Field> m_fields;

    std::string m_display_name;

    bool IsAccessible() const;

};
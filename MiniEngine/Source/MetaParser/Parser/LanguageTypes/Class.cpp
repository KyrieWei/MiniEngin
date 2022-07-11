#include "Common/Precompiled.h"
#include "Class.h"
#include <string>

BaseClass::BaseClass(const Cursor& cursor) : name(Utils::GetTypeNameWithoutNamespace(cursor.GetType())) {}

Class::Class(const Cursor& cursor, const std::vector<std::string>& current_namespace) : 
    TypeInfo(cursor, current_namespace), m_name(cursor.GetDisplayName()),
    m_qualified_name(Utils::GetTypeNameWithoutNamespace(cursor.GetType())),
    m_display_name(Utils::GetNameWithoutFirstM(m_qualified_name))
{
    Utils::ReplaceAll(m_name, " ", "");
    Utils::ReplaceAll(m_name, "MiniEngine::", "");

    for(auto& child : cursor.GetChildren())
    {
        switch (child.GetKind())
        {
        case CXCursor_CXXBaseSpecifier:
        {
            auto base_class = new BaseClass(child);
            m_base_classes.emplace_back(base_class);
        }
        break;

        case CXCursor_FieldDecl:
            m_fields.emplace_back(new Field(child, current_namespace, this));
            break;
        default:
            break;
        }
    }
}

bool Class::ShouldCompile() const { return ShouldCompileFields(); }

bool Class::ShouldCompileFields() const
{
    // return m_meta_data.GetFlag(NativeProperty::All) || m_meta_data.GetFlag(NativeProperty::Fields) ||
    //         m_meta_data.GetFlag(NativeProperty::WhiteListFields);

    return true;
}

std::string Class::GetClassName() { return m_name; }

bool Class::IsAccessible() const { return m_enabled; }
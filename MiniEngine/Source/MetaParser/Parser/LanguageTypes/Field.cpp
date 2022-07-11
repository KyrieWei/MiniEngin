#include "Common/Precompiled.h"

#include "Class.h"
#include "Field.h"

Field::Field(const Cursor& cursor, const std::vector<std::string>& current_namespace, Class* parent) :
    TypeInfo(cursor, current_namespace), m_is_const(cursor.GetType().IsConst()), m_parent(parent),
    m_name(cursor.GetSpelling()), m_display_name(Utils::GetNameWithoutFirstM(m_name)),
    m_type(Utils::GetTypeNameWithoutNamespace(cursor.GetType()))
{
    Utils::ReplaceAll(m_type, " ", "");
    Utils::ReplaceAll(m_type, "MiniEngine::", "");

    auto ret_string = Utils::GetStringWithoutQuot(m_meta_data.GetProperty("default"));
    m_default = ret_string;
}

bool Field::ShouldCompile() const { return IsAccessible(); }

bool Field::IsAccessible() const 
{
    return ((m_parent->m_meta_data.GetFlag(NativeProperty::Fields) ||
            m_parent->m_meta_data.GetFlag(NativeProperty::All)) &&
            !m_meta_data.GetFlag(NativeProperty::Disable)) ||
            (m_parent->m_meta_data.GetFlag(NativeProperty::WhiteListFields) &&
            m_meta_data.GetFlag(NativeProperty::Enable));
}
#include "Common/Precompiled.h"
#include "TypeInfo.h"

TypeInfo::TypeInfo(const Cursor& cursor, const std::vector<std::string>& current_namespace) :
    m_meta_data(cursor), m_enabled(m_meta_data.GetFlag(NativeProperty::Enable)), m_root_cursor(cursor), m_namespace(current_namespace)
{
    
}

const MetaInfo& TypeInfo::GetMetaData() const { return m_meta_data; }

std::string TypeInfo::GetSourceFile() const { return m_root_cursor.GetSourceFile(); }

std::vector<std::string> TypeInfo::GetCurrentNamespace() const { return m_namespace; }

Cursor& TypeInfo::GetCursor() { return m_root_cursor; }
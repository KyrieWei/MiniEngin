#include "Common/Precompiled.h"

#include "Cursor.h"
#include "CursorType.h"

CursorType::CursorType(const CXType& handle) : m_handle(handle) {}

std::string CursorType::GetDisplayName() const
{
    std::string display_name;

    Utils::ToString(clang_getTypeSpelling(m_handle), display_name);

    return display_name;
}

int CursorType::GetArgumentCount() const { return clang_getNumArgTypes(m_handle); }

CursorType CursorType::GetArgument(unsigned index) const { return clang_getArgType(m_handle, index); }

CursorType CursorType::GetCanonicalType() const { return clang_getCanonicalType(m_handle); }

Cursor CursorType::GetDeclaration() const { return clang_getTypeDeclaration(m_handle); }

CXTypeKind CursorType::GetKind() const { return m_handle.kind; }

bool CursorType::IsConst() const { return clang_isConstQualifiedType(m_handle) ? true : false; }
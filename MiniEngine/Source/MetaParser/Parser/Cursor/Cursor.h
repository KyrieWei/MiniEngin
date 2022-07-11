#pragma once

#include "CursorType.h"
#include <vector>

class Cursor
{
public:
    typedef std::vector<Cursor> List;

    typedef CXCursorVisitor Visitor;

    Cursor(const CXCursor& handle);

    CXCursorKind GetKind(void) const;

    std::string GetSpelling(void) const;
    std::string GetDisplayName(void) const;

    std::string GetSourceFile() const;

    bool IsDefinition(void) const;

    CursorType GetType(void) const;

    List GetChildren(void) const;

private:
    CXCursor m_handle;
};
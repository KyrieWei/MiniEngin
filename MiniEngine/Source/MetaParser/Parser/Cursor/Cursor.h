#pragma once

#include "CursorType.h"
#include <vector>

class Cursor
{
public:
    typedef std::vector<Cursor> List;

    typedef CXCursorVisitor Visitor;

    Cursor(const CXCursor& handle);

    List GetChildren(void) const;

private:
    CXCursor m_handle;
};
#include "Cursor.h"
#include "Common/Precompiled.h"

Cursor::Cursor(const CXCursor& handle) : m_handle(handle) {}

Cursor::List Cursor::GetChildren(void) const
{
    List children;

    auto visitor = [](CXCursor cursor, CXCursor parent, CXClientData data)
    {
        auto container = static_cast<List*>(data);
        container->emplace_back(cursor);
        if(cursor.kind == CXCursor_LastPreprocessing)
        {
            return CXChildVisit_Break;
        }

        return CXChildVisit_Continue;
    };

    clang_visitChildren(m_handle, visitor, &children);

    return children;
}
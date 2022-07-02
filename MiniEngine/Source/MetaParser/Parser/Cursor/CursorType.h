#pragma once
// #include "Common/Precompiled.h"
#include "clang-c/Index.h"

class Cursor;

class CursorType
{
public:
    CursorType(const CXType& handle);

private:
    CXType m_handle;
};
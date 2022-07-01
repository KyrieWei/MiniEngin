#pragma once
#include "Precompiled.h"

class Class;

struct SchemaModule
{
    std::string name;

    std::vector<std::shared_ptr<Class>> classess;
};

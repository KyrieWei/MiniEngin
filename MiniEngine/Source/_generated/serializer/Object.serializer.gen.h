#pragma once
#include "Runtime\Resource\ResType\Common\Object.h"

namespace ME{
    template<>
    PJson PSerializer::Write(const ComponentDefinitionRes& instance);
    template<>
    ComponentDefinitionRes& PSerializer::Read(const PJson& json_context, ComponentDefinitionRes& instance);
    template<>
    PJson PSerializer::Write(const ObjectDefinitionRes& instance);
    template<>
    ObjectDefinitionRes& PSerializer::Read(const PJson& json_context, ObjectDefinitionRes& instance);
    template<>
    PJson PSerializer::Write(const ObjectInstanceRes& instance);
    template<>
    ObjectInstanceRes& PSerializer::Read(const PJson& json_context, ObjectInstanceRes& instance);
}//namespace


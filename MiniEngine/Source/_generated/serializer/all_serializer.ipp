#pragma once
#include "_generated\serializer\Object.serializer.gen.h"
#include "_generated\serializer\Vector3.serializer.gen.h"
#include "_generated\serializer\World.serializer.gen.h"
#include "_generated\serializer\Matrix4.serializer.gen.h"
#include "_generated\serializer\Vector2.serializer.gen.h"
#include "_generated\serializer\Quaternion.serializer.gen.h"
#include "_generated\serializer\Vector4.serializer.gen.h"
#include "_generated\serializer\RenderObject.serializer.gen.h"
#include "_generated\serializer\Level.serializer.gen.h"
namespace ME{
    template<>
    PJson PSerializer::Write(const ComponentDefinitionRes& instance){
        PJson::object  ret_context;
        
        
        return  PJson(ret_context);
    }
    template<>
    ComponentDefinitionRes& PSerializer::Read(const PJson& json_context, ComponentDefinitionRes& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    PJson PSerializer::Write(const ObjectDefinitionRes& instance){
        PJson::object  ret_context;
        
        
        return  PJson(ret_context);
    }
    template<>
    ObjectDefinitionRes& PSerializer::Read(const PJson& json_context, ObjectDefinitionRes& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    PJson PSerializer::Write(const ObjectInstanceRes& instance){
        PJson::object  ret_context;
        
        
        return  PJson(ret_context);
    }
    template<>
    ObjectInstanceRes& PSerializer::Read(const PJson& json_context, ObjectInstanceRes& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    PJson PSerializer::Write(const Vector3& instance){
        PJson::object  ret_context;
        
        
        return  PJson(ret_context);
    }
    template<>
    Vector3& PSerializer::Read(const PJson& json_context, Vector3& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    PJson PSerializer::Write(const WorldRes& instance){
        PJson::object  ret_context;
        
        
        return  PJson(ret_context);
    }
    template<>
    WorldRes& PSerializer::Read(const PJson& json_context, WorldRes& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    PJson PSerializer::Write(const Matrix4x4_& instance){
        PJson::object  ret_context;
        
        
        return  PJson(ret_context);
    }
    template<>
    Matrix4x4_& PSerializer::Read(const PJson& json_context, Matrix4x4_& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    PJson PSerializer::Write(const Vector2& instance){
        PJson::object  ret_context;
        
        
        return  PJson(ret_context);
    }
    template<>
    Vector2& PSerializer::Read(const PJson& json_context, Vector2& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    PJson PSerializer::Write(const Quaternion& instance){
        PJson::object  ret_context;
        
        
        return  PJson(ret_context);
    }
    template<>
    Quaternion& PSerializer::Read(const PJson& json_context, Quaternion& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    PJson PSerializer::Write(const Vector4& instance){
        PJson::object  ret_context;
        
        
        return  PJson(ret_context);
    }
    template<>
    Vector4& PSerializer::Read(const PJson& json_context, Vector4& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    PJson PSerializer::Write(const GameObjectMeshDesc& instance){
        PJson::object  ret_context;
        
        
        return  PJson(ret_context);
    }
    template<>
    GameObjectMeshDesc& PSerializer::Read(const PJson& json_context, GameObjectMeshDesc& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    PJson PSerializer::Write(const GameObjectPartDesc& instance){
        PJson::object  ret_context;
        
        
        return  PJson(ret_context);
    }
    template<>
    GameObjectPartDesc& PSerializer::Read(const PJson& json_context, GameObjectPartDesc& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }
    template<>
    PJson PSerializer::Write(const LevelRes& instance){
        PJson::object  ret_context;
        
        
        return  PJson(ret_context);
    }
    template<>
    LevelRes& PSerializer::Read(const PJson& json_context, LevelRes& instance){
        assert(json_context.is_object());
        
        
        return instance;
    }

}


#pragma once
#include "Runtime\Function\Render\RenderObject.h"

namespace ME{
    class GameObjectMeshDesc;
    class GameObjectPartDesc;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeGameObjectMeshDescOperator{
    public:
        static const char* GetClassName(){ return "GameObjectMeshDesc";}
        static void* ConstructorWithJson(const PJson& json_context){
            GameObjectMeshDesc* ret_instance= new GameObjectMeshDesc;
            PSerializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static PJson WriteByName(void* instance){
            return PSerializer::Write(*(GameObjectMeshDesc*)instance);
        }
        // base class
        static int GetGameObjectMeshDescBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_GameObjectMeshDesc(){
        
        
        
        ClassFunctionTuple* f_class_function_tuple_GameObjectMeshDesc=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeGameObjectMeshDescOperator::getGameObjectMeshDescBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeGameObjectMeshDescOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeGameObjectMeshDescOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("GameObjectMeshDesc", f_class_function_tuple_GameObjectMeshDesc);
    }namespace TypeFieldReflectionOparator{
    class TypeGameObjectPartDescOperator{
    public:
        static const char* GetClassName(){ return "GameObjectPartDesc";}
        static void* ConstructorWithJson(const PJson& json_context){
            GameObjectPartDesc* ret_instance= new GameObjectPartDesc;
            PSerializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static PJson WriteByName(void* instance){
            return PSerializer::Write(*(GameObjectPartDesc*)instance);
        }
        // base class
        static int GetGameObjectPartDescBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_GameObjectPartDesc(){
        
        
        
        ClassFunctionTuple* f_class_function_tuple_GameObjectPartDesc=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::getGameObjectPartDescBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeGameObjectPartDescOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("GameObjectPartDesc", f_class_function_tuple_GameObjectPartDesc);
    }
namespace TypeWrappersRegister{
        void GameObjectMeshDesc(){ TypeWrapperRegister_GameObjectMeshDesc();}
        void GameObjectPartDesc(){ TypeWrapperRegister_GameObjectPartDesc();}
}//namespace TypeWrappersRegister

}//namespace Reflection
}//namespace ME


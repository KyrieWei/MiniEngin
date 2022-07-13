#pragma once
#include "Runtime\Core\Math\Vector2.h"

namespace ME{
    class Vector2;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeVector2Operator{
    public:
        static const char* GetClassName(){ return "Vector2";}
        static void* ConstructorWithJson(const PJson& json_context){
            Vector2* ret_instance= new Vector2;
            PSerializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static PJson WriteByName(void* instance){
            return PSerializer::Write(*(Vector2*)instance);
        }
        // base class
        static int GetVector2BaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Vector2(){
        
        
        
        ClassFunctionTuple* f_class_function_tuple_Vector2=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeVector2Operator::getVector2BaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeVector2Operator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeVector2Operator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("Vector2", f_class_function_tuple_Vector2);
    }
namespace TypeWrappersRegister{
        void Vector2(){ TypeWrapperRegister_Vector2();}
}//namespace TypeWrappersRegister

}//namespace Reflection
}//namespace ME


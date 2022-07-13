#pragma once
#include "Runtime\Core\Math\Quaternion.h"

namespace ME{
    class Quaternion;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeQuaternionOperator{
    public:
        static const char* GetClassName(){ return "Quaternion";}
        static void* ConstructorWithJson(const PJson& json_context){
            Quaternion* ret_instance= new Quaternion;
            PSerializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static PJson WriteByName(void* instance){
            return PSerializer::Write(*(Quaternion*)instance);
        }
        // base class
        static int GetQuaternionBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Quaternion(){
        
        
        
        ClassFunctionTuple* f_class_function_tuple_Quaternion=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeQuaternionOperator::getQuaternionBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeQuaternionOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeQuaternionOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("Quaternion", f_class_function_tuple_Quaternion);
    }
namespace TypeWrappersRegister{
        void Quaternion(){ TypeWrapperRegister_Quaternion();}
}//namespace TypeWrappersRegister

}//namespace Reflection
}//namespace ME


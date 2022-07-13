#pragma once
#include "Runtime\Resource\ResType\Common\World.h"

namespace ME{
    class WorldRes;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeWorldResOperator{
    public:
        static const char* GetClassName(){ return "WorldRes";}
        static void* ConstructorWithJson(const PJson& json_context){
            WorldRes* ret_instance= new WorldRes;
            PSerializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static PJson WriteByName(void* instance){
            return PSerializer::Write(*(WorldRes*)instance);
        }
        // base class
        static int GetWorldResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLstdSSstringROperatorMACRO
#define ArraystdSSvectorLstdSSstringROperatorMACRO
    class ArraystdSSvectorLstdSSstringROperator{
        public:
            static const char* GetArrayTypeName(){ return "std::vector<std::string>";}
            static const char* GetElementTypeName(){ return "std::string";}
            static int GetSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<std::string>*>(instance)->size());
            }
            static void* Get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<std::string>*>(instance))[index]));
            }
            static void Set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<std::string>*>(instance))[index] = *static_cast<std::string*>(element_value);
            }
    };
#endif //ArraystdSSvectorLstdSSstringROperator
}//namespace ArrayReflectionOperator

    void TypeWrapperRegister_WorldRes(){
        
        
        ArrayFunctionTuple* f_array_tuple_stdSSvectorLstdSSstringR = new  ArrayFunctionTuple(
            &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::set,
            &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::get,
            &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::getSize,
            &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::getArrayTypeName,
            &ArrayReflectionOperator::ArraystdSSvectorLstdSSstringROperator::getElementTypeName);
        REGISTER_ARRAY_TO_MAP("std::vector<std::string>", f_array_tuple_stdSSvectorLstdSSstringR);
        ClassFunctionTuple* f_class_function_tuple_WorldRes=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeWorldResOperator::getWorldResBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeWorldResOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeWorldResOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("WorldRes", f_class_function_tuple_WorldRes);
    }
namespace TypeWrappersRegister{
        void WorldRes(){ TypeWrapperRegister_WorldRes();}
}//namespace TypeWrappersRegister

}//namespace Reflection
}//namespace ME


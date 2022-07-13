#pragma once
#include "Runtime\Resource\ResType\Common\Object.h"

namespace ME{
    class ComponentDefinitionRes;
    class ObjectDefinitionRes;
    class ObjectInstanceRes;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeComponentDefinitionResOperator{
    public:
        static const char* GetClassName(){ return "ComponentDefinitionRes";}
        static void* ConstructorWithJson(const PJson& json_context){
            ComponentDefinitionRes* ret_instance= new ComponentDefinitionRes;
            PSerializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static PJson WriteByName(void* instance){
            return PSerializer::Write(*(ComponentDefinitionRes*)instance);
        }
        // base class
        static int GetComponentDefinitionResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_ComponentDefinitionRes(){
        
        
        
        ClassFunctionTuple* f_class_function_tuple_ComponentDefinitionRes=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeComponentDefinitionResOperator::getComponentDefinitionResBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeComponentDefinitionResOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeComponentDefinitionResOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("ComponentDefinitionRes", f_class_function_tuple_ComponentDefinitionRes);
    }namespace TypeFieldReflectionOparator{
    class TypeObjectDefinitionResOperator{
    public:
        static const char* GetClassName(){ return "ObjectDefinitionRes";}
        static void* ConstructorWithJson(const PJson& json_context){
            ObjectDefinitionRes* ret_instance= new ObjectDefinitionRes;
            PSerializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static PJson WriteByName(void* instance){
            return PSerializer::Write(*(ObjectDefinitionRes*)instance);
        }
        // base class
        static int GetObjectDefinitionResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperatorMACRO
#define ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperatorMACRO
    class ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator{
        public:
            static const char* GetArrayTypeName(){ return "std::vector<Reflection::ReflectionPtr<Component>>";}
            static const char* GetElementTypeName(){ return "Reflection::ReflectionPtr<Component>";}
            static int GetSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<Reflection::ReflectionPtr<Component>>*>(instance)->size());
            }
            static void* Get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<Reflection::ReflectionPtr<Component>>*>(instance))[index]));
            }
            static void Set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<Reflection::ReflectionPtr<Component>>*>(instance))[index] = *static_cast<Reflection::ReflectionPtr<Component>*>(element_value);
            }
    };
#endif //ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator
}//namespace ArrayReflectionOperator

    void TypeWrapperRegister_ObjectDefinitionRes(){
        
        
        ArrayFunctionTuple* f_array_tuple_stdSSvectorLReflectionSSReflectionPtrLComponentRR = new  ArrayFunctionTuple(
            &ArrayReflectionOperator::ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator::set,
            &ArrayReflectionOperator::ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator::get,
            &ArrayReflectionOperator::ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator::getSize,
            &ArrayReflectionOperator::ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator::getArrayTypeName,
            &ArrayReflectionOperator::ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator::getElementTypeName);
        REGISTER_ARRAY_TO_MAP("std::vector<Reflection::ReflectionPtr<Component>>", f_array_tuple_stdSSvectorLReflectionSSReflectionPtrLComponentRR);
        ClassFunctionTuple* f_class_function_tuple_ObjectDefinitionRes=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeObjectDefinitionResOperator::getObjectDefinitionResBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeObjectDefinitionResOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeObjectDefinitionResOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("ObjectDefinitionRes", f_class_function_tuple_ObjectDefinitionRes);
    }namespace TypeFieldReflectionOparator{
    class TypeObjectInstanceResOperator{
    public:
        static const char* GetClassName(){ return "ObjectInstanceRes";}
        static void* ConstructorWithJson(const PJson& json_context){
            ObjectInstanceRes* ret_instance= new ObjectInstanceRes;
            PSerializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static PJson WriteByName(void* instance){
            return PSerializer::Write(*(ObjectInstanceRes*)instance);
        }
        // base class
        static int GetObjectInstanceResBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 0;
            
            return count;
        }
        // fields
        
    };
}//namespace TypeFieldReflectionOparator
namespace ArrayReflectionOperator{
#ifndef ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperatorMACRO
#define ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperatorMACRO
    class ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator{
        public:
            static const char* GetArrayTypeName(){ return "std::vector<Reflection::ReflectionPtr<Component>>";}
            static const char* GetElementTypeName(){ return "Reflection::ReflectionPtr<Component>";}
            static int GetSize(void* instance){
                //todo: should check validation
                return static_cast<int>(static_cast<std::vector<Reflection::ReflectionPtr<Component>>*>(instance)->size());
            }
            static void* Get(int index,void* instance){
                //todo: should check validation
                return static_cast<void*>(&((*static_cast<std::vector<Reflection::ReflectionPtr<Component>>*>(instance))[index]));
            }
            static void Set(int index, void* instance, void* element_value){
                //todo: should check validation
                (*static_cast<std::vector<Reflection::ReflectionPtr<Component>>*>(instance))[index] = *static_cast<Reflection::ReflectionPtr<Component>*>(element_value);
            }
    };
#endif //ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator
}//namespace ArrayReflectionOperator

    void TypeWrapperRegister_ObjectInstanceRes(){
        
        
        ArrayFunctionTuple* f_array_tuple_stdSSvectorLReflectionSSReflectionPtrLComponentRR = new  ArrayFunctionTuple(
            &ArrayReflectionOperator::ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator::set,
            &ArrayReflectionOperator::ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator::get,
            &ArrayReflectionOperator::ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator::getSize,
            &ArrayReflectionOperator::ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator::getArrayTypeName,
            &ArrayReflectionOperator::ArraystdSSvectorLReflectionSSReflectionPtrLComponentRROperator::getElementTypeName);
        REGISTER_ARRAY_TO_MAP("std::vector<Reflection::ReflectionPtr<Component>>", f_array_tuple_stdSSvectorLReflectionSSReflectionPtrLComponentRR);
        ClassFunctionTuple* f_class_function_tuple_ObjectInstanceRes=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeObjectInstanceResOperator::getObjectInstanceResBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeObjectInstanceResOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeObjectInstanceResOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("ObjectInstanceRes", f_class_function_tuple_ObjectInstanceRes);
    }
namespace TypeWrappersRegister{
        void ComponentDefinitionRes(){ TypeWrapperRegister_ComponentDefinitionRes();}
        void ObjectDefinitionRes(){ TypeWrapperRegister_ObjectDefinitionRes();}
        void ObjectInstanceRes(){ TypeWrapperRegister_ObjectInstanceRes();}
}//namespace TypeWrappersRegister

}//namespace Reflection
}//namespace ME


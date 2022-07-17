#pragma once

#include "Runtime/Core/Meta/Json.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace ME
{
#if defined(__REFLECTION_PARSER__)
#define META(...) __attribute__((annotate(#__VA_ARGS__)))
#define CLASS(class_name, ...) class __attribute__((annotate(#__VA_ARGS__))) class_name
#define STRUCT(struct_name, ...) struct __attribute__((annotate(#__VA_ARGS__))) struct_name
#else
#define META(...)
#define CLASS(class_name, ...) class class_name
#define STRUCT(struct_name, ...) struct struct_name
#endif

#define REFLECTION_BODY(class_name) \
	friend class Reflection::TypeFieldReflectionOperator::Type##class_name##Operator; \
	friend class PSerializer;

#define REFLECTION_TYPE(class_name) \
	namespace Reflection \
	{ \
		namespace TypeFieldReflectionOperator \
		{ \
			class Type##class_name##Operator; \
		} \
	};

#define REGISTER_FIELD_TO_MAP(name, value) TypeMetaRegisterInterface::RegisterToFieldMap(name, value);
#define REGISTER_BASE_CLASS_TO_MAP(name, value) TypeMetaRegisterInterface::RegisterToClassMap(name, value);
#define REGISTER_ARRAY_TO_MAP(name, value) TypeMetaRegisterInterface::RegisterToArrayMap(name, value);
#define UNREGISTER_ALL TypeMetaRegisterInterface::UnregisterAll();

	namespace Reflection
	{
		class TypeMeta;
		class FieldAccessor;
		class ArrayAccessor;
		class ReflectionInstance;
	}

	typedef std::function<void(void*, void*)>		SetFunction;
	typedef std::function<void* (void*)>			GetFunction;
	typedef std::function<const char* ()>			GetNameFunction;
	typedef std::function<void(int, void*, void*)>	SetArrayFunc;
	typedef std::function<void* (int, void*)>		GetArrayFunc;
	typedef std::function<int(void*)>				GetSizeFunc;
	typedef std::function<bool()>					GetBoolFunc;

	typedef std::function<void* (const PJson&)>		ConstructorWithPJson;
	typedef std::function<PJson(void*)>				WritePJsonByName;
	typedef std::function<int(Reflection::ReflectionInstance*&, void*)> GetBaseClassReflectionInstanceListFunc;

	typedef std::tuple<SetFunction, GetFunction, GetNameFunction, GetNameFunction, GetNameFunction, GetBoolFunc> FieldFunctionTuple;
	typedef std::tuple<GetBaseClassReflectionInstanceListFunc, ConstructorWithPJson, WritePJsonByName> ClassFunctionTuple;
	typedef std::tuple<SetArrayFunc, GetArrayFunc, GetSizeFunc, GetNameFunction, GetNameFunction> ArrayFunctionTuple;


	namespace Reflection
	{

		class TypeMetaRegisterInterface
		{
		public:
			static void RegisterToClassMap(const char* name, ClassFunctionTuple* value);
			static void RegisterToFieldMap(const char* name, FieldFunctionTuple* value);
			static void RegisterToArrayMap(const char* name, ArrayFunctionTuple* value);

			static void UnregisterAll();
		};

		class TypeMeta
		{
			friend class FieldAccessor;
			friend class ArrayAccessor;
			friend class TypeMetaRegisterInterface;

		public:
			TypeMeta();

			static TypeMeta NewMetaFromName(std::string type_name);

			static bool NewArrayAccessorFromName(std::string array_type_name, ArrayAccessor& accessor);
			static ReflectionInstance NewFromNameAndPJson(std::string type_name, const PJson& json_context);
			static PJson WriteByName(std::string type_name, void* instance);

			std::string GetTypeName();

			int GetFieldsList(FieldAccessor*& out_list);

			int GetBaseClassReflectionInstanceList(ReflectionInstance*& out_list, void* instance);

			FieldAccessor GetFieldByName(const char* name);

			bool IsValid() { return m_is_valid; }

			TypeMeta& operator=(const TypeMeta& dest);

		private:
			TypeMeta(std::string type_name);

		private:
			std::vector<FieldAccessor, std::allocator<FieldAccessor>> m_fields;

			std::string m_type_name;

			bool m_is_valid;
		};

		class FieldAccessor
		{
			friend class TypeMeta;

		public:
			FieldAccessor();

			void* Get(void* instance);
			void  Set(void* instance, void* value);

			TypeMeta GetOwnerTypeMeta();

			bool GetTypeMeta(TypeMeta& field_type);
			const char* GetFieldName() const;
			const char* GetFieldTypeName();
			bool		IsArrayType();

			FieldAccessor& operator=(const FieldAccessor& dest);

		private:
			FieldAccessor(FieldFunctionTuple* functions);

		private:
			FieldFunctionTuple* m_functions;
			const char* m_field_name;
			const char* m_field_type_name;
		};

		class ArrayAccessor
		{
			friend class TypeMeta;

		public:
			ArrayAccessor();
			const char* GetArrayTypeName(); 
			const char* GetElementTypeName();
			void		Set(int index, void* instance, void* element_value);

			void* Get(int index, void* instance);
			int	  GetSize(void* instance);

			ArrayAccessor& operator=(ArrayAccessor& dest);

		private:
			ArrayAccessor(ArrayFunctionTuple* array_func);

		private:

			ArrayFunctionTuple* m_func;
			const char* m_array_type_name;
			const char* m_element_type_name;
		};

		class ReflectionInstance
		{
		public:
			ReflectionInstance(TypeMeta meta, void* instance) : m_meta(meta), m_instance(instance) {}
			ReflectionInstance() : m_meta(), m_instance(nullptr) {}

			ReflectionInstance& operator=(ReflectionInstance& dest);

			ReflectionInstance& operator=(ReflectionInstance&& dest);

		private:
			TypeMeta m_meta;
			void* m_instance;
		};



		template<typename T>
		class ReflectionPtr
		{
			template<typename U>
			friend class ReflectionPtr;

		public:
			ReflectionPtr(std::string type_name, T* instance) : m_type_name(type_name), m_instance(instance) {}
			ReflectionPtr() : m_type_name(), m_instance(nullptr) {}

			ReflectionPtr(const ReflectionPtr& dest) : m_type_name(dest.m_type_name), m_instance(dest.m_instance) {}

			template<typename U>
			ReflectionPtr<T>& operator=(const ReflectionPtr<U>& dest)
			{
				if (this == static_cast<void*>(&dest))
				{
					return *this;
				}

				m_type_name = dest.m_type_name;
				m_instance = static_cast<T*>(dest.m_instance);
				return *this;
			}

			template<typename U>
			ReflectionPtr<T>& operator=(ReflectionPtr<U>&& dest)
			{
				if (this == static_cast<void*>(&dest))
				{
					return *this;
				}

				m_type_name = dest.m_type_name;
				m_instance = static_cast<T*>(dest.m_instance);
				return *this;
			}

			ReflectionPtr<T>& operator=(const ReflectionPtr<T>& dest)
			{
				if (this == &dest)
				{
					return *this;
				}

				m_type_name = dest.m_type_name;
				m_instance = dest.m_instance;
				return *this;
			}

			ReflectionPtr<T>& operator=(ReflectionPtr<T>&& dest)
			{
				if (this == &dest)
				{
					return *this;
				}

				m_type_name = dest.m_type_name;
				m_instance = dest.m_instance;
				return *this;
			}

			std::string GetTypeName() const { return m_type_name; }

			void SetTypeName(std::string name) { m_type_name = name; }

			bool operator==(const T* ptr) const { return (m_instance == ptr); }

			bool operator!=(const T* ptr) const { return (m_instance != ptr); }

			bool operator==(const ReflectionPtr<T>& rhs_ptr) const { return m_instance == rhs_ptr.m_instance; }

			bool operator!=(const ReflectionPtr<T>& rhs_ptr) const { return m_instance != rhs_ptr.m_instance; }

			template<typename T1>
			explicit operator T1* ()
			{
				return static_cast<T1*>(m_instance);
			}

			template<typename T1>
			operator ReflectionPtr<T1>()
			{
				return ReflectionPtr<T1>(m_type_name, (T1*)(m_instance));
			}

			template<typename T1>
			explicit operator const T1* () const
			{
				return static_cast<T1*>(m_instance);
			}

			template<typename T1>
			operator const ReflectionPtr<T1>() const
			{
				return ReflectionPtr<T1>(m_type_name, (T1*)(m_instance));
			}

			T* operator->() { return m_instance; }

			T* operator->() const { return m_instance; }

			T& operator*() { return *(m_instance); }

			T* GetPtr() { return m_instance; }

			T* GetPtr() const { return m_instance; }

			const T& operator*() const { return *(static_cast<const T*>(m_instance)); }

			T*& GetPtrReference() { return m_instance; }

			operator bool() const { return (m_instance != nullptr); }

		private:
			std::string m_type_name{ "" };
			typedef T m_type;
			T* m_instance{ nullptr };
		};
	
	}

} //namespace MiniEngine
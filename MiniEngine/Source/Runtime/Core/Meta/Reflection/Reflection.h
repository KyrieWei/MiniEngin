#pragma once

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

	namespace Reflection
	{
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
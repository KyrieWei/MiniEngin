#include "Serializer.h"
#include <assert.h>

namespace ME
{
	template<>
	PJson PSerializer::Write(const char& instance)
	{
		return PJson(instance);
	}

	template<>
	char& PSerializer::Read(const PJson& json_context, char& instance)
	{
		assert(json_context.is_number());
		return instance = json_context.number_value();
	}

	template<>
	PJson PSerializer::Write(const int& instance)
	{
		return PJson(instance);
	}

	template<>
	int& PSerializer::Read(const PJson& json_context, int& instance)
	{
		assert(json_context.is_number());
		return instance = static_cast<int>(json_context.number_value());
	}

	template<>
	PJson PSerializer::Write(const unsigned int& instance)
	{
		return PJson(static_cast<int>(instance));
	}

	template<>
	unsigned int& PSerializer::Read(const PJson& json_context, unsigned int& instance)
	{
		assert(json_context.is_number());
		return instance = static_cast<unsigned int>(json_context.number_value());
	}

	template<>
	PJson PSerializer::Write(const float& instance)
	{
		return PJson(instance);
	}

	template<>
	float& PSerializer::Read(const PJson& json_context, float& instance)
	{
		assert(json_context.is_number());
		return instance = static_cast<float>(json_context.number_value());
	}

	template<>
	PJson PSerializer::Write(const double& instance)
	{
		return PJson(instance);
	}

	template<>
	double& PSerializer::Read(const PJson& json_context, double& instance)
	{
		assert(json_context.is_number());
		return instance = static_cast<float>(json_context.number_value());
	}

	template<>
	PJson PSerializer::Write(const bool& instance)
	{
		return PJson(instance);
	}

	template<>
	bool& PSerializer::Read(const PJson& json_context, bool& instance)
	{
		assert(json_context.is_bool());
		return instance = json_context.bool_value();
	}

	template<>
	PJson PSerializer::Write(const std::string& instance)
	{
		return PJson(instance);
	}

	template<>
	std::string& PSerializer::Read(const PJson& json_context, std::string& instance)
	{
		assert(json_context.is_string());
		return instance = json_context.string_value();
	}
}
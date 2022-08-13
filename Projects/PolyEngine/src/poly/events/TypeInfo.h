#pragma once
#include <typeinfo>

class TypeInfo {
public:
	TypeInfo(const std::type_info* info): info(info) {}

	const std::type_info* get() {
		return info;
	}

	bool operator==(const TypeInfo& other) const
	{
		return info == other.info;
	}

	struct HashFunction
	{
		size_t operator()(const TypeInfo& type) const
		{
			return type.info->hash_code();
		}
	};
private:
	const std::type_info* info;
};
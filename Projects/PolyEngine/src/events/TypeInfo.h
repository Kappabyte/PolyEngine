#pragma once
#include <typeinfo>

class TypeInfo {
public:
	TypeInfo(const std::type_info* info): info(info) {}

	const std::type_info* get() {
		return info;
	}

	bool operator< (const TypeInfo& object) const
	{
		return object.info != info;
	}
private:
	const std::type_info* info;
};
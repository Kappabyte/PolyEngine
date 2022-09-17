#pragma once
#include <typeinfo>
#include <cstdio>

class TypeInfo {
public:
    TypeInfo(const std::type_info* info): info(info) {}

    const std::type_info * get() const {
        return info;
    }

    bool operator==(const TypeInfo& other) const
    {
        return info->hash_code() == other.info->hash_code();
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
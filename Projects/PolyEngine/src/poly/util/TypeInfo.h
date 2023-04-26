#pragma once
#include <typeinfo>
#include <cstdio>

#define Type(x) TypeInfo(&typeid(x))

class TypeInfo {
public:
    explicit TypeInfo(const std::type_info* info): m_info(info) {}

    [[nodiscard]] const std::type_info * get() const {
        return m_info;
    }

    bool operator==(const TypeInfo& other) const
    {
        return m_info->hash_code() == other.m_info->hash_code();
    }

    struct HashFunction
    {
        size_t operator()(const TypeInfo& type) const
        {
            return type.m_info->hash_code();
        }
    };
private:
    const std::type_info* m_info;
};
#pragma once

#include <string>

namespace Poly {
    class NamespaceId {
    public:
        NamespaceId(const std::string& identifier); // NOLINT(google-explicit-constructor)
        NamespaceId(const char* identifier): NamespaceId(std::string(identifier)) {}; // NOLINT(google-explicit-constructor)
        NamespaceId(std::string n, std::string i);

        [[nodiscard]] std::string getNamespace() const;
        [[nodiscard]] std::string getIdentifier() const;

        [[nodiscard]] std::string toString() const;

        bool operator==(const NamespaceId& other) const;
    private:
        std::string m_namespace;
        std::string m_identifier;
    };
}
namespace std {

    template <>
    struct [[maybe_unused]] hash<Poly::NamespaceId>
    {
        std::size_t operator()(Poly::NamespaceId k) const
        {
            // Compute individual hash values for first, second and third
            // http://stackoverflow.com/a/1646913/126995
            size_t res = 17;
            res = res * 31 + hash<string>()(k.getNamespace());
            res = res * 31 + hash<string>()(k.getIdentifier());
            return res;
        }
    };

}


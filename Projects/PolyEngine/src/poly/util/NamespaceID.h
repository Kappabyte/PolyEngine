//
// Created by avery on 2022-09-20.
//

#pragma once

#include <string>

namespace Poly {
    class NamespaceID {
    public:
        NamespaceID(const std::string& identifier); // NOLINT(google-explicit-constructor)
        NamespaceID(const char* identifier): NamespaceID(std::string(identifier)) {}; // NOLINT(google-explicit-constructor)
        NamespaceID(std::string _namespace, std::string _identifier);

        std::string getNamespace();
        std::string getIdentifier();

        [[nodiscard]] std::string toString() const;

        bool operator==(const NamespaceID& other) const;
    private:
        std::string _namespace;
        std::string _identifier;
    };
}
namespace std {

    template <>
    struct hash<Poly::NamespaceID>
    {
        std::size_t operator()(Poly::NamespaceID k) const
        {
            // Compute individual hash values for first, second and third
            // http://stackoverflow.com/a/1646913/126995
            size_t res = 17;
            res = res * 31 + hash<string>()( k.getNamespace() );
            res = res * 31 + hash<string>()( k.getIdentifier() );
            return res;
        }
    };

}


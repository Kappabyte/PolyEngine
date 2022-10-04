//
// Created by avery on 2022-09-20.
//

#include "NamespaceID.h"

#include <utility>
#include <stdexcept>

namespace Poly {
    NamespaceID::NamespaceID(const std::string& identifier) {
        uint8_t colonCount = std::count(identifier.begin(), identifier.end(), ':');
        if(colonCount == 1) {
            std::string::size_type colonPos = identifier.find(':');
            _namespace = identifier.substr(0, colonPos);
            _identifier = identifier.substr(colonPos + 1);
        } else if(colonCount == 0) {
            _namespace = "poly";
            _identifier = identifier;
        } else {
            throw std::runtime_error("Invalid NamespaceID: " + _identifier);
        }
    }

    NamespaceID::NamespaceID(std::string _namespace, std::string _identifier): _namespace(std::move(_namespace)), _identifier(std::move(_identifier)) {
    }

    std::string NamespaceID::getNamespace() {
        return _namespace;
    }

    std::string NamespaceID::getIdentifier() {
        return _identifier;
    }

    std::string NamespaceID::toString() const {
        return _namespace + ":" + _identifier;
    }

    bool NamespaceID::operator==(const NamespaceID &other) const {
        return _namespace == other._namespace && _identifier == other._identifier;
    }
}
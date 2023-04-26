#include "NamespaceId.h"

#include <utility>
#include <stdexcept>
#include <regex>
#include "poly/util/Log.h"


namespace Poly {
    NamespaceId::NamespaceId(const std::string& identifier) {
        uint8_t colonCount = std::count(identifier.begin(), identifier.end(), ':');

        std::basic_regex reg = std::basic_regex("^[a-z_:]+");

        ASSERT(std::regex_match(identifier, reg) || colonCount > 1, "Invalid namespaceID: " + identifier);

        if(colonCount == 1) {
            std::string::size_type colonPos = identifier.find(':');
            m_namespace = identifier.substr(0, colonPos);
            m_identifier = identifier.substr(colonPos + 1);
        } else {
            m_namespace = "poly";
            m_identifier = identifier;
        }
    }

    NamespaceId::NamespaceId(std::string _namespace, std::string ListenerListidentifier): m_namespace(std::move(_namespace)), m_identifier(std::move(ListenerListidentifier)) {
    }

    std::string NamespaceId::getNamespace() const {
        return m_namespace;
    }

    std::string NamespaceId::getIdentifier() const {
        return m_identifier;
    }

    std::string NamespaceId::toString() const {
        return m_namespace + ":" + m_identifier;
    }

    bool NamespaceId::operator==(const NamespaceId &other) const {
        return m_namespace == other.m_namespace && m_identifier == other.m_identifier;
    }
}
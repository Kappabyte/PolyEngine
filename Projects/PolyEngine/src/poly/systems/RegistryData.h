#pragma once
#include <nlohmann/json.hpp>
#include <utility>
using Json = nlohmann::json;

namespace Poly {
    
    class RegistryDataBase {
    
    };
    
    template <typename DataType>
    class RegistryData : RegistryDataBase {
    public:
        explicit RegistryData(std::string path): m_path(path) {}
    
        DataType getData() {
            if(m_stale) {
                m_cachedData = loadData();
            }
            
            return m_cachedData;
        }
        
        void markStale() {
            m_stale = true;
        }
        
    protected:
        virtual DataType loadData() = 0;
        
        const std::string m_path;
    private:
        bool m_stale = true;
        
        DataType m_cachedData;
        
    };
    
    class JsonRegistryData : public RegistryData<Json> {
    public:
        JsonRegistryData();
    
        explicit JsonRegistryData(std::string path): RegistryData(std::move(path)) {};
        
    protected:
        Json loadData() override;
    };
}

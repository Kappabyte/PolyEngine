#pragma once
#include <unordered_map>
#include "poly/util/TypeInfo.h"
#include "poly/util/Ref.h"
#include "poly/util/NamespaceId.h"
#include <regex>
#include <unordered_set>
#include <filesystem>
#include <iostream>
#include "RegistryData.h"
#include <poly/util/Log.h>

std::basic_regex pathRegex = std::basic_regex("^([a-z]+/)+[a-z]+$");

std::string gameDataPath = "gamedata";

std::string getAbsolutePath(std::string ns, std::string path) {
    return gameDataPath + "/" + ns + "/" + path;
}

namespace Poly {
    
    /**
     * A collection of data files. Data files can be in multiple places, including on the physical filesystem, in a resource bundle, or in memory.
     */
    template <typename DataType>
    class Registry {
    public:
        
        /**
         * Get a registry from a path.
         * @param path The path of the registry.
         * </ul>
         * @return
         */
        static Shared<Registry<DataType>> getRegistry(const std::string& path) {
            //ASSERT(, "Invalid registry path.");
            if(!std::regex_match(path, pathRegex)) {spdlog::error("Assertion failed: {0}", "a"); __debugbreak();}
    
            return Shared<Registry<DataType>>(new Registry(path));
        }
        
        /**
         * Add a file to a memory location
         * @param file
         */
        void addFile(NamespaceId name, DataType file) {
            m_fileNames.insert(name);
            m_files.insert({name, file});
        }
    
        std::unordered_set<NamespaceId> getFiles() {
            return m_fileNames;
        }
    
        std::unordered_set<NamespaceId> getFiles(const std::string& fileNamespace) {
            std::unordered_set<NamespaceId> files = {};
            for(const auto& ns : m_fileNames) {
                if(ns.getNamespace() == fileNamespace) {
                    files.insert(ns);
                }
            }
            return files;
        }
        
        std::unordered_set<std::string> getNamespaces() {
            std::unordered_set<std::string> namespaces = {};
            for(const auto& ns : m_fileNames) {
                namespaces.insert(ns.getNamespace());
            }
            return namespaces;
        }
        
        DataType getFile(NamespaceId fileName) {
            return m_files[fileName];
        }
        
    private:
        explicit Registry(const std::string& path) {
            ASSERT((std::is_base_of<RegistryDataBase, DataType>::value), "DataType not derived from RegistryData");
            // Get all files on disk
            std::filesystem::create_directory(gameDataPath);
            for(auto& entry : std::filesystem::directory_iterator(gameDataPath)) {
                if(entry.is_directory()) {
                    std::string ns = entry.path().filename().string();
                    std::string absolutePath = getAbsolutePath(ns, path);
                
                    if(!std::filesystem::exists(absolutePath)) continue;
                    
                    for(auto& file : std::filesystem::directory_iterator(absolutePath)) {
                        std::string id = file.path().lexically_normal().filename().replace_extension("").string();
                        auto* nsid = new NamespaceId(ns, id);
                        DataType data = DataType(file.path().lexically_normal().string());
                        addFile(*nsid, data);
                    }
                }
            }
        }
        
        std::unordered_set<NamespaceId> m_fileNames = {};
        std::unordered_map<NamespaceId, DataType> m_files = {};
        
        static std::unordered_map<std::string, Registry<DataType>> m_registries;
    };
    
    template <typename DataType>
    std::unordered_map<std::string, Registry<DataType>> Registry<DataType>::m_registries = {};
} // Poly

#include <fstream>
#include "RegistryData.h"
#include "poly/util/Ref.h"

namespace Poly {
    
    Json JsonRegistryData::loadData() {
        std::ifstream f(m_path);
        return Json::parse(f);
    }
    
    JsonRegistryData::JsonRegistryData(): RegistryData<Json>(Json()) {
    
    }
}

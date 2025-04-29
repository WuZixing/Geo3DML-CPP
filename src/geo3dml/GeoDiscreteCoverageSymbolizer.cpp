// UTF-8编码
#include <geo3dml/GeoDiscreteCoverageSymbolizer.h>

using namespace geo3dml;

GeoDiscreteCoverageSymbolizer::GeoDiscreteCoverageSymbolizer() {

}

GeoDiscreteCoverageSymbolizer::~GeoDiscreteCoverageSymbolizer() {

}

Symbolizer* GeoDiscreteCoverageSymbolizer::Clone() const {
    return new GeoDiscreteCoverageSymbolizer();
}

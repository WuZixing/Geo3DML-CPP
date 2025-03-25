// UTF-8编码
#pragma once

#include "SpatialRelation.h"

namespace geo3dml {
    /// @brief 地质要素由作为其边界的其它地质要素包围而成的关系。该关系的源是边界所围成的地质要素，目标则是组成边界的要素。
    class BoundaryRelation : public SpatialRelation {

    };
}

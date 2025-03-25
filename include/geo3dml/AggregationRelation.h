// UTF-8编码
#pragma once

#include "SpatialRelation.h"

namespace geo3dml {
    /// @brief 聚合关系，表达地质要素由一个或多个其它地质要素聚合而成的关系。如某个断层面由多个小断面聚合而成，其中源表示被组成的地质要素，目标则是组成的部分。该关系可用于描述地质要素之间的普通聚合关系，不一定具有明确的地质含义。
    class AggregationRelation : public SpatialRelation {

    };
}

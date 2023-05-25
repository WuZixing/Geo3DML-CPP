// UTF-8编码
#pragma once

#include <geo3dml/CuboidVolume.h>

namespace g3dvtk {
    /// @brief 基于VTK数据结构的CuboidVolume类型实现。
    class CuboidVolume : public geo3dml::CuboidVolume {
    public:
        CuboidVolume();
        virtual ~CuboidVolume();
    };
}

// UTF-8编码
#pragma once

#include <geo3dml/Box3D.h>

namespace g3dvtk {
    extern void SetBox3DFromVTKBound(const double bounds[6], geo3dml::Box3D& box);
}


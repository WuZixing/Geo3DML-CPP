// UTF-8编码
#pragma once

#include "Volume.h"

namespace geo3dml {

    /// @brief 四面体构成的体。
    class TetrahedronVolume : public Volume {
    public:
        TetrahedronVolume();
        virtual ~TetrahedronVolume();

        /// @name 读写顶点的方法。
        ///@{
        virtual int AppendVertex(double x, double y, double z) = 0;
        virtual int GetVertexCount() const = 0;
        virtual bool GetVertexAt(int i, double& x, double& y, double& z) const = 0;
        ///@}

        /// @name 读写三棱柱的方法。
        ///@{
        virtual int AppendTetrahedron(int v1, int v2, int v3, int v4) = 0;
        virtual int GetTetrahedronCount() const = 0;
        virtual bool GetTetrahedronAt(int i, int& v1, int& v2, int& v3, int& v4) const = 0;
        ///@}
    };
}

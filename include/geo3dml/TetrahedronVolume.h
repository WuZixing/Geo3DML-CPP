// UTF-8编码
#pragma once

#include "Volume.h"

namespace geo3dml {
    /// @brief 四面体构成的体。从v2版本开始支持。
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

        /// @name 读写四面体单元的方法。
        ///@{
        /// @brief 指定构成体元的4个顶点，添加一个四面体体元。
        /// @param v1,v2,v3,v4 构成四面体的4个顶点的索引号。要求v1、v2和v3按右手系规则构成的三角形的法向朝向v4。
        /// @return 返回新添加的体元的索引号。
        virtual int AppendTetrahedron(int v1, int v2, int v3, int v4) = 0;
        virtual int GetTetrahedronCount() const = 0;
        virtual bool GetTetrahedronAt(int i, int& v1, int& v2, int& v3, int& v4) const = 0;
        ///@}
    };
}

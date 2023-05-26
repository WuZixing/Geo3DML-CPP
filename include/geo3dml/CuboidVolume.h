// UTF-8编码
#pragma once

#include "Volume.h"

namespace geo3dml {
    /// @brief 大小不一的六面体（如长方体）单元构成的体。
    class CuboidVolume : public Volume {
    public:
        CuboidVolume();
        virtual ~CuboidVolume();

        /// @name 读写顶点的方法。
        ///@{
        /// @brief 添加一个顶点。
        /// @param x 顶点的坐标：x。
        /// @param y 顶点的坐标：y。
        /// @param z 顶点的坐标：z。
        /// @return 返回新添加的顶点的索引号。
        virtual int AppendVertex(double x, double y, double z) = 0;
        virtual int GetVertexCount() const = 0;
        virtual bool GetVertexAt(int i, double& x, double& y, double& z) const = 0;
        ///@}

        /// @name 读写六面体体单元的方法。
        ///@{
        /// @brief 指定构成体元的8个顶点，添加一个六面体体元。
        /// @param v1,v2,v3,v4 构成底面的4个顶点的索引号。顶点的顺序应保持该面在右手坐标系下的法向朝向与该面对应的另一底面，即由顶点v5、v6、v7和v8构成的底面。
        /// @param v5,v6,v7,v8 构成与前面底面对应的另一底面的4个顶点的索引号。顶点的顺序使得v1、v2、v5和v6构成六面体的一个侧面；其余顶点依此类推。
        /// @return 返回新添加的体元的索引号。
        virtual int AppendCuboid(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8) = 0;
        virtual int GetCuboidCount() const = 0;
        virtual bool GetCuboidAt(int i, int& v1, int& v2, int& v3, int& v4, int& v5, int& v6, int& v7, int& v8) const = 0;
        ///@}
    };
}

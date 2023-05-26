// UTF-8编码234五六七
#pragma once

#include "Volume.h"

namespace geo3dml {

    /// @brief 广义三棱柱构成的体。
    class GTPVolume : public Volume {
    public:
        GTPVolume();
        virtual ~GTPVolume();

        /// @name 读写顶点的方法。
        ///@{
        virtual int AppendVertex(double x, double y, double z) = 0;
        virtual int GetVertexCount() const = 0;
        virtual bool GetVertexAt(int i, double& x, double& y, double& z) const = 0;
        ///@}

        /// @name 读写三棱柱的方法。
        ///@{
        /// @brief 指定构成体元的6个顶点，添加一个三棱柱体元。
        /// @param top1,top2,top3 构成顶面三角形的3个顶点的索引号。顶点的顺序应保持该面在右手坐标系下的法向朝向体元外部。
        /// @param bottom1,bottom2,bottom3 构成底面三角形的3个顶点的索引号。顶点的顺序使得top1、top2、bottom1与bottom2对应构成三棱柱的一个侧面；其余顶点依此类推。
        /// @return 返回新添加的体元的索引号。
        virtual int AppendPrism(int top1, int top2, int top3, int bottom1, int bottom2, int bottom3) = 0;
        virtual int GetPrismCount() const = 0;
        virtual bool GetPrismAt(int i, int& top1, int& top2, int& top3, int& bottom1, int& bottom2, int& bottom3) const = 0;
        ///@}
    };
}
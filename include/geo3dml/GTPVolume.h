// UTF-8编码234五六七
#pragma once

#include "GeoVolume.h"

namespace geo3dml {

    /// @brief 广义三棱柱构成的体。
    class GTPVolume : public GeoVolume {
    public:
        GTPVolume();
        virtual ~GTPVolume();

        /// @name 读写顶点的方法。
        //@{
        virtual int AppendVertex(double x, double y, double z) = 0;
        virtual int GetVertexCount() const = 0;
        virtual bool GetVertexAt(int i, double& x, double& y, double& z) const = 0;
        //@}

        /// @name 读写三棱柱的方法。
        //@{
        virtual int AppendPrism(int topVertex1, int topVertex2, int topVertex3, int bottomVertex1, int bottomVertex2, int bottomVertex3) = 0;
        virtual int GetPrismCount() const = 0;
        virtual bool GetPrismAt(int i, int& topVertex1, int& topVertex2, int topVertex3, int bottomVertex1, int& bottomVertex2, int& bottomVertex3) const = 0;
        //@}
    };
}
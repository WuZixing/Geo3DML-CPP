// UTF-8编码
#pragma once

#include <geo3dml/MultiTIN.h>

namespace geo3dml {
    namespace geometry {
        class MultiTIN : public geo3dml::MultiTIN {
        public:
            MultiTIN();
            virtual ~MultiTIN();

        public:
            /// @name 实现父类定义的接口。
            ///@{
            virtual int AddTIN(const geo3dml::TIN* tin) override;
            virtual int GetTINCount() const override;
            virtual int GetVertexCountOfTIN(int tinIndex) const override;
            virtual void GetVertexOfTIN(int tinIndex, int vertexIndex, double& x, double& y, double& z) const override;
            virtual int GetTriangleCountOfTIN(int tinIndex) const override;
            virtual void GetTriangleOfTIN(int tinIndex, int triangleIndex, int& v1, int& v2, int& v3) const override;
            ///@}

            /// @name 实现基类 geo3dml::Geometry 定义的接口。
            ///@{
            virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
            ///@}

        private:
            std::vector<geo3dml::TIN*> tins_;
        };
    }
}

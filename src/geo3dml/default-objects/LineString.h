// UTF-8编码
#pragma once

#include <geo3dml/LineString.h>

namespace geo3dml {
    namespace geometry {
        class LineString : public geo3dml::LineString {
        public:
            LineString();
            virtual ~LineString();

        public:
            /// @name 实现父类geo3dml::LineString定义的接口。
            ///@{
            virtual void AddVertex(double x, double y, double z) override;
            virtual int GetVertexCount() const override;
            virtual void GetVertexAt(int i, double& x, double& y, double& z) const override;
            ///@}

            /// @name 实现基类geo3dml::Geometry定义的接口。
            ///@{
            virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
            ///@}

        private:
            std::vector<Point3D> vertices_;
        };
    }
}

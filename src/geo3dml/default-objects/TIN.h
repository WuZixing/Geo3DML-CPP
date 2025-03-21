// UTF-8编码
#pragma once

#include <geo3dml/TIN.h>

namespace geo3dml {
    namespace geometry {
        class TIN : public geo3dml::TIN {
        public:
            TIN();
            virtual ~TIN();

        public:
			/// @name 实现父类定义的接口。
			///@{
			virtual void AppendVertex(double x, double y, double z) override;
			virtual int GetVertexCount() const override;
			virtual void GetVertexAt(int i, double& x, double& y, double& z) const override;
			virtual void AppendTriangle(int v1, int v2, int v3) override;
			virtual int GetTriangleCount() const override;
			virtual void GetTriangleAt(int i, int& v1, int& v2, int& v3) const override;
            ///@}

            /// @name 实现基类 geo3dml::Geometry 定义的接口。
            ///@{
            virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
            ///@}

        private:
            struct Triangle {
                int v1 = -1, v2 = -1, v3 = -1;

                Triangle(int v1 = -1, int v2 = -1, int v3 = -1) {
                    this->v1 = v1;
                    this->v2 = v2;
                    this->v3 = v3;
                }
            };
            std::vector<geo3dml::Point3D> vertices_;
            std::vector<Triangle> triangles_;
        };
    }
}

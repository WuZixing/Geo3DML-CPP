// UTF-8编码
#pragma once

#include <geo3dml/TetrahedronVolume.h>

namespace geo3dml {
    namespace geometry {
        class TetrahedronVolume : public geo3dml::TetrahedronVolume {
        public:
            TetrahedronVolume();
            virtual ~TetrahedronVolume();

        public:
            /// @name 实现父类定义的接口。
            ///@{
            virtual int AppendVertex(double x, double y, double z) override;
            virtual int GetVertexCount() const override;
            virtual bool GetVertexAt(int i, double& x, double& y, double& z) const override;
            virtual int AppendTetrahedron(int v1, int v2, int v3, int v4) override;
            virtual int GetTetrahedronCount() const override;
            virtual bool GetTetrahedronAt(int i, int& v1, int& v2, int& v3, int& v4) const override;
            ///@}

            /// @name 实现基类 geo3dml::Geometry 定义的接口。
            ///@{
            virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
            ///@}

        private:
            /// 四面体体元。由4个顶点构成。
            struct Tetrahedron {
                int v1 = -1, v2 = -1, v3 = -1, v4 = -1;
                Tetrahedron(int v1 = -1, int v2 = -1, int v3 = -1, int v4 = -1) {
                    this->v1 = v1;
                    this->v2 = v2;
                    this->v3 = v3;
                    this->v4 = v4;
                }
            };

            std::vector<Point3D> vertices_;
            std::vector<Tetrahedron> cells_;
        };
    }
}

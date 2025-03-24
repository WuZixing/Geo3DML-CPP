// UTF-8编码
#pragma once

#include <geo3dml/CuboidVolume.h>

namespace geo3dml {
    namespace geometry {
        class CuboidVolume : public geo3dml::CuboidVolume {
        public:
            CuboidVolume();
            virtual ~CuboidVolume();

        public:
            /// @name 实现父类定义的接口。
            ///@{
            virtual int AppendVertex(double x, double y, double z) override;
            virtual int GetVertexCount() const override;
            virtual bool GetVertexAt(int i, double& x, double& y, double& z) const override;
            virtual int AppendCuboid(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8) override;
            virtual int GetCuboidCount() const override;
            virtual bool GetCuboidAt(int i, int& v1, int& v2, int& v3, int& v4, int& v5, int& v6, int& v7, int& v8) const override;
            ///@}

            /// @name 实现基类 geo3dml::Geometry 定义的接口。
            ///@{
            virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
            ///@}

        private:
            /// 一个长方体由其8个顶点表达。
            struct Cuboid {
                int vertexIndices[8];

                Cuboid() {
                    for (int n = 0; n < 8; ++n) {
                        vertexIndices[n] = -1;
                    }
                }
            };

            std::vector<Point3D> vertices_;
            std::vector<Cuboid> cuboids_;
        };
    }
}

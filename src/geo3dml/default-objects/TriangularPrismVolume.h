// UTF-8编码
#pragma once

#include <geo3dml/TriangularPrismVolume.h>

namespace geo3dml {
    namespace geometry {
        class TriangularPrismVolume : public geo3dml::TriangularPrismVolume {
        public:
            TriangularPrismVolume();
            virtual ~TriangularPrismVolume();

        public:
            /// @name 实现父类定义的接口。
            ///@{
            virtual int AppendVertex(double x, double y, double z) override;
            virtual int GetVertexCount() const override;
            virtual bool GetVertexAt(int i, double& x, double& y, double& z) const override;
            virtual int AppendPrism(int top1, int top2, int top3, int bottom1, int bottom2, int bottom3) override;
            virtual int GetPrismCount() const override;
            virtual bool GetPrismAt(int i, int& top1, int& top2, int& top3, int& bottom1, int& bottom2, int& bottom3) const override;
            ///@}

            /// @name 实现基类 geo3dml::Geometry 定义的接口。
            ///@{
            virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
            ///@}

        private:
            std::vector<Point3D> vertices_;

            /// @brief 三棱柱的顶底面是三角形。
            struct Triangle {
                int v1 = -1, v2 = -1, v3 = -1;

                Triangle(int v1 = -1, int v2 = -1, int v3 = -1) {
                    this->v1 = v1;
                    this->v2 = v2;
                    this->v3 = v3;
                }
            };
            /// @brief 三棱柱。
            struct Prism {
                Triangle bottomTriangle, topTriangle;
            };
            std::vector<Prism> prisms_;
        };
    }
}

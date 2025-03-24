// UTF-8编码
#pragma once

#include <geo3dml/TruncatedRegularGrid.h>

namespace geo3dml {
    namespace geometry {
        class TruncatedRegularGrid : public geo3dml::TruncatedRegularGrid {
        public:
            TruncatedRegularGrid();
            virtual ~TruncatedRegularGrid();

        public:
            /// @name 实现父类定义的接口。
            ///@{
            virtual int AppendVertex(double x, double y, double z) override;
            virtual int GetVertexCount() const override;
            virtual bool GetVertexAt(int i, double& x, double& y, double& z) const override;
            virtual int AppendFace(const std::list<int>& vertices) override;
            virtual int GetFaceCount() const override;
            virtual bool GetFaceAt(int i, std::list<int>& vertices) const override;
            virtual int AppendCell(const std::list<int>& faces, int i = 0, int j = 0, int k = 0) override;
            virtual int GetCellCount() const override;
            virtual bool GetCellAt(int n, std::list<int>& faces, int& i, int& j, int& k) const override;
            ///@}

            /// @name 实现基类 geo3dml::Geometry 定义的接口。
            ///@{
            virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
            ///@}

        private:
            /// 面片。记录组成该面片的顶点列表。
            struct Face {
                std::list<int> vertices;
            };
            /// 体元。记录组成该体元的面片列表，以及体元的IJK索引值。
            struct Cell {
                std::list<int> faces;
                int i, j, k;

                Cell() { i = j = k = -1; };
            };

            std::vector<Point3D> vertices_;
            std::vector<Face> faces_;
            std::vector<Cell> cells_;
        };
    }
}

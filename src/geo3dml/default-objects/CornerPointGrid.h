// UTF-8编码
#pragma once

#include <geo3dml/CornerPointGrid.h>

namespace geo3dml {
    namespace geometry {
        class CornerPointGrid : public geo3dml::CornerPointGrid {
        public:
            CornerPointGrid();
            /// @brief 构造函数。
            /// @param dimI I轴（或X轴）方向划分的网格的数目。
            /// @param dimJ J轴（或Y轴）方向划分的网格的数目。
            /// @param dimK K轴（或Z轴）方向划分的网格的数目。
            CornerPointGrid(int dimI, int dimJ, int dimK);
            virtual ~CornerPointGrid();
            /// @brief 初始化网格。使用缺省的构造函数实例化对象后，需要调用本方法构造角点网格。
            /// @param dimI I轴（或X轴）方向划分的网格的数目。
            /// @param dimJ J轴（或Y轴）方向划分的网格的数目。
            /// @param dimK K轴（或Z轴）方向划分的网格的数目。
            /// @return 返回true表示网格构造成功，否则表示失败。
            virtual bool Init(int dimI, int dimJ, int dimK) override;

        public:
            /// @name 实现父类定义的接口。
            ///@{
            virtual void GetDimensions(int& i, int& j, int& k) const override;
            virtual void AddNextPillar(double headPos[3], double tailPos[3]) override;
            virtual void AddNextCell(
                int i, int j, int k,
                double bottomFrontLeft[3], double bottomFrontRight[3],
                double bottomBackLeft[3], double bottomBackRight[3],
                double topFrontLeft[3], double topFrontRight[3],
                double topBackLeft[3], double topBackRight[3],
                bool isValid = true
            ) override;
            virtual void SetCellValidation(int i, int j, int k, bool beValid = true) override;
            virtual void GetPillarAt(int i, int j, double headPos[3], double tailPos[3]) const override;
            virtual void GetCellAt(int i, int j, int k,
                double bottomFrontLeft[3], double bottomFrontRight[3],
                double bottomBackLeft[3], double bottomBackRight[3],
                double topFrontLeft[3], double topFrontRight[3],
                double topBackLeft[3], double topBackRight[3],
                bool& isValid) const override;
            ///@}

            /// @name 实现基类 geo3dml::Geometry 定义的接口。
            ///@{
            virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
            ///@}

        private:
            void DoubleArrayToPoint(const double pos[3], Point3D& pt) const;
            void PointToDoubleArray(const Point3D& pt, double pos[3]) const;
            int GetCellIndex(int i, int j, int k) const;

        private:
            /// @brief 角点网格的Pillar线。Pillar线有首、尾2个顶点定义。
            struct Pillar {
                Point3D head, tail;
            };
            /// @brief 角点网格中的体元。每个体元要记录其8个顶点的坐标，以及该体元是否有效。
            struct Cell {
                Point3D corners[8]; ///< 顶点的顺序：(0,0,0), (1,0,0), (0,1,0), (1,1,0), (0,0,1), (1,0,1), (0,1,1), (1,1,1)。
                bool isValid = false;
            };

            int dimI_, dimJ_, dimK_;
            std::vector<Pillar> pillars_;
            std::vector<Cell> cells_;
        };
    }
}

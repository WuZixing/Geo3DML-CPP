// UTF-8编码
#pragma once

#include <list>
#include "Volume.h"

namespace geo3dml {
    /// @brief TruncatedRegularGrid：截断规则网格。从v2版本开始支持。
    class TruncatedRegularGrid : public Volume {
    public:
        TruncatedRegularGrid();
        virtual ~TruncatedRegularGrid();

        /// @name 平面网格划分参数。
        ///@{
        /// 平面网格划分的原点。
        void SetPlaneGridOrigin(const Point3D& pt);
        const Point3D& GetPlaneGridOrigin() const;
        /// 平面坐标轴（Y轴）的方位角。正北为0度，正东为90度，正南为180度，正西为270度。
        void SetPlaneGridAzimuth(double degree);
        double GetPlaneGridAzimuth() const;
        /// 平面网格单元的大小，即沿坐标轴（X轴和Y轴）划分网格的步长。
        void SetPlaneGridCellSize(double xSize, double ySize);
        void GetPlaneGridCellSize(double& xSize, double& ySize) const;
        /// 平面网格划分的数目，即沿坐标轴（X轴和Y轴）划分的网格的数目。
        void SetPlaneGridCellNumber(int xNumber, int yNumber);
        void GetPlaneGridCellNumber(int& xNumber, int& yNumber) const;
        ///@}

        /// @name 顶点
        ///@{
        /// @brief 添加一个顶点。
        /// @param x,y,z 顶点的坐标。
        /// @return 返回新添加顶点的索引号。
        virtual int AppendVertex(double x, double y, double z) = 0;
        virtual int GetVertexCount() const = 0;
        virtual bool GetVertexAt(int i, double& x, double& y, double& z) const = 0;
        ///@}

        /// @name 面
        ///@{
        /// @brief 添加一个面片。
        /// @param vertices 指定构成该面片的顶点列表。由顶点的索引号构成。不重复存储首尾顶点。
        /// @return 返回新添加的面片的索引号。
        virtual int AppendFace(const std::list<int>& vertices) = 0;
        virtual int GetFaceCount() const = 0;
        virtual bool GetFaceAt(int i, std::list<int>& vertices) const = 0;
        ///@}

        /// @name 体元
        ///@{
        /// @brief 添加一个体元。
        /// @param faces 指定构成该体元的面片的列表。由面片的索引号构成。
        /// @param i,j,k 该体元对应的I、J、K索引值。
        /// @return 返回新添加的体元的索引号。
        virtual int AppendCell(const std::list<int>& faces, int i = 0, int j = 0, int k = 0) = 0;
        virtual int GetCellCount() const = 0;
        virtual bool GetCellAt(int n, std::list<int>& faces, int& i, int& j, int& k) const = 0;
        ///@}

    private:
        Point3D planeGridOrigin_;
        double planeGridAzimuth_;
        double planeGridCellSizeX_, planeGridCellSizeY_;
        int planeGridCellNumberX_, planeGridCellNumberY_;
    };
}

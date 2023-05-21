// UTF-8编码
#pragma once

#include "GeoVolume.h"
#include "Matrix4x4.h"
#include "Point3D.h"

namespace geo3dml {

    /// @brief 三维环境下的gml:RectifiedGrid。定义规则网格，以及带坐标变换的规则网格。
    class RectifiedGrid : public GeoVolume {
    public:
        /// @brief 构造函数。
        /// @param origin   网格划分的起始点在全局坐标系中的坐标。
        /// @param vecI     网格I坐标轴对应于全局坐标系的单位向量，表达网格单元沿I轴的棱的方向与长度。
        /// @param vecJ     网格J坐标轴对应于全局坐标系的单位向量，表达网格单元沿J轴的棱的方向与长度。
        /// @param vecK     网格K坐标轴对应于全局坐标系的单位向量，表达网格单元沿K轴的棱的方向与长度。
        /// @param highI    在局部坐标系下，网格的最大I坐标。
        /// @param highJ    在局部坐标系下，网格的最大J坐标。
        /// @param highK    在局部坐标系下，网格的最大K坐标。
        /// @param lowI     在局部坐标系下，网格的最小I坐标。缺省值为0。
        /// @param lowJ     在局部坐标系下，网格的最小J坐标。缺省值为0。
        /// @param lowK     在局部坐标系下，网格的最小K坐标。缺省值为0。
        RectifiedGrid(const Point3D& origin, const Vector3D& vecI, const Vector3D& vecJ, const Vector3D& vecK, int highI, int highJ, int highK, int lowI = 0, int lowJ = 0, int lowK = 0);
        /// @brief 在网格局部坐标系与全局坐标系重合的条件下，构造一个网格对象。
        /// @param origin   网格划分的起始点在全局坐标系中的坐标。
        /// @param stepI    网格单元沿I轴的棱的长度。
        /// @param stepJ    网格单元沿J轴的棱的长度。
        /// @param stepK    网格单元沿K轴的棱的长度。
        /// @param highI    在局部坐标系下，网格的最大I坐标。
        /// @param highJ    在局部坐标系下，网格的最大J坐标。
        /// @param highK    在局部坐标系下，网格的最大K坐标。
        /// @param lowI     在局部坐标系下，网格的最小I坐标。缺省值为0。
        /// @param lowJ     在局部坐标系下，网格的最小J坐标。缺省值为0。
        /// @param lowK     在局部坐标系下，网格的最小K坐标。缺省值为0。
        RectifiedGrid(const Point3D& origin, double stepI, double stepJ, double stepK, int highI, int highJ, int highK, int lowI = 0, int lowJ = 0, int lowK = 0);
        virtual ~RectifiedGrid();

        /// @brief 取网格划分的起始点坐标。
        /// @return 网格划分的起始点坐标。
        const Point3D& Origin() const;

        /// @brief 取网格I坐标轴对应于全局坐标系的单位向量。
        /// @return I坐标轴对应于全局坐标系的单位向量。
        const Vector3D& AxisI() const;
        /// @brief 取网格J坐标轴对应于全局坐标系的单位向量。
        /// @return J坐标轴对应于全局坐标系的单位向量。
        const Vector3D& AxisJ() const;
        /// @brief 取网格K坐标轴对应于全局坐标系的单位向量。
        /// @return K坐标轴对应于全局坐标系的单位向量。
        const Vector3D& AxisK() const;

        /// @brief 取网格单元范围。
        /// @param lowI 输出网格单元的最小I坐标。
        /// @param lowJ 输出网格单元的最小J坐标。
        /// @param lowK 输出网格单元的最小K坐标。
        /// @param highI 输出网格单元的最大I坐标。
        /// @param highJ 输出网格单元的最大J坐标。
        /// @param highK 输出网格单元的最大K坐标。
        void GetCellRange(int& lowI, int& lowJ, int& lowK, int& highI, int& highJ, int& highK) const;

        /// @brief 计算将该网格从其局部正交坐标系转换至全局坐标系的变换矩阵。
        /// @return 坐标变换矩阵。
        Matrix4x4 ComputeTransformMatrix() const;

        /// @name 实现父类 geo3dml::Geometry 定义的接口。
        /// @see geo3dml::Geometry#GetMinimumBoundingRectangle
        virtual Box3D GetMinimumBoundingRectangle() const override;

    private:
        Point3D origin_;
        Vector3D axisI_, axisJ_, axisK_;
        int lowI_, lowJ_, lowK_, highI_, highJ_, highK_;
    };
}
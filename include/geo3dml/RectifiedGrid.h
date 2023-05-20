// UTF-8编码
#pragma once

#include "GeoVolume.h"
#include "Math.h"
#include "Point3D.h"

namespace geo3dml {

    /// @brief 三维环境下的gml:RectifiedGrid。定义规则网格，以及带坐标变换的规则网格。
    class RectifiedGrid : public GeoVolume {
    public:
        /// @brief 构造函数
        /// @param origin   网格划分的起始点在全局坐标系中的坐标。
        /// @param vecI     网格I坐标轴对应于全局坐标系的单位向量，表达网格单元沿I轴的棱的方向与长度。
        /// @param vecJ     网格J坐标轴对应于全局坐标系的单位向量，表达网格单元沿J轴的棱的方向与长度。
        /// @param vecK     网格K坐标轴对应于全局坐标系的单位向量，表达网格单元沿K轴的棱的方向与长度。
        /// @param dimI     沿网格I坐标轴划分的网格的总数。
        /// @param dimJ     沿网格J坐标轴划分的网格的总数。
        /// @param dimK     沿网格K坐标轴划分的网格的总数。
        RectifiedGrid(const Point3D& origin, const Vector3D& vecI, const Vector3D& vecJ, const Vector3D& vecK, int dimI, int dimJ, int dimK);
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

        /// @brief 取网格划分的数目
        /// @param i 输出I轴方向划分的网格的总数。
        /// @param j 输出J轴方向划分的网格的总数。
        /// @param k 输出K轴方向划分的网格的总数。
        void GetDimensions(int& i, int& j, int& k) const;

        /// @brief 计算将该网格从其局部正交坐标系转换至全局坐标系的变换矩阵。
        /// @return 坐标变换矩阵。
        Matrix4x4 ComputeTransformMatrix() const;

        /// @name 实现父类 geo3dml::Geometry 定义的接口。
        /// @see geo3dml::Geometry#GetMinimumBoundingRectangle
        virtual bool GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) const override;

    private:
        Point3D origin_;
        Vector3D axisI_, axisJ_, axisK_;
        int dimI_, dimJ_, dimK_;
    };
}
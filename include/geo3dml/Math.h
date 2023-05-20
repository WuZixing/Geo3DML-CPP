// UTF-8编码
#pragma once

namespace geo3dml {

    class Vector3D {
    public:
        Vector3D(double x = 0, double y = 0, double z = 0);
        Vector3D(const Vector3D& v);
        ~Vector3D();

        Vector3D& operator=(const Vector3D& v);

        double X() const;
        double Y() const;
        double Z() const;

        Vector3D& X(double x);
        Vector3D& Y(double y);
        Vector3D& Z(double z);

        double LengthSquared() const;
        double Length() const;

        /// @brief 计算与该向量方向一致的单位向量。
        /// @return 与该向量方向一致的单位向量。
        Vector3D UnitVector() const;

    private:
        double x_, y_, z_;
    };

    class Matrix3x3 {
    public:
        Matrix3x3();
        Matrix3x3(const Matrix3x3& m);
        ~Matrix3x3();

        Matrix3x3& operator=(const Matrix3x3& m);

        /// @brief 将矩阵置为单位矩阵。
        /// @return 返回被修改后的矩阵。
        Matrix3x3& Identify();

        /// @brief 设置矩阵元素的值。
        /// @param row  该元素的位置：行号（[1, 3]）。
        /// @param col  该元素的位置：列号（[1, 3]）。
        /// @param v    该元素的值。
        /// @return     返回被修改后的矩阵。
        Matrix3x3& Element(int row, int col, double v);

        /// @brief 取矩阵元素的值。
        /// @param row  该元素的位置：行号（[1, 3]）。
        /// @param col  该元素的位置：列号（[1, 3]）。
        /// @return     该元素的值。位置无效时返回0。
        double Element(int row, int col) const;

    private:
        /// 行优先的矩阵，即首3个元素对应矩阵第一行从左至右的3个元素。
        double matrix_[9];
    };

    class Matrix4x4 {
    public:
        Matrix4x4();
        Matrix4x4(const Matrix4x4& m);
        ~Matrix4x4();

        Matrix4x4& operator=(const Matrix4x4& m);

        /// @brief 将矩阵置为单位矩阵。
        /// @return 返回被修改后的矩阵。
        Matrix4x4& Identify();

        /// @brief 设置矩阵元素的值。
        /// @param row  该元素的位置：行号（[1, 4]）。
        /// @param col  该元素的位置：列号（[1, 4]）。
        /// @param v    该元素的值。
        /// @return     返回被修改后的矩阵。
        Matrix4x4& Element(int row, int col, double v);

        /// @brief 取矩阵元素的值。
        /// @param row  该元素的位置：行号（[1, 4]）。
        /// @param col  该元素的位置：列号（[1, 4]）。
        /// @return     该元素的值。位置无效时返回0。
        double Element(int row, int col) const;

    private:
        /// 行优先的矩阵，即首4个元素对应矩阵第一行从左至右的4个元素。
        double matrix_[16];
    };
}

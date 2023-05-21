// UTF-8编码
#pragma once

namespace geo3dml {

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

        /// @brief 计算该矩阵的行列式。
        /// @return 矩阵的行列式的值。
        double Determinant() const;

    private:
        /// 行优先的矩阵，即首3个元素对应矩阵第一行从左至右的3个元素。
        double matrix_[9];
    };
}

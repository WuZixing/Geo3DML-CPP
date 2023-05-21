// UTF-8编码
#pragma once

namespace geo3dml {

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

        /// @brief 计算该矩阵的行列式。
        /// @return 矩阵的行列式的值。
        double Determinant() const;

    private:
        /// 行优先的矩阵，即首4个元素对应矩阵第一行从左至右的4个元素。
        double matrix_[16];
    };
}

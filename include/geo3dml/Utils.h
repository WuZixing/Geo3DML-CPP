// UTF-8编码
#pragma once
#include <string>

namespace geo3dml {
    extern bool IsZero(double v);
    extern bool IsTrue(const std::string& s);
    /// @brief 判断字符串a和b是否相等。该判别方法不区分字母的大小写形式。
    /// @param a 字符串a。
    /// @param b 字符串b。
    /// @return 字符串相等时返回true，否则返回false。
    extern bool IsiEqual(const std::string& a, const std::string& b);
}
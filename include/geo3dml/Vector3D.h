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
}

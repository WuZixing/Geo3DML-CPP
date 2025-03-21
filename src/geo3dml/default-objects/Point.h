// UTF-8编码
#pragma once

#include <geo3dml/Point.h>

namespace geo3dml {
    namespace geometry {
        class Point : public geo3dml::Point {
        public:
            Point();
            virtual ~Point();

        public:
            /// @name 基类geo3dml::Point定义的接口。
            ///@{
            virtual void SetPosition(double x, double y, double z) override;
            virtual void GetPosition(double& x, double& y, double& z) const override;
            virtual double GetX() const override;
            virtual double GetY() const override;
            virtual double GetZ() const override;
            ///@}

            /// @name 基类geo3dml::Geometry定义的接口。
            ///@{
            virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
            ///@}
            
        private:
            double x_, y_, z_;
        };
    }
}

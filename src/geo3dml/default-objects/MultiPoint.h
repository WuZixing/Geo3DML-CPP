// UTF-8编码
#pragma once

#include <geo3dml/MultiPoint.h>

namespace geo3dml {
    namespace geometry {
        /// 多点。
        class MultiPoint : public geo3dml::MultiPoint {
		public:
			MultiPoint();
			virtual ~MultiPoint();

		public:
			/// @name 实现父类定义的接口。
			///@{
			virtual void AddPoint(double x, double y, double z) override;
			virtual int GetPointCount() const override;
			virtual void GetPointAt(int i, double& x, double& y, double& z) const override;
			///@}

			/// @name 基类geo3dml::Geometry定义的接口。
			///@{
			virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
			///@}

		private:
			std::vector<Point3D> points_;
        };
    }
}

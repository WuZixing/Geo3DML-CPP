// UTF8-编码
#pragma once

#include "ObjectFactory.h"

namespace geo3dml {
    /// @brief 缺省的ObjectFactory实现类。提供几何对象的缺省实现。
    class DefaultObjectFactory : public ObjectFactory {
    public:
        DefaultObjectFactory();
        virtual ~DefaultObjectFactory();

        /// @name 实现父类定义的接口。
        ///@{
        virtual ObjectFactory* Clone() override;

		virtual geo3dml::Point* NewPoint() override;
		virtual geo3dml::MultiPoint* NewMultiPoint() override;
		virtual geo3dml::LineString* NewLineString() override;
		virtual geo3dml::MultiLineString* NewMultiLineString() override;
		virtual geo3dml::TIN* NewTIN() override;
		virtual geo3dml::CornerPointGrid* NewCornerPointGrid() override;
		virtual geo3dml::CornerPointGrid* NewCornerPointGrid(int dimI, int dimJ, int dimK) override;
		virtual geo3dml::Annotation* NewAnnotation() override;

		virtual geo3dml::TriangularPrismVolume* NewTriangularPrismVolume() override;

		virtual geo3dml::RectifiedGrid* NewRectifiedGrid(
			const geo3dml::Point3D& origin,
			const geo3dml::Vector3D& vecI, const geo3dml::Vector3D& vecJ, const geo3dml::Vector3D& vecK,
			int highI, int highJ, int highK, int lowI = 0, int lowJ = 0, int lowK = 0) override;
		virtual geo3dml::RectifiedGrid* NewRectifiedGrid(
			const geo3dml::Point3D& origin,
			double stepI, double stepJ, double stepK,
			int highI, int highJ, int highK, int lowI = 0, int lowJ = 0, int lowK = 0) override;

		virtual geo3dml::TetrahedronVolume* NewTetrahedronVolume() override;

		virtual geo3dml::CuboidVolume* NewCuboidVolume() override;

		virtual geo3dml::TruncatedRegularGrid* NewTruncatedRegularGrid() override;

		virtual geo3dml::ShapeProperty* NewShapeProperty() override;

		virtual geo3dml::Actor* NewActor() override;
        ///@}
    };
}

// UTF-8编码
#pragma once

#include "Project.h"
#include "Model.h"
#include "FeatureClass.h"
#include "Feature.h"
#include "TIN.h"
#include "CornerPointGrid.h"
#include "LineString.h"
#include "Point.h"
#include "MultiPoint.h"
#include "Map.h"
#include "PointSymbolizer.h"
#include "LineSymbolizer.h"
#include "SurfaceSymbolizer.h"
#include "GeoDiscreteCoverageSymbolizer.h"
#include "FeatureTypeStyle.h"
#include "Annotation.h"
#include "MultiLineString.h"
#include "TriangularPrismVolume.h"
#include "RectifiedGrid.h"
#include "TetrahedronVolume.h"
#include "CuboidVolume.h"
#include "TruncatedRegularGrid.h"

namespace geo3dml {
	/// Factory for Geo3DML objects. It is not thread safe.
	class ObjectFactory {
	public:
		static std::string TypeNameOfGeometry(Geometry* shape);

	public:
		ObjectFactory();
		virtual ~ObjectFactory();

		/// Clone the ObjectFactory itself.
		virtual ObjectFactory* Clone() = 0;

		/// @name model objects.
		///@{
		virtual Project* NewProject();

		virtual Model* NewModel();

		virtual FeatureClass* NewFeatureClass();

		virtual Feature* NewFeature();
		///@}

		/// @name goemetry(shape) objects.
		///@{
		virtual Point* NewPoint() = 0;

		virtual MultiPoint* NewMultiPoint() = 0;
		
		virtual LineString* NewLineString() = 0;

		virtual MultiLineString* NewMultiLineString() = 0;

		virtual TIN* NewTIN() = 0;

		virtual CornerPointGrid* NewCornerPointGrid() = 0;

		virtual CornerPointGrid* NewCornerPointGrid(int dimI, int dimJ, int dimK) = 0;

		virtual Annotation* NewAnnotation() = 0;

		virtual TriangularPrismVolume* NewTriangularPrismVolume() = 0;

		/// @brief 构造一个 RectifiedGrid 对象。
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
		/// @return			构造的 RectifiedGrid 对象。该指针所指向的对象由调用者负责管理。
		virtual RectifiedGrid* NewRectifiedGrid(
			const Point3D& origin,
			const Vector3D& vecI, const Vector3D& vecJ, const Vector3D& vecK,
			int highI, int highJ, int highK, int lowI = 0, int lowJ = 0, int lowK = 0) = 0;

		/// @brief 在网格局部坐标系与全局坐标系重合的条件下，构造一个 RectifiedGrid 对象。
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
		virtual RectifiedGrid* NewRectifiedGrid(
			const Point3D& origin,
			double stepI, double stepJ, double stepK,
			int highI, int highJ, int highK, int lowI = 0, int lowJ = 0, int lowK = 0) = 0;

		virtual TetrahedronVolume* NewTetrahedronVolume() = 0;

		virtual CuboidVolume* NewCuboidVolume() = 0;

		virtual TruncatedRegularGrid* NewTruncatedRegularGrid() = 0;
		///@}

		/// @name shape property.
		///@{
		virtual ShapeProperty* NewShapeProperty() = 0;
		///@}

		/// @name map
		///@{
		virtual Map* NewMap();

		virtual Layer* NewLayer();

		virtual Actor* NewActor();

		virtual PointSymbolizer* NewPointSymbolizer();

		virtual LineSymbolizer* NewLineSymbolizer();
		
		virtual SurfaceSymbolizer* NewSurfaceSymbolizer();

		virtual GeoDiscreteCoverageSymbolizer* NewGeoDiscreteCoverageSymbolizer();

		virtual FeatureTypeStyle* NewFeatureTypeStyle();
		///@}

	public:
		Geometry* NewGeometry(const std::string& typeName);
	};
}

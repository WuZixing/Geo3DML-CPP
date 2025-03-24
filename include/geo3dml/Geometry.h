// UTF-8编码
#pragma once

#include "Box3D.h"
#include "Geo3DML.h"
#include "ShapeProperty.h"

namespace geo3dml {

	/// A Geometry object is thread safe.
	class Geometry : public Object {
	public:
		Geometry();
		virtual ~Geometry();

		/// @brief 计算几何对象的最小外包矩形.
		/// @return 几何对象的最小外包矩形。
		virtual Box3D GetMinimumBoundingRectangle() const = 0;

		/// @brief 设置几何对象关联的属性场对象。
		/// @param prop 属性场对象。该属性场对象的内存将由本几何对象负责释放。
		/// @param t 属性场关联的目标位置。
		virtual void SetProperty(ShapeProperty* prop, ShapeProperty::SamplingTarget t);
		/// @brief 取几何对象关联属性场。
		/// @param t 属性场关联的目标位置。
		/// @return 属性场对象。该属性场对象的内存将由本几何对象负责释放。
		virtual ShapeProperty* GetProperty(ShapeProperty::SamplingTarget t) const;

	private:
		/// @brief 顶点集合上的属性场。
		ShapeProperty* vertexProperty_;
		/// @brief 边（或棱）集合上的属性场。
		ShapeProperty* edgeProperty_;
		/// @brief 面片集合上的属性场。
		ShapeProperty* faceProperty_;
		/// @brief 体元集合上的属性场。
		ShapeProperty* voxelProperty_;
	};
}

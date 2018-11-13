#pragma once

#include "Geo3DML.h"
#include "ShapeProperty.h"

namespace geo3dml {
	class Shape : public Object {
	public:
		Shape();
		virtual ~Shape();

	public:
		virtual void GetBoundingBox(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) = 0;
		virtual void SetProperty(ShapeProperty* prop, ShapeProperty::SamplingTarget t) = 0;
		virtual ShapeProperty* GetProperty(ShapeProperty::SamplingTarget t) = 0;
	};
}

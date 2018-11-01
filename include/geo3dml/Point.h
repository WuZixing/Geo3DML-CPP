#pragma once

#include "Shape.h"

namespace geo3dml {

	class Point : public Shape {
	public:
		Point();
		virtual ~Point();

	public:
		virtual void SetPosition(double x, double y, double z) = 0;
		virtual void GetPosition(double& x, double& y, double& z) = 0;
	};
}

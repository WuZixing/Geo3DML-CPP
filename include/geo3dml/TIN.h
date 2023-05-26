// UTF-8编码
#pragma once

#include "Geometry.h"

namespace geo3dml {

	class TIN : public Geometry {
	public:
		TIN();
		virtual ~TIN();

		//@{
		virtual void AppendVertex(double x, double y, double z) = 0;
		virtual int GetVertexCount() const = 0;
		virtual void GetVertexAt(int i, double& x, double& y, double& z) const = 0;
		//@}

		//@{
		/// @brief 指定3个顶点，添加一个三角形。
		/// @param v1,v2,v3 构成三角形的3个顶点的索引号。v1、v2和v3按右手系规则构成的三角形的法向为面的外侧。
		/// @return 返回新添加的三角形的索引号。
		virtual void AppendTriangle(int v1, int v2, int v3) = 0;
		virtual int GetTriangleCount() const = 0;
		virtual void GetTriangleAt(int i, int& v1, int& v2, int& v3) const = 0;
		//@}
	};
}

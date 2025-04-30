// UTF-8编码
#pragma once

#include "TIN.h"

namespace geo3dml {
	/// @brief 多个TIN形成的组合对象。
	class MultiTIN: public Geometry {
	public:
		MultiTIN();
		virtual ~MultiTIN();

	public:
		/// 向集合中添加一个TIN对象。
        /// @param tin 新添加的TIN对象。它的内存由调用者管理。
		/// @return 新添加的对象在集合中的索引位置。
		virtual int AddTIN(const TIN* tin) = 0;
		virtual int GetTINCount() const = 0;
		/// @name 访问TIN对象的顶点。
		///@{
		virtual int GetVertexCountOfTIN(int tinIndex) const = 0;
		virtual void GetVertexOfTIN(int tinIndex, int vertexIndex, double& x, double& y, double& z) const = 0;
		///@}
		/// @name 访问TIN对象的三角形。
		///@{
		virtual int GetTriangleCountOfTIN(int tinIndex) const = 0;
		virtual void GetTriangleOfTIN(int tinIndex, int triangleIndex, int& v1, int& v2, int& v3) const = 0;
		///@}
	};
}

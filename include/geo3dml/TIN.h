#pragma once

#include "Geometry.h"

namespace geo3dml {

	class TIN : public Geometry {
	public:
		TIN();
		virtual ~TIN();

		//@{
		virtual void AddVertex(int index, double x, double y, double z) = 0;
		virtual int GetVertexCount() const = 0;
		virtual void GetVertexAt(int i, double& x, double& y, double& z) const = 0;
		//@}

		//@{
		virtual void AddTriangle(int index, int vertex1, int vertex2, int vertex3) = 0;
		virtual int GetTriangleCount() const = 0;
		virtual void GetTriangleAt(int i, int& vertex1, int& vertex2, int& vertex3) const = 0;
		//@}
	};
}

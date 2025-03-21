// UTF-8编码
#pragma once

#include <geo3dml/MultiLineString.h>
#include "LineString.h"

namespace geo3dml {
    namespace geometry {
        class MultiLineString : public geo3dml::MultiLineString {
		public:
			MultiLineString();
			virtual ~MultiLineString();

		public:
			/// @name 实现父类定义的接口。
			///@{
			virtual int AddLineString(const geo3dml::LineString* line) override;
			virtual int GetLineStringCount() const override;
			virtual int GetVertexCountOfLineString(int lineIndex) const override;
			virtual void GetVertexOfLineString(int lineIndex, int vertexIndex, double& x, double& y, double& z) const override;
			///@}

			/// @name 实现基类定义的接口。
			///@{
			virtual Box3D GetMinimumBoundingRectangle() const override;
			///@}

		private:
			std::vector<geometry::LineString> lines_;
        };
    }
}

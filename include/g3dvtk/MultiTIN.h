// UTF-8编码
#pragma once

#include <geo3dml/MultiTIN.h>
#include <vtkPolyData.h>
#include <g3dvtk/ShapeHelper.h>

namespace g3dvtk {

	class MultiTIN : public geo3dml::MultiTIN {
	public:
		MultiTIN();
		virtual ~MultiTIN();

		/// @name 实现父类定义的接口。
		//@{
		virtual int AddTIN(const geo3dml::TIN* tin) override;
		virtual int GetTINCount() const override;
		virtual int GetVertexCountOfTIN(int tinIndex) const override;
		virtual void GetVertexOfTIN(int tinIndex, int vertexIndex, double& x, double& y, double& z) const override;
		virtual int GetTriangleCountOfTIN(int tinIndex) const override;
		virtual void GetTriangleOfTIN(int tinIndex, int triangleIndex, int& v1, int& v2, int& v3) const override;
		//@}

		/// @name 实现基类 geo3dml::Geometry 定义的接口。
		//@{
		virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
		virtual void SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t) override;
		virtual geo3dml::ShapeProperty* GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const override;
		//@}

		vtkPolyData* GetPolyData() const;

	private:
		vtkSmartPointer<vtkPolyData> polyData_;
		ShapeHelper shapeHelper_;
        /// 每个TIN包含的顶点。
        std::vector<std::vector<vtkIdType>> tinVertices_;
		struct Triangle {
			int v1 = -1, v2 = -1, v3 = -1;

			Triangle(int v1 = -1, int v2 = -1, int v3 = -1) {
				this->v1 = v1;
				this->v2 = v2;
				this->v3 = v3;
			}
		};
        /// 每个TIN包含的三角形。
        std::vector<std::vector<Triangle>> tinTriangles_;
	};
}

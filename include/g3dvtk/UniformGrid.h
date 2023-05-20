#pragma once

#include <geo3dml/UniformGrid.h>
#include <vtkSmartPointer.h>
#include <vtkUniformGrid.h>
#include <g3dvtk/ShapeHelper.h>

namespace g3dvtk {

	class UniformGrid : public geo3dml::UniformGrid {
	public:
		UniformGrid();
		/// @see geo3dml::UniformGrid#UniformGrid .
		UniformGrid(
			double originX, double originY, double originZ,
			double stepX, double stepY, double stepZ,
			int dimI, int dimJ, int dimK
		);
		virtual ~UniformGrid();

		/// @name Overrided methods inhertied from geo3dml::UniformGrid .
		//@{
		/// @see geo3dml::UniformGrid#Init .
		virtual bool Init(double originX, double originY, double originZ,
			double stepX, double stepY, double stepZ,
			int dimI, int dimJ, int dimK);
		/// @see geo3dml::UniformGrid#GetDimensions .
		virtual void GetDimensions(int& i, int& j, int& k) const;
		/// @see geo3dml::UniformGrid#GetOrigin .
		virtual void GetOrigin(double& x, double& y, double& z) const;
		/// @see geo3dml::UniformGrid#GetSteps .
		virtual void GetSteps(double& sx, double& sy, double& sz) const;
		/// @see geo3dml::UniformGrid#SetCellValidation .
		virtual void SetCellValidation(int i, int j, int k, bool beValid = true);
		/// @see geo3dml::UniformGrid#IsCellValid .
		virtual bool IsCellValid(int i, int j, int k) const;
		/// @see geo3dml::UniformGrid#CalculateCellIndex .
		virtual int CalculateCellIndex(int i, int j, int k) const;
		//@}

		/// @name Methods inherited from geo3dml::Geometry.
		//@{
		virtual bool GetMinimumBoundingRectangle(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ) const;
		virtual void SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t);
		virtual geo3dml::ShapeProperty* GetProperty(geo3dml::ShapeProperty::SamplingTarget t) const;
		//@}

	public:
		vtkUniformGrid * GetUniformGrid() const;

	private:
		vtkSmartPointer<vtkUniformGrid> uniformGrid_;
		ShapeHelper shapeHelper_;
	};
}
#pragma once

#include <geo3dml/CornerPointGrid.h>
#include <vtkPolyData.h>
#include <vtkStructuredGrid.h>
#include <vtkBlankStructuredGrid.h>
#include <vtkUnsignedCharArray.h>
#include <g3dvtk/ShapeHelper.h>

namespace g3dvtk {

	class CornerPointGrid : public geo3dml::CornerPointGrid {
	public:
		CornerPointGrid();
		/// @see geo3dml::CornerPointGrid#CornerPointGrid .
		CornerPointGrid(int dimI, int dimJ, int dimK);
		virtual ~CornerPointGrid();

		/// @name Overriding methods inherited from geo3dml::CornerPointGrid.
		//@{
		virtual bool Init(int dimI, int dimJ, int dimK);
		virtual void GetDimensions(int& i, int& j, int& k);
		virtual void AddNextPillar(double headPos[3], double tailPos[3]);
		virtual void AddNextCell(
			int i, int j, int k,
			double bottomFrontLeft[3], double bottomFrontRight[3],
			double bottomBackLeft[3], double bottomBackRight[3],
			double topFrontLeft[3], double topFrontRight[3],
			double topBackLeft[3], double topBackRight[3],
			bool beValied = true
		);
		virtual void SetCellValidation(int i, int j, int k, bool isValied = true);
		virtual void GetPillarAt(int i, int j, double headPos[3], double tailPos[3]);
		virtual void GetCellAt(int i, int j, int k,
			double bottomFrontLeft[3], double bottomFrontRight[3],
			double bottomBackLeft[3], double bottomBackRight[3],
			double topFrontLeft[3], double topFrontRight[3],
			double topBackLeft[3], double topBackRight[3],
			bool& isValid);
		//@}

		/// @name Methods inherited from geo3dml::Shape.
		//@{
		virtual bool GetBoundingBox(double& minX, double& minY, double& minZ, double& maxX, double& maxY, double& maxZ);
		virtual void SetProperty(geo3dml::ShapeProperty* prop, geo3dml::ShapeProperty::SamplingTarget t);
		virtual geo3dml::ShapeProperty* GetProperty(geo3dml::ShapeProperty::SamplingTarget t);
		//@}

	public:
		vtkPolyData* GetPillars();
		vtkStructuredGrid* GetStructuredGrid();
		vtkBlankStructuredGrid* GetBlankStructuredGrid();

	private:
		/// Prviate non-lock implementation of GetDimensions.
		void InnerGetDimensions(int& i, int& j, int& k);
		/// Private non-lock implementation of SetCellValidation.
		void InnerSetCellValidation(int i, int j, int k, bool isValied = true);

	private:
		const unsigned char Cell_Invalid = 0;
		const unsigned char Cell_Valid = 1;

	private:
		vtkSmartPointer<vtkPolyData> pillars_;
		vtkSmartPointer<vtkStructuredGrid> cells_;
		vtkSmartPointer<vtkBlankStructuredGrid> blankCells_;
		vtkSmartPointer<vtkUnsignedCharArray> blankPoints_;
		ShapeHelper shapeHelper_;
	};
}

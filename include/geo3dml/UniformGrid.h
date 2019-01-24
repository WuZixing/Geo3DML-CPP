#pragma once

#include "Geometry.h"

namespace geo3dml {

	class UniformGrid : public Geometry {
	public:
		UniformGrid();
		/// Constructor.
		/// @param originX X coordinate of the origin point.
		/// @param originY Y coordinate of the origin point.
		/// @param originZ Z coordinate of the origin point.
		/// @param stepX Interpoint space along the X axis.
		/// @param stepY Interpoint space along the Y axis.
		/// @param stepZ Interpoint space along the Z axis.
		/// @param dimI Number of cells along the X axis.
		/// @param dimJ Number of cells along the Y axis.
		/// @param dimZ Number of cells along the Z axis.
		UniformGrid(
			double originX, double originY, double originZ,
			double stepX, double stepY, double stepZ,
			int dimI, int dimJ, int dimK
		);
		virtual ~UniformGrid();
		virtual bool Init(double originX, double originY, double originZ,
			double stepX, double stepY, double stepZ,
			int dimI, int dimJ, int dimK) = 0;

	public:
		/// Get cell dimensions along X, Y and Z axes respectively.
		/// @param[out] i Number of cells along the X axis.
		/// @param[out] j Number of cells along the Y axis.
		/// @param[out] z Number of cells along the Z axis.
		virtual void GetDimensions(int& i, int& j, int& k) = 0;
		virtual void GetOrigin(double& x, double& y, double& z) = 0;
		virtual void GetSteps(double& sx, double& sy, double& sz) = 0;
		virtual void SetCellValidation(int i, int j, int k, bool beValid = true) = 0;
		virtual bool IsCellValid(int i, int j, int k) = 0;
		virtual int CalculateCellIndex(int i, int j, int k) = 0;
	};
}
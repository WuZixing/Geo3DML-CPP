#pragma once

#include "Geometry.h"

namespace geo3dml {

	class CornerPointGrid : public Geometry {
	public:
		CornerPointGrid();
		/// Constructor.
		/// @param dimI Number of cells along the X axis.
		/// @param dimJ Number of cells along the Y axis.
		/// @param dimZ Number of cells along the Z axis.
		CornerPointGrid(int dimI, int dimJ, int dimK);
		virtual ~CornerPointGrid();
		/// Initialize the grid.
		virtual bool Init(int dimI, int dimJ, int dimK) = 0;

	public:
		/// Get cell dimensions along X, Y and Z axes respectively.
		/// @param[out] i Number of cells along the X axis.
		/// @param[out] j Number of cells along the Y axis.
		/// @param[out] z Number of cells along the Z axis.
		virtual void GetDimensions(int& i, int& j, int& k) = 0;

		/// Add a pillar in the row-major order.
		/// @details Pillars must be added in the row-major order which is the I-major order..
		/// @param headPos Head point of the pillar.
		/// @param tailPos Tail point of the pillar.
		virtual void AddNextPillar(double headPos[3], double tailPos[3]) = 0;

		/// Add a cell in the row-major order.
		/// @detials Cells must be added in the row-major order. A cell is valid in default.
		/// @param i The index of the cell along X axis.
		/// @param j The index of the cell along Y axis.
		/// @param k The index of the cell along Z axis.
		/// @param bottomFrontLeft Position of the cell's bottom-fornt-left vertex.
		/// @param bottomFrontRight Position of the cell's bottom-front-right vertex.
		/// @param bottomBackLeft Position of the cell's bottom-back-left vertex.
		/// @param bottomBackRight Position of the cell's bottom-back-right vertex.
		/// @param topFrontLeft Position of the cell's top-front-left vertex.
		/// @param topFrontRight Position of the cell's top-front-right vertex.
		/// @param topBackLeft Position of the cell's top-back-left vertex.
		/// @param topBackRight Position of the cell's top-back-right vertex.
		/// @param beValid Whether this cell is valid.
		virtual void AddNextCell(
			int i, int j, int k,
			double bottomFrontLeft[3], double bottomFrontRight[3],
			double bottomBackLeft[3], double bottomBackRight[3],
			double topFrontLeft[3], double topFrontRight[3],
			double topBackLeft[3], double topBackRight[3],
			bool isValied = true
		) = 0;

		virtual void SetCellValidation(int i, int j, int k, bool beValid = true) = 0;

		virtual void GetPillarAt(int i, int j, double headPos[3], double tailPos[3]) = 0;
		virtual void GetCellAt(int i, int j, int k,
			double bottomFrontLeft[3], double bottomFrontRight[3],
			double bottomBackLeft[3], double bottomBackRight[3],
			double topFrontLeft[3], double topFrontRight[3],
			double topBackLeft[3], double topBackRight[3],
			bool& isValid) = 0;
	};
}

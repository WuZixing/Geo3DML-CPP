// UTF-8编码
#include "Utils.h"

void g3dvtk::SetBox3DFromVTKBound(const double bounds[6], geo3dml::Box3D& box) {
	box.min.x = bounds[0];
	box.max.x = bounds[1];
	box.min.y = bounds[2];
	box.max.y = bounds[3];
	box.min.z = bounds[4];
	box.max.z = bounds[5];
}

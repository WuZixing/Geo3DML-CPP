#include <g3dxml/XMLShapeWriter.h>

using namespace g3dxml;

XMLShapeWriter::XMLShapeWriter() {

}

XMLShapeWriter::~XMLShapeWriter() {

}

bool XMLShapeWriter::Write(geo3dml::Shape* shape, std::ostream& output) {
	output << "<Shape>" << std::endl;
	geo3dml::TIN* tin = dynamic_cast<geo3dml::TIN*>(shape);
	if (tin != NULL) {
		WriteTIN(tin, output);
	} else {
		geo3dml::LineString* line = dynamic_cast<geo3dml::LineString*>(shape);
		if (line != NULL) {
			WriteLineString(line, output);
		} else {
			geo3dml::Point* point = dynamic_cast<geo3dml::Point*>(shape);
			if (point != NULL) {
				WritePoint(point, output);
			} else {
				geo3dml::MultiPoint* mPoint = dynamic_cast<geo3dml::MultiPoint*>(shape);
				if (mPoint != NULL) {
					WriteMultiPoint(mPoint, output);
				} else {
					geo3dml::CornerPointGrid* cornerGrid = dynamic_cast<geo3dml::CornerPointGrid*>(shape);
					if (cornerGrid != NULL) {
						WriteCornerPointGrid(cornerGrid, output);
					} else {
						geo3dml::UniformGrid* rectGrid = dynamic_cast<geo3dml::UniformGrid*>(shape);
						if (rectGrid != NULL) {
							WriteUniformGrid(rectGrid, output);
						}
					}
				}
			}
		}
	}
	output << "</Shape>" << std::endl;
	return IsOK();
}

void XMLShapeWriter::WriteTIN(geo3dml::TIN* tin, std::ostream& output) {
	output << "<GeoTin gml:id=\"" << tin->GetID() << "\">" << std::endl;
	// vertices
	int vertexNumber = tin->GetVertexCount();
	if (vertexNumber > 0) {
		output << "<Vertices>" << std::endl;
		double x, y, z;
		for (int i = 0; i < vertexNumber; ++i) {
			tin->GetVertexAt(i, x, y, z);
			output << "<Vertex gml:srsDimension=\"3\" IndexNo=\"" << i << "\">" << x << " " << y << " " << z << "</Vertex>" << std::endl;
		}
		output << "</Vertices>" << std::endl;
	}
	// triangles
	int triangleNumber = tin->GetTriangleCount();
	if (triangleNumber > 0) {
		output << "<Triangles>" << std::endl;
		int v1, v2, v3;
		for (int i = 0; i < triangleNumber; ++i) {
			tin->GetTriangleAt(i, v1, v2, v3);
			output << "<Triangle IndexNo=\"" << i << "\">" << std::endl
				<< "<VertexList>" << v1 << " " << v2 << " " << v3 << "</VertexList>" << std::endl;
				// << "<NeighborList>-1 -1 -1</NeighborList>" << std::endl;
			output << "</Triangle>" << std::endl;
		}
		output << "</Triangles>" << std::endl;
	}
	output << "</GeoTin>" << std::endl;
}

void XMLShapeWriter::WriteLineString(geo3dml::LineString* line, std::ostream& output) {
	output << "<gml:LineString gml:id=\"" << line->GetID() << "\">" << std::endl;
	double x = 0, y = 0, z = 0;
	int vertexNumber = line->GetVertexCount();
	output << "<gml:posList srsDimension=\"3\" count=\"" << vertexNumber << "\">" << std::endl;
	for (int i = 0; i < vertexNumber; ++i) {
		line->GetVertexAt(i, x, y, z);
		output << x << " " << y << " " << z << std::endl;
	}
	output << "</gml:posList>" << std::endl;
	output << "</gml:LineString>" << std::endl;
}

void XMLShapeWriter::WritePoint(geo3dml::Point* point, std::ostream& output) {
	output << "<gml:Point gml:id=\"" << point->GetID() << "\">" << std::endl;
	double x = 0, y = 0, z = 0;
	point->GetPosition(x, y, z);
	output << "<gml:pos srsDimension=\"3\">" << x << " " << y << " " << z << "</gml:pos>" << std::endl;
	output << "</gml:Point>" << std::endl;
}

void XMLShapeWriter::WriteMultiPoint(geo3dml::MultiPoint* mPoint, std::ostream& output) {
	output << "<gml:MultiPoint gml:id=\"" << mPoint->GetID() << "\">" << std::endl
		<< "<gml:pointMembers>" << std::endl;
	double x = 0, y = 0, z = 0;
	int ptNum = mPoint->GetPointCount();
	for (int i = 0; i < ptNum; ++i) {
		mPoint->GetPointAt(i, x, y, z);
		output << "<gml:Point gml:id=\"" << i << "\">" << std::endl 
			<< "<gml:pos srsDimension=\"3\">" << x << " " << y << " " << z << "</gml:pos>" << std::endl 
			<< "</gml:Point>" << std::endl;
	}
	output << "</gml:pointMembers>" << std::endl
		<< "</gml:MultiPoint>" << std::endl;
}

void XMLShapeWriter::WriteCornerPointGrid(geo3dml::CornerPointGrid* cornerGrid, std::ostream& output) {
	output << "<GeoCornerPointGrid gml:id=\"" << cornerGrid->GetID() << "\">" << std::endl;
	int dimI = 0, dimJ = 0, dimK = 0;
	cornerGrid->GetDimensions(dimI, dimJ, dimK);
	output << "<Dimension>" << dimI << " " << dimJ << " " << dimK << "</Dimension>" << std::endl;
	// pillars
	output << "<Pillars>" << std::endl;
	double headPos[3] = { 0.0 }, tailPos[3] = {0.0};
	for (int j = 0; j <= dimJ; ++j) {
		for (int i = 0; i <= dimI; ++i) {
			cornerGrid->GetPillarAt(i, j, headPos, tailPos);
			output << "<Pillar>" << std::endl
				<< "<HeadPos>" << headPos[0] << " " << headPos[1] << " " << headPos[2] << "</HeadPos>" << std::endl
				<< "<TailPos>" << tailPos[0] << " " << tailPos[1] << " " << tailPos[2] << "</TailPos>" << std::endl
				<< "</Pillar>" << std::endl;
		}
	}
	output << "</Pillars>" << std::endl;
	// cells
	output << "<Cells ZValue=\"elevation\">" << std::endl;
	double bottomFrontLeft[3], bottomFrontRight[3], bottomBackLeft[3], bottomBackRight[3], topFrontLeft[3], topFrontRight[3], topBackLeft[3], topBackRight[3];
	bool isValid = true;
	for (int k = 0; k < dimK; ++k) {
		for (int j = 0; j < dimJ; ++j) {
			for (int i = 0; i < dimI; ++i) {
				cornerGrid->GetCellAt(i, j, k, bottomFrontLeft, bottomFrontRight, bottomBackLeft, bottomBackRight, topFrontLeft, topFrontRight, topBackLeft, topBackRight, isValid);
				output << "<Cell Valid=\"" << isValid << "\">" << bottomFrontLeft[2] << " " << bottomFrontRight[2] << " " << bottomBackLeft[2] << " " << bottomBackRight[2] << " " << topFrontLeft[2] << " " << topFrontRight[2] << " " << topBackLeft[2] << " " << topBackRight[2] << "</Cell>" << std::endl;
			}
		}
	}
	output << "</Cells>" << std::endl;
	output << "</GeoCornerPointGrid>" << std::endl;
}

void XMLShapeWriter::WriteUniformGrid(geo3dml::UniformGrid* uniformGrid, std::ostream& output) {
	output << "<GeoUniformGrid gml:id=\"" << uniformGrid->GetID() << "\">" << std::endl;
	double x = 0, y = 0, z = 0;
	uniformGrid->GetOrigin(x, y, z);
	output << "<Origin>" << x << " " << y << " " << z << "</Origin>" << std::endl;
	uniformGrid->GetSteps(x, y, z);
	output << "<Steps>" << x << " " << y << " " << z << "</Steps>" << std::endl;
	int dimI = 0, dimJ = 0, dimK = 0;
	uniformGrid->GetDimensions(dimI, dimJ, dimK);
	output << "<Dimension>" << dimI << " " << dimJ << " " << dimK << "</Dimension>" << std::endl;
	// blank cells
	output << "<Cells>" << std::endl;
	for (int k = 0; k < dimK; ++k) {
		for (int j = 0; j < dimJ; ++j) {
			for (int i = 0; i < dimI; ++i) {
				if (!uniformGrid->IsCellValid(i, j, k)) {
					output << "<Cell I=\"" << i << "\" J=\"" << j << "\" K=\"" << k << "\" Valid=\"false\"/>" << std::endl;
				}
			}
		}
	}
	output << "</Cells>" << std::endl;
	output << "</GeoUniformGrid>" << std::endl;
}

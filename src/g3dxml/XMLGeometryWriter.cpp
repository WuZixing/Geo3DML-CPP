#include <g3dxml/XMLGeometryWriter.h>
#include <g3dxml/MultiTIN.h>

using namespace g3dxml;

XMLGeometryWriter::XMLGeometryWriter() {

}

XMLGeometryWriter::~XMLGeometryWriter() {

}

bool XMLGeometryWriter::Write(geo3dml::Geometry* geo, std::ostream& output, SchemaVersion v) {
	output << "<Shape>" << std::endl;
	geo3dml::TIN* tin = dynamic_cast<geo3dml::TIN*>(geo);
	if (tin != nullptr) {
		WriteTIN(tin, output);
	} else {
		geo3dml::MultiTIN* mTin = dynamic_cast<geo3dml::MultiTIN*>(geo);
		if (mTin != nullptr) {
			MultiTIN mTinWriter(nullptr);
			mTinWriter.Write(mTin, output);
		} else {
			geo3dml::LineString* line = dynamic_cast<geo3dml::LineString*>(geo);
			if (line != nullptr) {
				WriteLineString(line, output);
			} else {
				geo3dml::MultiLineString* mLine = dynamic_cast<geo3dml::MultiLineString*>(geo);
				if (mLine != nullptr) {
					WriteMultiLineString(mLine, output);
				} else {
					geo3dml::Point* point = dynamic_cast<geo3dml::Point*>(geo);
					if (point != nullptr) {
						WritePoint(point, output);
					} else {
						geo3dml::Annotation* annotation = dynamic_cast<geo3dml::Annotation*>(geo);
						if (annotation != nullptr) {
							WriteAnnotation(annotation, output);
						} else {
							geo3dml::MultiPoint* mPoint = dynamic_cast<geo3dml::MultiPoint*>(geo);
							if (mPoint != nullptr) {
								WriteMultiPoint(mPoint, output);
							} else {
								geo3dml::CornerPointGrid* cornerGrid = dynamic_cast<geo3dml::CornerPointGrid*>(geo);
								if (cornerGrid != nullptr) {
									WriteCornerPointGrid(cornerGrid, output);
								} else {
									if (v != Schema_1_0) {
										geo3dml::TriangularPrismVolume* gtpGrid = dynamic_cast<geo3dml::TriangularPrismVolume*>(geo);
										if (gtpGrid != nullptr) {
											WriteTriangularPrismVolume(gtpGrid, output);
										} else {
											geo3dml::RectifiedGrid* rectGrid = dynamic_cast<geo3dml::RectifiedGrid*>(geo);
											if (rectGrid != nullptr) {
												WriteRectifiedGrid(rectGrid, output);
											} else {
												geo3dml::TetrahedronVolume* tetraVolume = dynamic_cast<geo3dml::TetrahedronVolume*>(geo);
												if (tetraVolume != nullptr) {
													WriteTetrahedronVolume(tetraVolume, output);
												} else {
													geo3dml::CuboidVolume* cuboidVolume = dynamic_cast<geo3dml::CuboidVolume*>(geo);
													if (cuboidVolume != nullptr) {
														WriteCuboidVolume(cuboidVolume, output);
													} else {
														geo3dml::TruncatedRegularGrid* trGrid = dynamic_cast<geo3dml::TruncatedRegularGrid*>(geo);
														if (trGrid != nullptr) {
															WriteTruncatedRegularGrid(trGrid, output);
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	output << "</Shape>" << std::endl;
	return IsOK();
}

void XMLGeometryWriter::WriteTIN(geo3dml::TIN* tin, std::ostream& output) {
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

void XMLGeometryWriter::WriteLineString(geo3dml::LineString* line, std::ostream& output) {
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

void XMLGeometryWriter::WriteMultiLineString(geo3dml::MultiLineString* mLine, std::ostream& output) {
	output << "<gml:MultiCurve gml:id=\"" << mLine->GetID() << "\">" << std::endl;
	double x = 0, y = 0, z = 0;
	int lineNumber = mLine->GetLineStringCount();
	for (int i = 0; i < lineNumber; ++i) {
		int vertexNumber = mLine->GetVertexCountOfLineString(i);
		output << "<gml:curveMember>" << std::endl
			<< "<gml:LineString>" << std::endl
			<< "<gml:posList srsDimension=\"3\" count=\"" << vertexNumber << "\">" << std::endl;
		for (int j = 0; j < vertexNumber; ++j) {
			mLine->GetVertexOfLineString(i, j, x, y, z);
			output << x << " " << y << " " << z << std::endl;
		}
		output << "</gml:posList>" << std::endl
			<< "</gml:LineString>" << std::endl
			<< "</gml:curveMember>" << std::endl;
	}
	output << "</gml:MultiCurve>" << std::endl;
}

void XMLGeometryWriter::WritePoint(geo3dml::Point* point, std::ostream& output) {
	output << "<gml:Point gml:id=\"" << point->GetID() << "\">" << std::endl;
	double x = 0, y = 0, z = 0;
	point->GetPosition(x, y, z);
	output << "<gml:pos srsDimension=\"3\">" << x << " " << y << " " << z << "</gml:pos>" << std::endl;
	output << "</gml:Point>" << std::endl;
}

void XMLGeometryWriter::WriteAnnotation(geo3dml::Annotation* annotation, std::ostream& output) {
	output << "<GeoAnnotation gml:id=\"" << annotation->GetID() << "\">" << std::endl
		<< "<gml:pointMembers>" << std::endl;
	double x = 0, y = 0, z = 0;
	int ptNum = annotation->GetPointCount();
	for (int i = 0; i < ptNum; ++i) {
		annotation->GetPointAt(i, x, y, z);
		output << "<gml:Point gml:id=\"" << i << "\">" << std::endl
			<< "<gml:pos srsDimension=\"3\">" << x << " " << y << " " << z << "</gml:pos>" << std::endl
			<< "</gml:Point>" << std::endl;
	}
	output << "</gml:pointMembers>" << std::endl
		<< "<Labels>" << std::endl;
	for (int i = 0; i < ptNum; ++i) {
		std::string label = annotation->GetLabelOfPointAt(i);
		output << "<Label IndexNo=\"" << i << "\">" << label << "</Label>" << std::endl;
	}
	output << "</Labels>" << std::endl
		<< "</GeoAnnotation>" << std::endl;
}

void XMLGeometryWriter::WriteMultiPoint(geo3dml::MultiPoint* mPoint, std::ostream& output) {
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

void XMLGeometryWriter::WriteCornerPointGrid(geo3dml::CornerPointGrid* cornerGrid, std::ostream& output) {
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

void XMLGeometryWriter::WriteTriangularPrismVolume(geo3dml::TriangularPrismVolume* gtpGrid, std::ostream& output) {
	output << "<GeoTriangularPrismVolume gml:id=\"" << gtpGrid->GetID() << "\">" << std::endl;
	// vertices
	int vertexNumber = gtpGrid->GetVertexCount();
	if (vertexNumber > 0) {
		output << "<Vertices>" << std::endl;
		double x, y, z;
		for (int i = 0; i < vertexNumber; ++i) {
			gtpGrid->GetVertexAt(i, x, y, z);
			output << "<Vertex gml:srsDimension=\"3\" IndexNo=\"" << i << "\">" << x << " " << y << " " << z << "</Vertex>" << std::endl;
		}
		output << "</Vertices>" << std::endl;
	}
	// prisms
	int prismNumber = gtpGrid->GetPrismCount();
	if (prismNumber > 0) {
		output << "<Prisms>" << std::endl;
		int tv1, tv2, tv3, bv1, bv2, bv3;
		for (int i = 0; i < prismNumber; ++i) {
			gtpGrid->GetPrismAt(i, tv1, tv2, tv3, bv1, bv2, bv3);
			output << "<Prism IndexNo=\"" << i << "\">" << std::endl
				<< "<TopTriangle>" << tv1 << " " << tv2 << " " << tv3 << "</TopTriangle>" << std::endl
				<< "<BottomTriangle>" << bv1 << " " << bv2 << " " << bv3 << "</BottomTriangle>" << std::endl;
			// << "<NeighborList>-1 -1 -1</NeighborList>" << std::endl;
			output << "</Prism>" << std::endl;
		}
		output << "</Prisms>" << std::endl;
	}
	output << "</GeoTriangularPrismVolume>" << std::endl;
}

void XMLGeometryWriter::WriteRectifiedGrid(const geo3dml::RectifiedGrid* grid, std::ostream& output) {
	output << "<gml:RectifiedGrid gml:id=\"" << grid->GetID() << "\" gml:dimension=\"3\">" << std::endl;
	// limits
	int lowI = 0, lowJ = 0, lowK = 0, highI = 0, highJ = 0, highK = 0;
	grid->GetCellRange(lowI, lowJ, lowK, highI, highJ, highK);
	output << "<gml:limits>" << std::endl
		<< "<gml:GridEnvelope>" << std::endl
		<< "<gml:low>" << lowI << ' ' << lowJ << ' ' << lowK << "</gml:low>" << std::endl
		<< "<gml:high>" << highI << ' ' << highJ << ' ' << highK << "</gml:high>" << std::endl
		<< "</gml:GridEnvelope>" << std::endl
		<< "</gml:limits>" << std::endl;
	// axis label
	output << "<gml:axisLabels>I J K</gml:axisLabels>" << std::endl;
	// origin
	const geo3dml::Point3D& origin = grid->Origin();
	output << "<gml:origin>" << std::endl
		<< "<gml:Point>" << origin.x << ' ' << origin.y << ' ' << origin.z << "</gml:Point>" << std::endl
		<< "</gml:origin>" << std::endl;
	// offset vectors
	geo3dml::Vector3D vectors[3];
	vectors[0] = grid->AxisI();
	vectors[1] = grid->AxisJ();
	vectors[2] = grid->AxisK();
	for (int i = 0; i < 3; ++i) {
		output << "<gml:offsetVector>" << vectors[i].X() << ' ' << vectors[i].Y() << ' ' << vectors[i].Z() << "</gml:offsetVector>" << std::endl;
	}
	output << "</gml:RectifiedGrid>" << std::endl;
}

void XMLGeometryWriter::WriteTetrahedronVolume(const geo3dml::TetrahedronVolume* tetraVolume, std::ostream& output) {
	output << "<GeoTetrahedronVolume gml:id=\"" << tetraVolume->GetID() << "\">" << std::endl;
	// vertices
	int vertexNumber = tetraVolume->GetVertexCount();
	if (vertexNumber > 0) {
		output << "<Vertices>" << std::endl;
		double x, y, z;
		for (int i = 0; i < vertexNumber; ++i) {
			tetraVolume->GetVertexAt(i, x, y, z);
			output << "<Vertex gml:srsDimension=\"3\" IndexNo=\"" << i << "\">" << x << ' ' << y << ' ' << z << "</Vertex>" << std::endl;
		}
		output << "</Vertices>" << std::endl;
	}
	// tetrahedrons
	int tetraNumber = tetraVolume->GetTetrahedronCount();
	if (tetraNumber > 0) {
		output << "<Tetrahedrons>" << std::endl;
		int v1, v2, v3, v4;
		for (int i = 0; i < tetraNumber; ++i) {
			tetraVolume->GetTetrahedronAt(i, v1, v2, v3, v4);
			output << "<Tetrahedron IndexNo=\"" << i << "\">" << std::endl
				<< "<VertexList>" << v1 << ' ' << v2 << ' ' << v3 << ' ' << v4 << "</VertexList>" << std::endl;
			// << "<NeighborList>-1 -1 -1 -1</NeighborList>" << std::endl;
			output << "</Tetrahedron>" << std::endl;
		}
		output << "</Tetrahedrons>" << std::endl;
	}
	output << "</GeoTetrahedronVolume>" << std::endl;
}

void XMLGeometryWriter::WriteCuboidVolume(const geo3dml::CuboidVolume* cuboidVolume, std::ostream& output) {
	output << "<GeoCuboidVolume gml:id=\"" << cuboidVolume->GetID() << "\">" << std::endl;
	// vertices
	int vertexNumber = cuboidVolume->GetVertexCount();
	if (vertexNumber > 0) {
		output << "<Vertices>" << std::endl;
		double x, y, z;
		for (int i = 0; i < vertexNumber; ++i) {
			cuboidVolume->GetVertexAt(i, x, y, z);
			output << "<Vertex gml:srsDimension=\"3\" IndexNo=\"" << i << "\">" << x << ' ' << y << ' ' << z << "</Vertex>" << std::endl;
		}
		output << "</Vertices>" << std::endl;
	}
	// cuboids
	int cuboidNumber = cuboidVolume->GetCuboidCount();
	if (cuboidNumber > 0) {
		output << "<Cuboids>" << std::endl;
		int v1, v2, v3, v4, v5, v6, v7, v8;
		for (int i = 0; i < cuboidNumber; ++i) {
			cuboidVolume->GetCuboidAt(i, v1, v2, v3, v4, v5, v6, v7, v8);
			output << "<Cuboid IndexNo=\"" << i << "\">" << std::endl
				<< "<VertexList>" << v1 << ' ' << v2 << ' ' << v3 << ' ' << v4 << ' ' << v5 << ' ' << v6 << ' ' << v7 << ' ' << v8 << "</VertexList>" << std::endl;
			output << "</Cuboid>" << std::endl;
		}
		output << "</Cuboids>" << std::endl;
	}
	output << "</GeoCuboidVolume>" << std::endl;
}

void XMLGeometryWriter::WriteTruncatedRegularGrid(const geo3dml::TruncatedRegularGrid* trGrid, std::ostream& output) {
	output << "<GeoTruncatedRegularGrid gml:id=\"" << trGrid->GetID() << "\">" << std::endl;
	// plane grid 
	const geo3dml::Point3D& origin = trGrid->GetPlaneGridOrigin();
	double stepX = 0, stepY = 0;
	trGrid->GetPlaneGridCellSize(stepX, stepY);
	int dimX = 0, dimY = 0;
	trGrid->GetPlaneGridCellNumber(dimX, dimY);
	output << "<PlaneGrid>" << std::endl
		<< "<Origin gml:srsDimension=\"3\">" << origin.x << ' ' << origin.y << ' ' << origin.z << "</Origin>" << std::endl
		<< "<Azimuth>" << trGrid->GetPlaneGridAzimuth() << "</Azimuth>" << std::endl
		<< "<Steps>" << stepX << ' ' << stepY << "</Steps>" << std::endl
		<< "<Dimension>" << dimX << ' ' << dimY << "</Dimension>" << std::endl
		<< "</PlaneGrid>";
	// vertices
	int vertexNumber = trGrid->GetVertexCount();
	output << "<Vertices>" << std::endl;
	double x = 0, y = 0, z = 0;
	for (int n = 0; n < vertexNumber; ++n) {
		trGrid->GetVertexAt(n, x, y, z);
		output << "<Vertex gml:srsDimension=\"3\" IndexNo=\"" << n << "\">" << x << ' ' << y << ' ' << z << "</Vertex>" << std::endl;
	}
	output << "</Vertices>" << std::endl;
	// faces
	std::list<int> idList;
	int faceNumber = trGrid->GetFaceCount();
	output << "<Faces>" << std::endl;
	for (int n = 0; n < faceNumber; ++n) {
		trGrid->GetFaceAt(n, idList);
		output << "<Face IndexNo=\"" << n << "\">" << std::endl;
		output << "<VertexList Length=\"" << idList.size() << "\">";
		auto cItor = idList.cbegin();
		if (cItor != idList.cend()) {
			output << *cItor;
			++cItor;
		}
		for (; cItor != idList.cend(); ++cItor) {
			output << ' ' << *cItor;
		}
		output << "</VertexList>" << std::endl;
		output << "</Face>" << std::endl;
	}
	output << "</Faces>" << std::endl;
	// cells
	int i = 0, j = 0, k = 0;
	int cellNumber = trGrid->GetCellCount();
	output << "<Cells>" << std::endl;
	for (int n = 0; n < cellNumber; ++n) {
		trGrid->GetCellAt(n, idList, i, j, k);
		output << "<Cell IndexNo=\"" << n << "\" I=\"" << i << "\" J=\"" << j << "\" K=\"" << k << "\">" << std::endl;
		output << "<FaceList Length=\"" << idList.size() << "\">";
		auto cItor = idList.cbegin();
		if (cItor != idList.cend()) {
			output << *cItor;
			++cItor;
		}
		for (; cItor != idList.cend(); ++cItor) {
			output << ' ' << *cItor;
		}
		output << "</FaceList>" << std::endl;
		output << "</Cell>" << std::endl;
	}
	output << "</Cells>" << std::endl;
	output << "</GeoTruncatedRegularGrid>" << std::endl;
}

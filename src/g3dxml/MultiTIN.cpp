// UTF-8编码
#include <g3dxml/MultiTIN.h>
#include <g3dxml/XMLTINReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string MultiTIN::Element = "MultiSurface";

MultiTIN::MultiTIN(geo3dml::ObjectFactory* factory) {
    g3dFactory_ = factory;
}

MultiTIN::~MultiTIN() {

}

geo3dml::MultiTIN* MultiTIN::Read(xmlTextReaderPtr reader) {
	geo3dml::MultiTIN* mTin = g3dFactory_->NewMultiTIN();
	mTin->SetID(XMLReaderHelper::AttributeGMLID(reader));
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, XMLTINReader::Element)) {
				XMLTINReader tinReader(g3dFactory_);
				geo3dml::TIN* tin = tinReader.ReadTIN(reader);
				if (tin != nullptr) {
					mTin->AddTIN(tin);
					delete tin;
					tin = nullptr;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element);
		SetStatus(false, err);
	}
	if (!IsOK()) {
		delete mTin;
		mTin = nullptr;
	}
	return mTin;
}

void MultiTIN::Write(geo3dml::MultiTIN* mTin, std::ostream& output) const {
    output << "<gml:" << Element << ">" << std::endl;
    for (int m = 0; m < mTin->GetTINCount(); ++m) {
		output << "<gml:surfaceMember>" << std::endl
			<< "<GeoTin>" << std::endl;
		// 顶点
		int vertexNumber = mTin->GetVertexCountOfTIN(m);
		if (vertexNumber > 0) {
			output << "<Vertices>" << std::endl;
			double x, y, z;
			for (int n = 0; n < vertexNumber; ++n) {
				mTin->GetVertexOfTIN(m, n, x, y, z);
				output << "<Vertex gml:srsDimension=\"3\" IndexNo=\"" << n << "\">" << x << " " << y << " " << z << "</Vertex>" << std::endl;
			}
			output << "</Vertices>" << std::endl;
		}
		// 三角形 
		int triangleNumber = mTin->GetTriangleCountOfTIN(m);
		if (triangleNumber > 0) {
			output << "<Triangles>" << std::endl;
			int v1, v2, v3;
			for (int n = 0; n < triangleNumber; ++n) {
				mTin->GetTriangleOfTIN(m, n, v1, v2, v3);
				output << "<Triangle IndexNo=\"" << n << "\">" << std::endl
					<< "<VertexList>" << v1 << " " << v2 << " " << v3 << "</VertexList>" << std::endl;
				// << "<NeighborList>-1 -1 -1</NeighborList>" << std::endl;
				output << "</Triangle>" << std::endl;
			}
			output << "</Triangles>" << std::endl;
		}
		output << "</GeoTin>" << std::endl
			<< "</gml:surfaceMember>" << std::endl;
    }
    output << "</gml:" << Element << ">" << std::endl;
}

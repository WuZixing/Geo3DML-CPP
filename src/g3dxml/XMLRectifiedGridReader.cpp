// UTF-8编码
#include <g3dxml/XMLRectifiedGridReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

const std::string XMLRectifiedGridReader::Element = "RectifiedGrid";
const std::string XMLRectifiedGridReader::Element_Low = "low";
const std::string XMLRectifiedGridReader::Element_High = "high";
const std::string XMLRectifiedGridReader::Element_Origin = "Point";
const std::string XMLRectifiedGridReader::Element_OffsetVector = "offsetVector";

        /// @brief 构造函数。
        /// @param factory Geo3DML对象的工厂类对象。该对象的内存由调用者负责管理。
XMLRectifiedGridReader::XMLRectifiedGridReader(geo3dml::ObjectFactory* factory) : XMLIO() {
    g3dFactory_ = factory;
}

XMLRectifiedGridReader::~XMLRectifiedGridReader() {

}

geo3dml::RectifiedGrid* XMLRectifiedGridReader::ReadGrid(xmlTextReaderPtr reader) {
    geo3dml::RectifiedGrid* grid = nullptr;
    std::string id = XMLReaderHelper::AttributeGMLID(reader);
    std::string str = XMLReaderHelper::Attribute(reader, "gml:dimension");
    int dim = strtol(str.c_str(), nullptr, 10);
    if (dim != 3) {
        SetStatus(false, std::string("unsupported dimension: ") + str);
        return grid;
    }
    int lowI = 0, lowJ = 0, lowK = 0, highI = -1, highJ = -1, highK = -1;
    geo3dml::Point3D origin;
    geo3dml::Vector3D vectors[3] = {
        geo3dml::Vector3D(1, 0, 0), geo3dml::Vector3D(0, 1, 0), geo3dml::Vector3D(0, 0, 1)
    };
    int vecIndex = -1;
    int status = xmlTextReaderRead(reader);
    while (status == 1) {
        const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
        int nodeType = xmlTextReaderNodeType(reader);
        if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
            break;
        } else if (nodeType == XML_READER_TYPE_ELEMENT) {
            if (geo3dml::IsiEqual(localName, Element_Low)) {
                if (!XMLReaderHelper::TextNode(reader, Element_Low, str)) {
                    SetStatus(false, str);
                    break;
                }
                char* end = nullptr;
                lowI = strtol(str.c_str(), &end, 10);
                lowJ = strtol(end, &end, 10);
                lowK = strtol(end, nullptr, 10);
            } else if (geo3dml::IsiEqual(localName, Element_High)) {
                if (!XMLReaderHelper::TextNode(reader, Element_High, str)) {
                    SetStatus(false, str);
                    break;
                }
                char* end = nullptr;
                highI = strtol(str.c_str(), &end, 10);
                highJ = strtol(end, &end, 10);
                highK = strtol(end, nullptr, 10);
            } else if (geo3dml::IsiEqual(localName, Element_Origin)) {
                if (!XMLReaderHelper::TextNode(reader, Element_Origin, str)) {
                    SetStatus(false, str);
                    break;
                }
                char* end = nullptr;
                origin.x = strtod(str.c_str(), &end);
                origin.y = strtod(end, &end);
                origin.z = strtod(end, nullptr);
            } else if (geo3dml::IsiEqual(localName, Element_OffsetVector)) {
                if (!XMLReaderHelper::TextNode(reader, Element_OffsetVector, str)) {
                    SetStatus(false, str);
                    break;
                }
                ++vecIndex;
                if (vecIndex < 3) {
                    char* end = nullptr;
                    vectors[vecIndex].X(strtod(str.c_str(), &end));
                    vectors[vecIndex].Y(strtod(end, &end));
                    vectors[vecIndex].Z(strtod(end, nullptr));
                }
            }
        }
        status = xmlTextReaderRead(reader);
    }
    if (status != 1) {
        std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element);
        SetStatus(false, err);
    }
    if (IsOK()) {
        origin.x += vectors[0].X() * lowI;
        origin.y += vectors[0].Y() * lowJ;
        origin.z += vectors[0].Z() * lowK;
        grid = g3dFactory_->NewRectifiedGrid(origin, vectors[0], vectors[1], vectors[2], highI - lowI + 1, highJ - lowJ + 1, highK - lowK + 1);
        if (grid != nullptr) {
            grid->SetID(id);
        }
    }
    return grid;
}

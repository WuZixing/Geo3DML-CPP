// UTF-8编码
#pragma once

#include <g3dxml/XMLIO.h>
#include <g3dxml/XMLReaderHelper.h>

namespace g3dxml {

    class XMLTruncatedRegularGridReader: public XMLIO {
    public:
        /// Name of the SGrid element.
        static const std::string Element;

    public:
        /// 构造函数。
        /// @param factory 创建Geo3DML对象的工厂对象。该对象由调用者负责管理。
        XMLTruncatedRegularGridReader(geo3dml::ObjectFactory* factory);
        virtual ~XMLTruncatedRegularGridReader();

        geo3dml::TruncatedRegularGrid* ReadGrid(xmlTextReaderPtr reader);

    private:
        bool ReadPlaneGrid(xmlTextReaderPtr reader, geo3dml::TruncatedRegularGrid* trGrid);
        bool ReadVertex(xmlTextReaderPtr reader, geo3dml::TruncatedRegularGrid* trGrid);
        bool ReadFace(xmlTextReaderPtr reader, geo3dml::TruncatedRegularGrid* trGrid);
        bool ReadCell(xmlTextReaderPtr reader, geo3dml::TruncatedRegularGrid* trGrid);

    private:
        static const std::string Element_PlaneGrid;
        static const std::string Element_Vertex;
        static const std::string Element_Face;
        static const std::string Element_Cell;

    private:
        geo3dml::ObjectFactory* g3dFactory_;
    };
}

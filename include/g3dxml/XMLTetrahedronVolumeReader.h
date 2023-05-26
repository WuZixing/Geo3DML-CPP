// UTF-8编码
#pragma once

#include <g3dxml/XMLIO.h>
#include <g3dxml/XMLReaderHelper.h>

namespace g3dxml {

    class XMLTetrahedronVolumeReader : public XMLIO {
    public:
        /// Name of the tetrahedron volume element.
        static const std::string Element;

    public:
        /// 构造函数。
        /// @param factory 创建Geo3DML对象的工厂对象。该对象由调用者负责管理。
        XMLTetrahedronVolumeReader(geo3dml::ObjectFactory* factory);
        virtual ~XMLTetrahedronVolumeReader();

        geo3dml::TetrahedronVolume* ReadTetrahedronVolume(xmlTextReaderPtr reader);

    private:
        bool ReadVertex(xmlTextReaderPtr reader, geo3dml::TetrahedronVolume* tetraVolume);
        bool ReadTetrahedron(xmlTextReaderPtr reader, geo3dml::TetrahedronVolume* tetraVolume);

    private:
        static const std::string Element_Vertex;
        static const std::string Element_Tetrahedron;
        static const std::string Element_VertexList;

    private:
        geo3dml::ObjectFactory* g3dFactory_;
    };
}


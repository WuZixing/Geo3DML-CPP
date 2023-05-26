// UTF-8编码
#pragma once

#include <g3dxml/XMLIO.h>
#include <g3dxml/XMLReaderHelper.h>

namespace g3dxml {

    class XMLCuboidVolumeReader : public XMLIO {
    public:
        /// Name of the cuboid volume element.
        static const std::string Element;

    public:
        /// 构造函数。
        /// @param factory 创建Geo3DML对象的工厂对象。该对象由调用者负责管理。
        XMLCuboidVolumeReader(geo3dml::ObjectFactory* factory);
        virtual ~XMLCuboidVolumeReader();

        geo3dml::CuboidVolume* ReadCuboidVolume(xmlTextReaderPtr reader);

    private:
        bool ReadVertex(xmlTextReaderPtr reader, geo3dml::CuboidVolume* cuboidVolume);
        bool ReadCuboid(xmlTextReaderPtr reader, geo3dml::CuboidVolume* cuboidVolume);

    private:
        static const std::string Element_Vertex;
        static const std::string Element_Cuboid;
        static const std::string Element_VertexList;

    private:
        geo3dml::ObjectFactory* g3dFactory_;
    };
}

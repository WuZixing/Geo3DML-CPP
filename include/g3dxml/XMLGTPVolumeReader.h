// UTF-8编码
#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

    /// @brief 广义三棱柱数据读入方法。
    class XMLGTPVolumeReader : public XMLIO {
    public:
        /// XML元素的名字。
        static const std::string Element;

    public:
        /// @brief 构造函数。
        /// @param factory Geo3DML对象的工厂类对象。该对象的内存由调用者负责管理。
        XMLGTPVolumeReader(geo3dml::ObjectFactory* factory);
        virtual ~XMLGTPVolumeReader();

        geo3dml::GTPVolume* ReadVolume(xmlTextReaderPtr reader);

    private:
        bool ReadVertex(xmlTextReaderPtr reader, geo3dml::GTPVolume* gtp);
        bool ReadPrism(xmlTextReaderPtr reader, geo3dml::GTPVolume* gtp);

    private:
        static const std::string Element_Vertex;
        static const std::string Element_Prism;
        static const std::string Element_TopTriangle;
        static const std::string Element_BottomTriangle;
        static const std::string Element_NeighborList;

    private:
        geo3dml::ObjectFactory* g3dFactory_;
    };
}

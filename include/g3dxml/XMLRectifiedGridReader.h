// UTF-8编码
#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

    /// @brief RectifiedGrid 数据读入方法。
    class XMLRectifiedGridReader : public XMLIO {
    public:
        /// XML元素的名字。
        static const std::string Element;

    public:
        /// @brief 构造函数。
        /// @param factory Geo3DML对象的工厂类对象。该对象的内存由调用者负责管理。
        XMLRectifiedGridReader(geo3dml::ObjectFactory* factory);
        virtual ~XMLRectifiedGridReader();

        geo3dml::RectifiedGrid* ReadGrid(xmlTextReaderPtr reader);

    private:

    private:
        static const std::string Element_Low;
        static const std::string Element_High;
        static const std::string Element_Origin;
        static const std::string Element_OffsetVector;

    private:
        geo3dml::ObjectFactory* g3dFactory_;
    };
}

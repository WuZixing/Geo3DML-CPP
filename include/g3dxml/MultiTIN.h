// UTF-8编码
#pragma once

#include <iostream>
#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {
	class MultiTIN : public XMLIO {
	public:
		/// Name of the geometry element.
		static const std::string Element;

	public:
		/// 构造函数。
        /// @param factory Geo3DML对象的工厂类。其内存由调用者管理。
		MultiTIN(geo3dml::ObjectFactory* factory);
		virtual ~MultiTIN();

        /// @brief 从XML文档中读取一个多TIN对象。
        /// @param reader XML文档的读取器。
		/// @return 返回读取的对象。
		geo3dml::MultiTIN* Read(xmlTextReaderPtr reader);

        /// @brief 输出一个多TIN对象到XML文档。
		/// @param mTin		要被输出的多TIN对象。
		/// @param output	输出流。
		void Write(geo3dml::MultiTIN* mTin, std::ostream& output) const;

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}

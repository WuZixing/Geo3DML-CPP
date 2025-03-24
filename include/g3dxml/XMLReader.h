// UTF-8编码
#pragma once

#include <geo3dml/ObjectFactory.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {
	/// @brief 从XML为你教案读取Geo3DML数据的工具类。
	class XMLReader : public XMLIO {
	public:
		/// 构造函数。
		/// @param factory 构造Geo3DML对象的工厂类对象。该对象在读取文件期间应一直有效，并由调用者负责销毁。如果该参数为nullptr，则使用缺省的构造类对象（此时，构造类对象由本XMLReader对象负责管理）。
		XMLReader(geo3dml::ObjectFactory* factory = nullptr);
		virtual ~XMLReader();

		/// Load Geo3DML data from XML file.
		/// The current working directory should be set as the file's direcotry before calling this method.
		geo3dml::Object* LoadXMLFile(const std::string& file);

	private:
		geo3dml::ObjectFactory* g3dFactory_;
		/// g3dFactory_对象是否是本对象私有的。私有的ObjectFactory应在本对象析构时被销毁。
		bool isPrivateFactory_;
	};
}

// UTF-8编码
#pragma once

#include <libxml/xmlreader.h>
#include <geo3dml/ObjectFactory.h>

namespace g3dxml {

	class XMLReaderHelper {
	public:
		/// Detect file's encoding.
		static std::string DectectFileEncoding(const std::string& filePath);
		static bool IsUTF8(const std::string& encodingName);
		static std::string FormatErrorMessageAboutEncoding(const std::string& encodingName, const std::string& filePath);

		/// Check whether a path is relative.
		static bool IsRelativePath(const std::string& path);

		/// Get an element's text value.
		/// @param reader the XML reader.
		/// @param element name of the element to be parsed.
		/// @param[out] str Output the text value of the element if no error happended, otherwise it will store the error message.
		/// @return Return true if parsing succeeded without any error, otherwise false.
		static bool TextNode(xmlTextReaderPtr reader, const std::string& element, std::string& str);

		/// @brief 读取XML标签的gml:id属性值。
		/// @param reader XML文件读取工具。
		/// @return 标签中的gml:id属性值。
		static std::string AttributeGMLID(xmlTextReaderPtr reader);
		/// @brief 读取XML标签的某属性值。
		/// @param reader XML文件读取工具。
		/// @param attribute XML标签的属性名字。
		/// @return 标签中的属性值。
		static std::string Attribute(xmlTextReaderPtr reader, const std::string& attribute);
		/// @brief 从XML标签的 xlink:href 属性中提取ID值。
		/// @param reader XML文件读取工具。
		/// @return ID属性值。
		static std::string AttributeIdInHref(xmlTextReaderPtr reader);

		static std::string FormatErrorMessageWithPosition(xmlTextReaderPtr reader, const std::string& message);
	};
}

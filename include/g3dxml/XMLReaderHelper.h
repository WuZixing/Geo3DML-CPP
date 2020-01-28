#pragma once

#include <libxml/xmlreader.h>
#include <geo3dml/ObjectFactory.h>

namespace g3dxml {

	class XMLReaderHelper {
	public:
		/// Detect file's encoding.
		static std::string DectectFileEncoding(const std::string& file);
		static bool IsUTF8(const std::string& encodingName);

		/// Get an element's text value.
		/// @param reader the XML reader.
		/// @param element name of the element to be parsed.
		/// @param[out] str Output the text value of the element if no error happended, otherwise it will store the error message.
		/// @return Return true if parsing succeeded without any error, otherwise false.
		static bool TextNode(xmlTextReaderPtr reader, const std::string& element, std::string& str);

		static std::string AttributeGMLID(xmlTextReaderPtr reader);
		static std::string Attribute(xmlTextReaderPtr reader, const std::string& attribute);

		static std::string FormatErrorMessageWithPosition(xmlTextReaderPtr reader, const std::string& message);
	};
}

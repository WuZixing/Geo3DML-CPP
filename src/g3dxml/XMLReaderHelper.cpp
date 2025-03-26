#include <g3dxml/XMLReaderHelper.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include <regex>
#include <geo3dml/Utils.h>

using namespace g3dxml;

#if defined(_WIN32)
#include <windows.h>
/**
* __xmlIOWin32UTF8ToWChar:
* @u8String:  uft-8 string
*
* Convert a string from utf-8 to wchar (WINDOWS ONLY!)
*/
static wchar_t *
__Win32UTF8ToWChar(const char *u8String) {
	wchar_t *wString = NULL;

	if (u8String) {
		int wLen = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, u8String, -1, NULL, 0);
		if (wLen) {
			wString = (wchar_t*)malloc(wLen * sizeof(wchar_t));
			if (wString) {
				if (MultiByteToWideChar(CP_UTF8, 0, u8String, -1, wString, wLen) == 0) {
					free(wString);
					wString = NULL;
				}
			}
		}
	}

	return wString;
}
#endif

std::string XMLReaderHelper::DectectFileEncoding(const std::string& file) {
#if defined(_WIN32)
	std::ifstream f;
	wchar_t* wPath = __Win32UTF8ToWChar(file.c_str());
	if (wPath) {
		f.open(wPath);
		free(wPath);
		wPath = NULL;
	} else {
		f.open(file);
	}
#else
	std::ifstream f(file);
#endif
	if (f.is_open()) {
		std::string firstLine;
		while (firstLine.empty()) {
			std::getline(f, firstLine);
		}
		f.close();
		size_t pos = firstLine.find("encoding=");
		if (pos != std::string::npos) {
			size_t first_quote = firstLine.find('"', pos);
			size_t last_quote = firstLine.find('"', first_quote + 1);
			if (first_quote != std::string::npos && last_quote != std::string::npos) {
				return firstLine.substr(first_quote + 1, last_quote - first_quote - 1);
			} else {
				return "";
			}
		} else {
			return "";
		}
	} else {
		return "";
	}
}

bool XMLReaderHelper::IsUTF8(const std::string& encodingName) {
	if (geo3dml::IsiEqual(encodingName, "utf-8")) {
		return true;
	}
	if (geo3dml::IsiEqual(encodingName, "utf8")) {
		return true;
	}
	return false;
}

bool XMLReaderHelper::IsRelativePath(const std::string& path) {
#if defined(_WIN32)
	bool isRelative = true;
	wchar_t* wPath = __xmlIOWin32UTF8ToWChar(path.c_str());
	if (wPath != NULL) {
		std::wregex re(L"^[a-zA-Z]:\\\\.*$");
		std::wcmatch m;
		if (std::regex_match(wPath, m, re)) {
			isRelative = false;
		}
		xmlFree(wPath);
	} else {
		std::regex re("^[a-zA-Z]:\\\\.*$");
		std::cmatch m;
		if (std::regex_match(path.c_str(), m, re)) {
			isRelative = false;
		}
	}
	return isRelative;
#else
	if (!path.empty() && path.at(0) == '/') {
		return false;
	} else {
		return true;
	}
#endif
}

bool XMLReaderHelper::TextNode(xmlTextReaderPtr reader, const std::string& element, std::string& str) {
	int status = xmlTextReaderRead(reader);
	if (status != 1) {
		str = FormatErrorMessageWithPosition(reader, "can not read element " + element);
		return false;
	}
	str = "";
	bool metEndElement = false;
	while (status == 1) {
		int nodeType = xmlTextReaderNodeType(reader);
		switch (nodeType) {
		case XML_READER_TYPE_TEXT: {
			const xmlChar* v = xmlTextReaderConstValue(reader);
			if (v) {
				str = (const char*)v;
			}
			break;
		}
		case XML_READER_TYPE_END_ELEMENT: {
			const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
			if (localName != NULL && geo3dml::IsiEqual(localName, element)) {
				metEndElement = true;
			}
			break;
		}
		default:
			break;
		}
		if (metEndElement) {
			break;
		}
		status = xmlTextReaderRead(reader);
	}
	if (metEndElement) {
		return true;
	} else {
		str = FormatErrorMessageWithPosition(reader, "missing end element of " + element);
		return false;
	}
}

std::string XMLReaderHelper::AttributeGMLID(xmlTextReaderPtr reader) {
	return Attribute(reader, "gml:id");
}

std::string XMLReaderHelper::Attribute(xmlTextReaderPtr reader, const std::string& attribute) {
	std::string attri;
	xmlChar* v = xmlTextReaderGetAttribute(reader, (const xmlChar*)attribute.c_str());
	if (v != NULL) {
		attri = (const char*)v;
		xmlFree(v);
	}
	return attri;
}

std::string XMLReaderHelper::AttributeIdInHref(xmlTextReaderPtr reader) {
	xmlChar* href = xmlTextReaderGetAttribute(reader, (const xmlChar*)"href");
	if (href == NULL) {
		href = xmlTextReaderGetAttribute(reader, (const xmlChar*)"xlink:href");
	}
	if (href != NULL) {
		std::string id((const char*)href);
		id = id.substr(id.find_last_of('#') + 1);
		xmlFree(href);
		return id;
	} else {
		return std::string();
	}
}

std::string XMLReaderHelper::FormatErrorMessageWithPosition(xmlTextReaderPtr reader, const std::string& message) {
	std::ostringstream ostr;
	ostr << "line " << xmlTextReaderGetParserLineNumber(reader) << ", column " << xmlTextReaderGetParserColumnNumber(reader) << ": " << message;
	return ostr.str();
}

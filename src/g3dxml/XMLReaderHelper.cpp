#include <g3dxml/XMLReaderHelper.h>
#include <fstream>
#include <sstream>

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
	if (_stricmp(encodingName.c_str(), "utf-8") == 0) {
		return true;
	}
	if (_stricmp(encodingName.c_str(), "utf8") == 0) {
		return true;
	}
	return false;
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
			if (localName != NULL && _stricmp(localName, element.c_str()) == 0) {
				metEndElement = true;
				break;
			}
		}
		default: {
			break;
		}
		}
		if (metEndElement)
			break;
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

bool XMLReaderHelper::IsZero(double v) {
	return fabs(v) <= 10e-6;
}

std::string XMLReaderHelper::FormatErrorMessageWithPosition(xmlTextReaderPtr reader, const std::string& message) {
	std::ostringstream ostr;
	ostr << "line " << xmlTextReaderGetParserLineNumber(reader) << ", column " << xmlTextReaderGetParserColumnNumber(reader) << ": " << message;
	return ostr.str();
}

bool XMLReaderHelper::IsTrue(const std::string& s) {
	if (_stricmp(s.c_str(), "1") == 0) {
		return true;
	} else if (_stricmp(s.c_str(), "true") == 0) {
		return true;
	} else if (_stricmp(s.c_str(), "yes") == 0) {
		return true;
	} else if (_stricmp(s.c_str(), "t") == 0) {
		return true;
	} else if (_stricmp(s.c_str(), "y") == 0) {
		return true;
	} else {
		return false;
	}
}
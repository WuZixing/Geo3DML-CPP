#include <g3dxml/XMLReader.h>
#include <g3dxml/XMLProjectReader.h>
#include <g3dxml/XMLModelReader.h>
#include <geo3dml/Utils.h>

using namespace g3dxml;

XMLReader::XMLReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
}

XMLReader::~XMLReader() {
	g3dFactory_ = NULL;
}

geo3dml::Object* XMLReader::LoadXMLFile(const std::string& file) {
	if (g3dFactory_ == NULL) {
		SetStatus(false, "G3DObjectFactory is NULL");
		return NULL;
	}
	std::string fileEncoding = XMLReaderHelper::DectectFileEncoding(file);
	if (!XMLReaderHelper::IsUTF8(fileEncoding)) {
		SetStatus(false, "unsupported encoding " + fileEncoding + " of file " + file);
		return NULL;
	}
	LIBXML_TEST_VERSION
	geo3dml::Object* g3dObject = NULL;
	xmlTextReaderPtr reader = xmlReaderForFile(file.c_str(), fileEncoding.c_str(), 0);
	if (reader != NULL) {
		int status = xmlTextReaderRead(reader);
		while (status == 1) {
			const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
			int nodeType = xmlTextReaderNodeType(reader);
			if (nodeType != XML_READER_TYPE_ELEMENT) {
				status = xmlTextReaderRead(reader);
				continue;
			}
			if (geo3dml::IsiEqual(localName, XMLProjectReader::Element)) {
#if defined(_WIN32)
				const char primaryPathSeperator = '\\';
				const char secondaryPathSeperator = '/';	// Qt uses '/' as path seperator on windows.
#else
				const char primaryPathSeperator = '/';
				const char secondaryPathSeperator = '\\';
#endif
				std::string projectDirectory;
				size_t pos = file.find_last_of(primaryPathSeperator);
				if (pos == std::string::npos) {
					pos = file.find_last_of(secondaryPathSeperator);
				}
				if (pos != std::string::npos) {
					projectDirectory = file.substr(0, pos + 1);
				}
				XMLProjectReader projectReader(g3dFactory_, projectDirectory);
				g3dObject = projectReader.ReadProject(reader);
				if (!projectReader.IsOK()) {
					SetStatus(false, projectReader.Error());
				}
			} else if (XMLModelReader::IsModelElementName(localName)) {
				XMLModelReader modelReader(g3dFactory_);
				g3dObject = modelReader.ReadModel(reader);
				if (!modelReader.IsOK()) {
					SetStatus(false, modelReader.Error());
				}
			}
			if (g3dObject == NULL && IsOK()) {
				status = xmlTextReaderRead(reader);
			} else {
				break;
			}
		}
		if (status != 1) {
			std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "failed to parse file " + file);
			SetStatus(false, err);
		}
		xmlTextReaderClose(reader);
		xmlFreeTextReader(reader);
	} else {
		SetStatus(false, "failed to open file " + file);
	}
	xmlCleanupParser();
	return g3dObject;
}

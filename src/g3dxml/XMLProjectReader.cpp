#include <g3dxml/XMLProjectReader.h>
#include <g3dxml/XMLModelReader.h>
#include <g3dxml/XMLMapReader.h>
#include <regex>
#include <geo3dml/Utils.h>

using namespace g3dxml;

std::string XMLProjectReader::Element = "Geo3DProject";
std::string XMLProjectReader::Element_Name = "Name";
std::string XMLProjectReader::Element_Description = "Description";
std::string XMLProjectReader::Element_Model = "Model";
std::string XMLProjectReader::Element_Include = "include";
std::string XMLProjectReader::Element_Style = "GeoSceneStyle";
std::string XMLProjectReader::Element_Light = "Light";
std::string XMLProjectReader::Element_Map = "Map";

XMLProjectReader::XMLProjectReader(geo3dml::ObjectFactory* factory, const std::string& projectDirectory) {
	g3dFactory_ = factory;
	projectDirectory_ = projectDirectory;
}

XMLProjectReader::~XMLProjectReader() {
	g3dFactory_ = NULL;
}

geo3dml::Project* XMLProjectReader::ReadProject(xmlTextReaderPtr reader) {
	geo3dml::Project* project = g3dFactory_->NewProject();
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Name)) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, Element_Name, v)) {
					SetStatus(false, v);
					break;
				}
				project->SetName(v);
			} else if (geo3dml::IsiEqual(localName, Element_Description)) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, Element_Description, v)) {
					SetStatus(false, v);
					break;
				}
				project->SetDescription(v);
			} else if (geo3dml::IsiEqual(localName, Element_Model)) {
				geo3dml::Model* model = ReadModel(reader);
				if (model != NULL) {
					project->AddModel(model);
				} else {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Style)) {
				if (!ReadStyle(reader, project)) {
					break;
				}
			} else if (geo3dml::IsiEqual(localName, Element_Map)) {
				geo3dml::Map* map = ReadMap(reader);
				if (map != NULL) {
					project->AddMap(map);
				} else {
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element);
		SetStatus(false, err);
	}
	if (!IsOK()) {
		delete project;
		project = NULL;
	}
	return project;
}

geo3dml::Model* XMLProjectReader::ReadModel(xmlTextReaderPtr reader) {
	// a Geo3DModel element can be embedded in <Model>, or included from another xml file by an xi:include element.
	geo3dml::Model* model = NULL;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Model)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Include)) {
				// load from XML file.
				xmlChar* href = xmlTextReaderGetAttribute(reader, (const xmlChar*)"href");
				if (href != NULL) {
					XMLModelReader modelReader(g3dFactory_);
					if (IsRelativePath((const char*)href)) {
						model = modelReader.LoadFromFile(projectDirectory_ + (const char*)href);
					} else {
						model = modelReader.LoadFromFile((const char*)href);
					}
					xmlFree(href);
					if (!modelReader.IsOK()) {
						SetStatus(false, modelReader.Error());
					}
				} else {
					std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing attribute of href");
					SetStatus(false, err);
				}
			} else if (XMLModelReader::IsModelElementName(localName)) {
				// read from <GeoModel> element.
				XMLModelReader modelReader(g3dFactory_);
				model = modelReader.ReadModel(reader);
				if (!modelReader.IsOK()) {
					SetStatus(false, modelReader.Error());
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Model);
		SetStatus(false, err);
	}
	return model;
}

bool XMLProjectReader::ReadStyle(xmlTextReaderPtr reader, geo3dml::Project* project) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Style)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "Background")) {
				std::string strColor;
				if (!XMLReaderHelper::TextNode(reader, "Background", strColor)) {
					SetStatus(false, strColor);
					break;
				}
				char* end = NULL;
				double r = strtod(strColor.c_str(), &end);
				double g = strtod(end, &end);
				double b = strtod(end, NULL);
				project->GetSceneStyle().SetBackgroundColor(geo3dml::Color(r, g, b));
			} else if (geo3dml::IsiEqual(localName, Element_Light)) {
				geo3dml::Light light;
				if (ReadLight(reader, light)) {
					project->GetSceneStyle().AddLight(light);
				} else {
					break;
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Style);
		SetStatus(false, err);
	}
	return IsOK();
}

bool XMLProjectReader::ReadLight(xmlTextReaderPtr reader, geo3dml::Light& light) {
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Light)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, "On")) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, "On", v)) {
					SetStatus(false, v);
					break;
				}
				light.Switch(geo3dml::IsTrue(v));
			} else if (geo3dml::IsiEqual(localName, "Type")) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, "Type", v)) {
					SetStatus(false, v);
					break;
				}
				light.SetType(geo3dml::Light::NameToLightType(v));
			} else if (geo3dml::IsiEqual(localName, "Position")) {
				std::string pos;
				if (!XMLReaderHelper::TextNode(reader, "Position", pos)) {
					SetStatus(false, pos);
					break;
				}
				char* end = NULL;
				double x = strtod(pos.c_str(), &end);
				double y = strtod(end, &end);
				double z = strtod(end, NULL);
				light.SetPosition(x, y, z);
			} else if (geo3dml::IsiEqual(localName, "FocalPosition")) {
				std::string pos;
				if (!XMLReaderHelper::TextNode(reader, "FocalPosition", pos)) {
					SetStatus(false, pos);
					break;
				}
				char* end = NULL;
				double x = strtod(pos.c_str(), &end);
				double y = strtod(end, &end);
				double z = strtod(end, NULL);
				light.SetFocalPosition(x, y, z);
			} else if (geo3dml::IsiEqual(localName, "Intensity")) {
				std::string str;
				if (!XMLReaderHelper::TextNode(reader, "Intensity", str)) {
					SetStatus(false, str);
					break;
				}
				double intensity = strtod(str.c_str(), NULL);
				light.SetIntensity(intensity);
			} else if (geo3dml::IsiEqual(localName, "AmbientColor")) {
				std::string str;
				if (!XMLReaderHelper::TextNode(reader, "AmbientColor", str)) {
					SetStatus(false, str);
					break;
				}
				char* end = NULL;
				double r = strtod(str.c_str(), &end);
				double g = strtod(end, &end);
				double b = strtod(end, NULL);
				light.SetAmbientColor(geo3dml::Color(r, g, b));
			} else if (geo3dml::IsiEqual(localName, "DiffuseColor")) {
				std::string str;
				if (!XMLReaderHelper::TextNode(reader, "DiffuseColor", str)) {
					SetStatus(false, str);
					break;
				}
				char* end = NULL;
				double r = strtod(str.c_str(), &end);
				double g = strtod(end, &end);
				double b = strtod(end, NULL);
				light.SetDiffuseColor(geo3dml::Color(r, g, b));
			} else if (geo3dml::IsiEqual(localName, "SpecularColor")) {
				std::string str;
				if (!XMLReaderHelper::TextNode(reader, "SpecularColor", str)) {
					SetStatus(false, str);
					break;
				}
				char* end = NULL;
				double r = strtod(str.c_str(), &end);
				double g = strtod(end, &end);
				double b = strtod(end, NULL);
				light.SetSpecularColor(geo3dml::Color(r, g, b));
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Light);
		SetStatus(false, err);
	}
	return IsOK();
}

geo3dml::Map* XMLProjectReader::ReadMap(xmlTextReaderPtr reader) {
	// a Geo3DMap element can be embedded in <Map>, or included from another xml file by an xi:include element.
	geo3dml::Map* map = NULL;
	int status = xmlTextReaderRead(reader);
	while (status == 1) {
		const char* localName = (const char*)xmlTextReaderConstLocalName(reader);
		int nodeType = xmlTextReaderNodeType(reader);
		if (nodeType == XML_READER_TYPE_END_ELEMENT && geo3dml::IsiEqual(localName, Element_Map)) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (geo3dml::IsiEqual(localName, Element_Include)) {
				// load from XML file.
				xmlChar* href = xmlTextReaderGetAttribute(reader, (const xmlChar*)"href");
				if (href != NULL) {
					XMLMapReader mapReader(g3dFactory_);
					if (IsRelativePath((const char*)href)) {
						map = mapReader.LoadFromFile(projectDirectory_ + (const char*)href);
					} else {
						map = mapReader.LoadFromFile((const char*)href);
					}
					xmlFree(href);
					if (!mapReader.IsOK()) {
						SetStatus(false, mapReader.Error());
					}
				} else {
					std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing attribute of href");
					SetStatus(false, err);
				}
			} else if (geo3dml::IsiEqual(localName, XMLMapReader::Element)) {
				// read from <Geo3DMap> element.
				XMLMapReader mapReader(g3dFactory_);
				map = mapReader.ReadMap(reader);
				if (!mapReader.IsOK()) {
					SetStatus(false, mapReader.Error());
				}
			}
		}
		status = xmlTextReaderRead(reader);
	}
	if (status != 1) {
		std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing end element of " + Element_Map);
		SetStatus(false, err);
	}
	return map;
}

bool XMLProjectReader::IsRelativePath(const std::string& path) {
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

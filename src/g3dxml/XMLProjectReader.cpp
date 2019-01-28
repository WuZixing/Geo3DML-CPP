#include <g3dxml/XMLProjectReader.h>
#include <g3dxml/XMLModelReader.h>
#include <g3dxml/XMLMapReader.h>

using namespace g3dxml;

std::string XMLProjectReader::Element = "Geo3DProject";
std::string XMLProjectReader::Element_Name = "Name";
std::string XMLProjectReader::Element_Description = "Description";
std::string XMLProjectReader::Element_Model = "Model";
std::string XMLProjectReader::Element_Include = "include";
std::string XMLProjectReader::Element_Style = "GeoSceneStyle";
std::string XMLProjectReader::Element_Light = "Light";
std::string XMLProjectReader::Element_Map = "Map";

XMLProjectReader::XMLProjectReader(geo3dml::ObjectFactory* factory) {
	g3dFactory_ = factory;
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, Element_Name.c_str()) == 0) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, Element_Name, v)) {
					SetStatus(false, v);
					break;
				}
				project->SetName(v);
			} else if (_stricmp(localName, Element_Description.c_str()) == 0) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, Element_Description, v)) {
					SetStatus(false, v);
					break;
				}
				project->SetDescription(v);
			} else if (_stricmp(localName, Element_Model.c_str()) == 0) {
				geo3dml::Model* model = ReadModel(reader);
				if (model != NULL) {
					project->AddModel(model);
				} else {
					break;
				}
			} else if (_stricmp(localName, Element_Style.c_str()) == 0) {
				if (!ReadStyle(reader, project)) {
					break;
				}
			} else if (_stricmp(localName, Element_Map.c_str()) == 0) {
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_Model.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, Element_Include.c_str()) == 0) {
				// load from XML file.
				xmlChar* href = xmlTextReaderGetAttribute(reader, (const xmlChar*)"href");
				if (href != NULL) {
					XMLModelReader modelReader(g3dFactory_);
					model = modelReader.LoadFromFile((const char*)href);
					xmlFree(href);
					if (!modelReader.IsOK()) {
						SetStatus(false, modelReader.Error());
					}
				} else {
					std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing attribute of href");
					SetStatus(false, err);
				}
				break;
			} else if (XMLModelReader::IsModelElementName(localName)) {
				// read from <GeoModel> element.
				XMLModelReader modelReader(g3dFactory_);
				model = modelReader.ReadModel(reader);
				if (!modelReader.IsOK()) {
					SetStatus(false, modelReader.Error());
				}
				break;
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_Style.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, "Background") == 0) {
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
			} else if (_stricmp(localName, Element_Light.c_str()) == 0) {
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_Light.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, "On") == 0) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, "On", v)) {
					SetStatus(false, v);
					break;
				}
				light.Switch(XMLReaderHelper::IsTrue(v));
			} else if (_stricmp(localName, "Type") == 0) {
				std::string v;
				if (!XMLReaderHelper::TextNode(reader, "Type", v)) {
					SetStatus(false, v);
					break;
				}
				light.SetType(geo3dml::Light::NameToLightType(v));
			} else if (_stricmp(localName, "Position") == 0) {
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
			} else if (_stricmp(localName, "FocalPosition") == 0) {
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
			} else if (_stricmp(localName, "Intensity") == 0) {
				std::string str;
				if (!XMLReaderHelper::TextNode(reader, "Intensity", str)) {
					SetStatus(false, str);
					break;
				}
				double intensity = strtod(str.c_str(), NULL);
				light.SetIntensity(intensity);
			} else if (_stricmp(localName, "AmbientColor") == 0) {
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
			} else if (_stricmp(localName, "DiffuseColor") == 0) {
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
			} else if (_stricmp(localName, "SpecularColor") == 0) {
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
		if (nodeType == XML_READER_TYPE_END_ELEMENT && _stricmp(localName, Element_Map.c_str()) == 0) {
			break;
		} else if (nodeType == XML_READER_TYPE_ELEMENT) {
			if (_stricmp(localName, Element_Include.c_str()) == 0) {
				// load from XML file.
				xmlChar* href = xmlTextReaderGetAttribute(reader, (const xmlChar*)"href");
				if (href != NULL) {
					XMLMapReader mapReader(g3dFactory_);
					map = mapReader.LoadFromFile((const char*)href);
					xmlFree(href);
					if (!mapReader.IsOK()) {
						SetStatus(false, mapReader.Error());
					}
				} else {
					std::string err = XMLReaderHelper::FormatErrorMessageWithPosition(reader, "missing attribute of href");
					SetStatus(false, err);
				}
				break;
			} else if (XMLModelReader::IsModelElementName(localName)) {
				// read from <Geo3DMap> element.
				XMLMapReader mapReader(g3dFactory_);
				map = mapReader.ReadMap(reader);
				if (!mapReader.IsOK()) {
					SetStatus(false, mapReader.Error());
				}
				break;
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

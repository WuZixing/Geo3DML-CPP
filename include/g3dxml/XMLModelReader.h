#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLModelReader : public XMLIO {
	public:
		/// Name of the model element.
		static std::string Element;
		static bool IsModelElementName(const std::string& name);

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLModelReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLModelReader();

		geo3dml::Model* ReadModel(xmlTextReaderPtr reader);
		geo3dml::Model* LoadFromFile(const std::string& file);

	private:
		bool ReadMetadata(xmlTextReaderPtr reader, geo3dml::Model* model);
		bool ReadMetadataContact(xmlTextReaderPtr reader, geo3dml::Metadata& meta);
		std::string ReadCharacterString(xmlTextReaderPtr reader, const std::string& parentNode);
		bool ReadMetadataDateStamp(xmlTextReaderPtr reader, geo3dml::Metadata& meta);
		bool ReadMetadataSpatialCoordinateReference(xmlTextReaderPtr reader, geo3dml::Metadata& meta);
		bool ReadMetadataCRS(xmlTextReaderPtr reader, geo3dml::Metadata& meta);
		bool ReadMetadataVRS(xmlTextReaderPtr reader, geo3dml::Metadata& meta);

	private:
		static const std::string OldElement;
		static const std::string Element_Name;
		static const std::string Element_Type;
		/// @name 元数据
		///@{
		static const std::string Element_Metadata;
		static const std::string Element_DateStamp;
		static const std::string Element_Description;
		static const std::string Element_Version;
		static const std::string Element_ToolName;
		static const std::string Element_ToolVersion;
		static const std::string Element_SpatialReferenceSystem;
		static const std::string Element_CoordinateReferenceSystem;
		static const std::string Element_VerticalReferenceSystem;
		///@}

	private:
		geo3dml::ObjectFactory* g3dFactory_;
	};
}
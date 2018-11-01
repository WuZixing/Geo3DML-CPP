#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLUniformGridReader : public XMLIO {
	public:
		/// Name of the rectified grid element.
		static std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLUniformGridReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLUniformGridReader();

		geo3dml::UniformGrid* ReadUniformGrid(xmlTextReaderPtr reader);

	private:
		bool ReadCells(xmlTextReaderPtr reader, geo3dml::UniformGrid* grid);
		bool ReadCell(xmlTextReaderPtr reader, geo3dml::UniformGrid* grid);

	private:
		const std::string Element_Origin = "Origin";
		const std::string Element_Steps = "Steps";
		const std::string Element_Dimension = "Dimension";
		const std::string Element_Cells = "Cells";
		const std::string Element_Cell = "Cell";

	private:
		geo3dml::ObjectFactory * g3dFactory_;
	};
}
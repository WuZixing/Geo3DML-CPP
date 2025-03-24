// UTF-8编码
#pragma once

#include <g3dxml/XMLReaderHelper.h>
#include <g3dxml/XMLIO.h>

namespace g3dxml {

	class XMLCornerPointGridReader : public XMLIO {
	public:
		/// Name of the corner point grid element.
		static const std::string Element;

	public:
		/// Constructor.
		/// @param factory the factory of Geo3DML objects. The factory object should be deallocated by the caller.
		XMLCornerPointGridReader(geo3dml::ObjectFactory* factory);
		virtual ~XMLCornerPointGridReader();

		geo3dml::CornerPointGrid* ReadCornerPointGrid(xmlTextReaderPtr reader);

	private:
		bool ReadPillar(xmlTextReaderPtr reader, geo3dml::CornerPointGrid* grid);
		bool ReadCells(xmlTextReaderPtr reader, geo3dml::CornerPointGrid* grid);
		bool ReadCell(xmlTextReaderPtr reader, geo3dml::CornerPointGrid* grid, int i, int j, int k, const std::string& zValueTag = "elevation");
		void ComputeZByElevation(const double headPosOfPillar[3], const double tailPosOfPillar[3], const double& z, double pos[3]);
		void ComputeZByLength(const double headPosOfPillar[3], const double tailPosOfPillar[3], const double& len, double pos[3]);

	private:
		static const std::string Element_Dimension;
		static const std::string Element_Pillar;
		static const std::string Element_Pillar_HeadPos;
		static const std::string Element_Pillar_TailPos;
		static const std::string Element_Cells;
		static const std::string Element_Cell;

	private:
		geo3dml::ObjectFactory * g3dFactory_;
	};
}

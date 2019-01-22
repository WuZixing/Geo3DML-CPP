#pragma once

#include <geo3dml/Actor.h>
#include <geo3dml/PointSymbolizer.h>
#include <geo3dml/LineSymbolizer.h>
#include <geo3dml/SurfaceSymbolizer.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>

namespace g3dvtk {

	class Actor : public geo3dml::Actor {
	public:
		Actor();
		virtual ~Actor();

		/// @name methods defined in geo3dml::Actor.
		//@{
		virtual void BindGeometry(geo3dml::Feature* feature, geo3dml::Geometry* geo, geo3dml::Symbolizer* sym);
		virtual geo3dml::Feature* GetBindingFeature();
		virtual geo3dml::Geometry* GetBindingGeometry();
		virtual geo3dml::Symbolizer* MakeSymbozier();
		//@}

		vtkActor* GetVTKActor();

	private:
		void ConfigByPointSymbolizer(const geo3dml::PointSymbolizer* sym);
		void ConfigByLineSymbolizer(const geo3dml::LineSymbolizer* sym);
		void ConfigBySurfaceSymbolizer(const geo3dml::SurfaceSymbolizer* sym);
		void ConfigByMaterial(const geo3dml::Material& m, vtkProperty* p);
		void SetRandomRenderOption();

		geo3dml::Material ToMaterial(vtkProperty* p);
		void ToPointSymbolizer(vtkProperty* p, geo3dml::PointSymbolizer* sym);
		void ToLineSymbolizer(vtkProperty* p, geo3dml::LineSymbolizer* sym);
		void ToSurfaceSymbolizer(vtkProperty* p, geo3dml::SurfaceSymbolizer* sym);

	private:
		geo3dml::Feature* bindingFeature_;
		geo3dml::Geometry* bindingGeometry_;
		vtkSmartPointer<vtkActor> actor_;
	};
}

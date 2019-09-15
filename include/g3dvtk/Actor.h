#pragma once

#include <geo3dml/Actor.h>
#include <geo3dml/PointSymbolizer.h>
#include <geo3dml/LineSymbolizer.h>
#include <geo3dml/SurfaceSymbolizer.h>
#include <vtkSmartPointer.h>
#include <vtkProp.h>
#include <vtkActor.h>
#include <vtkTransform.h>

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
		virtual bool IsVisible();
		virtual void SetVisible(bool show);
		virtual geo3dml::Symbolizer* MakeSymbozier();
		//@}

		vtkProp* GetVTKProp();
		void SetUserTransform(vtkTransform* t);

	private:
		void ConfigByPointSymbolizer(const geo3dml::PointSymbolizer* sym, vtkProperty* p);
		void ConfigByLineSymbolizer(const geo3dml::LineSymbolizer* sym, vtkProperty* p);
		void ConfigBySurfaceSymbolizer(const geo3dml::SurfaceSymbolizer* sym, vtkProperty* p);
		void ConfigByMaterial(const geo3dml::Material& m, vtkProperty* p);
		void SetRandomRenderOption(vtkProperty* p);

		geo3dml::Material ToMaterial(vtkProperty* p);
		void ToPointSymbolizer(vtkProperty* p, geo3dml::PointSymbolizer* sym);
		void ToLineSymbolizer(vtkProperty* p, geo3dml::LineSymbolizer* sym);
		void ToSurfaceSymbolizer(vtkProperty* p, geo3dml::SurfaceSymbolizer* sym);

	private:
		geo3dml::Feature* bindingFeature_;
		geo3dml::Geometry* bindingGeometry_;
		vtkSmartPointer<vtkProp> vtkProp_;
	};
}

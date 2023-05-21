#pragma once

#include <geo3dml/Actor.h>
#include <geo3dml/LineSymbolizer.h>
#include <geo3dml/Matrix4x4.h>
#include <geo3dml/PointSymbolizer.h>
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
		virtual geo3dml::Feature* GetBindingFeature() const;
		virtual geo3dml::Geometry* GetBindingGeometry() const;
		virtual bool IsVisible() const;
		virtual void SetVisible(bool show);
		virtual geo3dml::Symbolizer* MakeSymbozier() const;
		//@}

		vtkProp* GetVTKProp() const;
		void SetUserTransform(vtkTransform* t);

	private:
		void ConfigByPointSymbolizer(const geo3dml::PointSymbolizer* sym, vtkProperty* p) const;
		void ConfigByLineSymbolizer(const geo3dml::LineSymbolizer* sym, vtkProperty* p) const;
		void ConfigBySurfaceSymbolizer(const geo3dml::SurfaceSymbolizer* sym, vtkProperty* p) const;
		void ConfigByMaterial(const geo3dml::Material& m, vtkProperty* p) const;
		void SetRandomRenderOption(vtkProperty* p) const;

		geo3dml::Material ToMaterial(vtkProperty* p) const;
		void ToPointSymbolizer(vtkProperty* p, geo3dml::PointSymbolizer* sym) const;
		void ToLineSymbolizer(vtkProperty* p, geo3dml::LineSymbolizer* sym) const;
		void ToSurfaceSymbolizer(vtkProperty* p, geo3dml::SurfaceSymbolizer* sym) const;

		void G3DMatrixToVTKMatrix(const geo3dml::Matrix4x4& g3dMatrix, vtkMatrix4x4* vtkMatrix) const;

	private:
		geo3dml::Feature* bindingFeature_;
		geo3dml::Geometry* bindingGeometry_;
		vtkSmartPointer<vtkProp> vtkProp_;
	};
}

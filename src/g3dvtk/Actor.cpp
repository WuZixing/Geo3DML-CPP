#include <g3dvtk/Actor.h>
#include <g3dvtk/TIN.h>
#include <g3dvtk/CornerPointGrid.h>
#include <g3dvtk/UniformGrid.h>
#include <g3dvtk/LineString.h>
#include <g3dvtk/Point.h>
#include <g3dvtk/MultiPoint.h>
#include <g3dvtk/ObjectFactory.h>
#include <g3dvtk/ColorMap.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkOpenGLActor.h>
#include <vtkPolyData.h>
#include <vtkImageToStructuredGrid.h>

using namespace g3dvtk;

Actor::Actor() {
	bindingFeature_ = NULL;
	bindingGeometry_ = NULL;
	symbolizer_ = NULL;
}

Actor::~Actor() {
	if (symbolizer_ != NULL) {
		delete symbolizer_;
	}
}

void Actor::BindGeometry(geo3dml::Feature* feature, geo3dml::Geometry* geo, geo3dml::Symbolizer* sym) {
	bindingFeature_ = feature;
	bindingGeometry_ = geo;
	if (bindingGeometry_ == NULL || bindingGeometry_->GetShape() == NULL) {
		return;
	}
	actor_ = vtkSmartPointer<vtkOpenGLActor>::New();
	geo3dml::Shape* shape = bindingGeometry_->GetShape();
	g3dvtk::TIN* tin = dynamic_cast<g3dvtk::TIN*>(shape);
	if (tin != NULL) {
		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputData(tin->GetPolyData());
		actor_->SetMapper(mapper);
		geo3dml::SurfaceSymbolizer* surfaceSymbolizer = dynamic_cast<geo3dml::SurfaceSymbolizer*>(sym);
		if (surfaceSymbolizer != NULL) {
			ConfigBySurfaceSymbolizer(surfaceSymbolizer);
		} else {
			SetRandomRenderOption();
		}
	} else {
		g3dvtk::CornerPointGrid* grid = dynamic_cast<g3dvtk::CornerPointGrid*>(shape);
		if (grid != NULL) {
			vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
			mapper->SetInputData(grid->GetStructuredGrid());
			actor_->SetMapper(mapper);
			SetRandomRenderOption();
		} else {
			g3dvtk::UniformGrid* grid = dynamic_cast<g3dvtk::UniformGrid*>(shape);
			if (grid != NULL) {
				vtkSmartPointer<vtkImageToStructuredGrid> algo = vtkSmartPointer<vtkImageToStructuredGrid>::New();
				algo->SetInputData(grid->GetUniformGrid());
				vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
				mapper->SetInputConnection(algo->GetOutputPort());
				actor_->SetMapper(mapper);
				SetRandomRenderOption();
			} else {
				g3dvtk::LineString* lineString = dynamic_cast<g3dvtk::LineString*>(shape);
				if (lineString != NULL) {
					vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
					mapper->SetInputData(lineString->GetPolyData());
					actor_->SetMapper(mapper);
					geo3dml::LineSymbolizer* lineSymbolizer = dynamic_cast<geo3dml::LineSymbolizer*>(sym);
					if (lineSymbolizer != NULL) {
						ConfigByLineSymbolizer(lineSymbolizer);
					} else {
						SetRandomRenderOption();
					}
				} else {
					g3dvtk::Point* point = dynamic_cast<g3dvtk::Point*>(shape);
					if (point != NULL) {
						vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
						mapper->SetInputData(point->GetPolyData());
						actor_->SetMapper(mapper);
						geo3dml::PointSymbolizer* pointSymbolizer = dynamic_cast<geo3dml::PointSymbolizer*>(sym);
						if (pointSymbolizer != NULL) {
							ConfigByPointSymbolizer(pointSymbolizer);
						} else {
							SetRandomRenderOption();
						}
					} else {
						g3dvtk::MultiPoint* mPoint = dynamic_cast<g3dvtk::MultiPoint*>(shape);
						if (mPoint != NULL) {
							vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
							mapper->SetInputData(mPoint->GetPolyData());
							actor_->SetMapper(mapper);
							geo3dml::PointSymbolizer* pointSymbolizer = dynamic_cast<geo3dml::PointSymbolizer*>(sym);
							if (pointSymbolizer != NULL) {
								ConfigByPointSymbolizer(pointSymbolizer);
							} else {
								SetRandomRenderOption();
							}
						}
					}
				}
			}
		}
	}
}

geo3dml::Feature* Actor::GetBindingFeature() const {
	return bindingFeature_;
}

geo3dml::Geometry* Actor::GetBindingGeometry() const {
	return bindingGeometry_;
}

geo3dml::Symbolizer* Actor::GetSymbozier() {
	return NULL;
}

vtkActor* Actor::GetVTKActor() const {
	return actor_;
}

void Actor::ConfigByPointSymbolizer(const geo3dml::PointSymbolizer* sym) {
	vtkProperty* p = actor_->GetProperty();
	p->SetPointSize(sym->GetSize());
	ConfigMaterial(sym->GetMaterial(), p);
}

void Actor::ConfigByLineSymbolizer(const geo3dml::LineSymbolizer* sym) {
	vtkProperty* p = actor_->GetProperty();
	p->SetLineWidth(sym->GetWidth());
	ConfigMaterial(sym->GetMaterial(), p);
}

void Actor::ConfigBySurfaceSymbolizer(const geo3dml::SurfaceSymbolizer* sym) {
	vtkProperty* p = actor_->GetProperty();
	ConfigMaterial(sym->GetFrontMaterial(), p);
	if (sym->IsVertexRenderEnabled()) {
		p->SetPointSize(sym->GetVertexSymbolizer().GetSize());
		p->VertexVisibilityOn();
	} else {
		p->VertexVisibilityOff();
	}
	if (sym->IsFrameRenderEnabled()) {
		p->SetLineWidth(sym->GetFrameSymbolizer().GetWidth());
		p->EdgeVisibilityOn();
	} else {
		p->EdgeVisibilityOff();
	}
}

void Actor::ConfigMaterial(const geo3dml::Material& m, vtkProperty* p) {
	geo3dml::Color diffuseColor = m.GetDiffuseColor();
	geo3dml::Color specularColor = m.GetSpecularColor();
	p->SetAmbient(m.GetAmbientIntensity());
	p->SetDiffuseColor(diffuseColor.R(), diffuseColor.G(), diffuseColor.B());
	p->SetSpecularColor(specularColor.R(), specularColor.G(), specularColor.B());
	p->SetOpacity(1 - m.GetTransparency());
}

void Actor::SetRandomRenderOption() {
	double r = 0, g = 0, b = 0;
	ColorMap* colorMap = ColorMap::NewDefaultMap();
	colorMap->RandomColor(r, g, b);
	delete colorMap;
	vtkProperty* p = actor_->GetProperty();
	p->SetColor(r, g, b);
	p->SetPointSize(3);
	p->SetAmbient(0.25);
}

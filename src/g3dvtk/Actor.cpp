#include <g3dvtk/Actor.h>
#include <g3dvtk/TIN.h>
#include <g3dvtk/CornerPointGrid.h>
#include <g3dvtk/UniformGrid.h>
#include <g3dvtk/LineString.h>
#include <g3dvtk/Point.h>
#include <g3dvtk/MultiPoint.h>
#include <g3dvtk/Annotation.h>
#include <g3dvtk/ObjectFactory.h>
#include <g3dvtk/ColorMap.h>
#include <g3dvtk/DiscreteAttributeColorTransfer.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkOpenGLActor.h>
#include <vtkPolyData.h>
#include <vtkImageToStructuredGrid.h>
#include <vtkActor2D.h>
#include <vtkDiscretizableColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkDiscreteMarchingCubes.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkWindowedSincPolyDataFilter.h>
#include <vtkThreshold.h>
#include <vtkImageDataToPointSet.h>
#include <set>
#include <vtkDiscreteFlyingEdges3D.h>
#include <vtkContourFilter.h>
// #include <vtkSurfaceNets3D.h>
#include <vtkConstrainedSmoothingFilter.h>
#include <vtkPointSmoothingFilter.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkExtractUnstructuredGrid.h>

using namespace g3dvtk;

Actor::Actor() {
	bindingFeature_ = NULL;
	bindingGeometry_ = NULL;
}

Actor::~Actor() {

}

void Actor::BindGeometry(geo3dml::Feature* feature, geo3dml::Geometry* geo, geo3dml::Symbolizer* sym) {
	bindingFeature_ = feature;
	bindingGeometry_ = geo;
	if (bindingGeometry_ == NULL) {
		return;
	}
	g3dvtk::TIN* tin = dynamic_cast<g3dvtk::TIN*>(bindingGeometry_);
	if (tin != NULL) {
		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputData(tin->GetPolyData());
		vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
		actor->SetMapper(mapper);
		geo3dml::SurfaceSymbolizer* surfaceSymbolizer = dynamic_cast<geo3dml::SurfaceSymbolizer*>(sym);
		if (surfaceSymbolizer != NULL) {
			ConfigBySurfaceSymbolizer(surfaceSymbolizer, actor->GetProperty());
		} else {
			SetRandomRenderOption(actor->GetProperty());
		}
		vtkProp_ = actor;
	} else {
		g3dvtk::CornerPointGrid* grid = dynamic_cast<g3dvtk::CornerPointGrid*>(bindingGeometry_);
		if (grid != NULL) {
			vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
			mapper->SetInputData(grid->GetStructuredGrid());
			vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
			actor->SetMapper(mapper);
			SetRandomRenderOption(actor->GetProperty());
			vtkProp_ = actor;
		} else {
			g3dvtk::UniformGrid* grid = dynamic_cast<g3dvtk::UniformGrid*>(bindingGeometry_);
			if (grid != NULL) {
				vtkUniformGrid* uniGrid = grid->GetUniformGrid();
				geo3dml::ShapeProperty* shapeProp = grid->GetProperty(geo3dml::ShapeProperty::Vertex);
				if (shapeProp != nullptr) {
					const geo3dml::Field& field = shapeProp->GetFieldAt(0);
					vtkPointData* ptData = uniGrid->GetPointData();
					vtkDataArray* da = ptData->GetArray(field.Name().c_str());
					ptData->SetScalars(da);
				} else {
					shapeProp = grid->GetProperty(geo3dml::ShapeProperty::Voxel);
					if (shapeProp != nullptr) {
						const geo3dml::Field& field = shapeProp->GetFieldAt(0);
						vtkCellData* cellData = uniGrid->GetCellData();
						vtkDataArray* da = cellData->GetArray(field.Name().c_str());
						cellData->SetScalars(da);
					}
				}
				// vtkSmartPointer<vtkImageToStructuredGrid> algo = vtkSmartPointer<vtkImageToStructuredGrid>::New();
				// vtkSmartPointer<vtkDiscreteFlyingEdges3D> algo = vtkSmartPointer<vtkDiscreteFlyingEdges3D>::New();
				vtkSmartPointer<vtkDiscreteMarchingCubes> algo = vtkSmartPointer<vtkDiscreteMarchingCubes>::New();
				// vtkSmartPointer<vtkContourFilter> algo = vtkSmartPointer<vtkContourFilter>::New();
				// vtkSmartPointer<vtkSurfaceNets3D> algo = vtkSmartPointer<vtkSurfaceNets3D>::New();
				algo->SetInputData(uniGrid);
				algo->GenerateValues(1, 3, 3);

				//*
				vtkSmartPointer<vtkWindowedSincPolyDataFilter> smoother = vtkSmartPointer<vtkWindowedSincPolyDataFilter>::New();
				smoother->SetInputConnection(algo->GetOutputPort());
				smoother->SetNumberOfIterations(8);
				smoother->BoundarySmoothingOff();
				smoother->FeatureEdgeSmoothingOff();
				smoother->SetFeatureAngle(120);
				smoother->SetEdgeAngle(120);
				smoother->SetPassBand(0.001);
				smoother->NonManifoldSmoothingOn();
				smoother->NormalizeCoordinatesOn();
				//*/
				/*/
				vtkSmartPointer<vtkSmoothPolyDataFilter> smoother = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
				smoother->SetInputConnection(algo->GetOutputPort());
				smoother->SetNumberOfIterations(8);
				smoother->BoundarySmoothingOn();
				smoother->FeatureEdgeSmoothingOn();
				smoother->SetFeatureAngle(120);
				*/

				vtkSmartPointer<vtkThreshold> selector = vtkSmartPointer<vtkThreshold>::New();
				selector->SetInputConnection(smoother->GetOutputPort());
				selector->SetThresholdFunction(vtkThreshold::THRESHOLD_BETWEEN);
				selector->SetLowerThreshold(0);
				selector->SetUpperThreshold(5);
				selector->SetInputArrayToProcess(
					0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_CELLS, vtkDataSetAttributes::SCALARS);
				//*/

				vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
				mapper->SetInputConnection(selector->GetOutputPort());
				vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
				actor->SetMapper(mapper);
				SetRandomRenderOption(actor->GetProperty());
				vtkProp_ = actor;
				//*//////////////////////////////////////////
				if (shapeProp != nullptr) {
					const geo3dml::Field& field = shapeProp->GetFieldAt(0);
					int dimI = 0, dimJ = 0, dimK = 0;
					grid->GetDimensions(dimI, dimJ, dimK);
					const int cellNumber = dimK * dimJ * dimI;
					if (field.DataType() == geo3dml::Field::Integer) {
						std::set<int> attriValues;
						int minValue = 1, maxValue = -1;
						for (int i = 0; i < cellNumber; ++i) {
							int value = shapeProp->IntValue(0, i);
							if (value == -99) {
								continue;
							}
							attriValues.insert(value);
							if (minValue > maxValue) {
								minValue = value;
								maxValue = value;
							} else {
								if (minValue > value) {
									minValue = value;
								}
								if (maxValue < value) {
									maxValue = value;
								}
							}
						}
						g3dvtk::DiscreteAttributeColorTransfer colorMap;
						for (std::set<int>::const_iterator citor = attriValues.cbegin(); citor != attriValues.cend(); ++citor) {
							colorMap.InsertAttribute(*citor);
						}
						colorMap.Compile();
						vtkSmartPointer<vtkDiscretizableColorTransferFunction> colorFunc = vtkSmartPointer<vtkDiscretizableColorTransferFunction>::New();
						colorFunc->DiscretizeOn();
						colorFunc->SetNumberOfValues(attriValues.size());
						double r = 0, g = 0, b = 0;
						for (std::set<int>::const_iterator citor = attriValues.cbegin(); citor != attriValues.cend(); ++citor) {
							colorMap.PickUpColor(*citor, r, g, b);
							colorFunc->AddRGBPoint(*citor, r, g, b);
							colorFunc->SetAnnotation(vtkVariant(*citor), std::to_string(*citor).c_str());
						}
						vtkSmartPointer<vtkPiecewiseFunction> alphaFunc = vtkSmartPointer<vtkPiecewiseFunction>::New();
						alphaFunc->AddSegment(minValue - 1e-6, 1, maxValue + 1e-6, 1);
						alphaFunc->ClampingOff();
						colorFunc->SetScalarOpacityFunction(alphaFunc);
						colorFunc->EnableOpacityMappingOff();
						colorFunc->ClampingOff();
						colorFunc->Build();
						// mapper->SetScalarModeToUseCellFieldData();
						// mapper->SetScalarModeToUsePointFieldData();
						mapper->SetLookupTable(colorFunc);
						// mapper->SelectColorArray(field.Name().c_str());
						// mapper->ScalarVisibilityOn();
						// mapper->ScalarVisibilityOff();
					}
				}
				///////////////////////////////////////////*/
			} else {
				g3dvtk::LineString* lineString = dynamic_cast<g3dvtk::LineString*>(bindingGeometry_);
				if (lineString != NULL) {
					vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
					mapper->SetInputData(lineString->GetPolyData());
					vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
					actor->SetMapper(mapper);
					geo3dml::LineSymbolizer* lineSymbolizer = dynamic_cast<geo3dml::LineSymbolizer*>(sym);
					if (lineSymbolizer != NULL) {
						ConfigByLineSymbolizer(lineSymbolizer, actor->GetProperty());
					} else {
						SetRandomRenderOption(actor->GetProperty());
					}
					vtkProp_ = actor;
				} else {
					g3dvtk::Point* point = dynamic_cast<g3dvtk::Point*>(bindingGeometry_);
					if (point != NULL) {
						vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
						mapper->SetInputData(point->GetPolyData());
						vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
						actor->SetMapper(mapper);
						geo3dml::PointSymbolizer* pointSymbolizer = dynamic_cast<geo3dml::PointSymbolizer*>(sym);
						if (pointSymbolizer != NULL) {
							ConfigByPointSymbolizer(pointSymbolizer, actor->GetProperty());
						} else {
							SetRandomRenderOption(actor->GetProperty());
						}
						vtkProp_ = actor;
					} else {
						g3dvtk::Annotation* annotation = dynamic_cast<g3dvtk::Annotation*>(bindingGeometry_);
						if (annotation != NULL) {
							vtkSmartPointer<vtkLabeledDataMapper> labelMapper = vtkSmartPointer<vtkLabeledDataMapper>::New();
							annotation->ConfigLabelMapper(labelMapper);
							vtkSmartPointer<vtkActor2D> actor2D = vtkSmartPointer<vtkActor2D>::New();
							actor2D->SetMapper(labelMapper);
							vtkProp_ = actor2D;
						} else {
							g3dvtk::MultiPoint* mPoint = dynamic_cast<g3dvtk::MultiPoint*>(bindingGeometry_);
							if (mPoint != NULL) {
								vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
								mapper->SetInputData(mPoint->GetPolyData());
								vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
								actor->SetMapper(mapper);
								geo3dml::PointSymbolizer* pointSymbolizer = dynamic_cast<geo3dml::PointSymbolizer*>(sym);
								if (pointSymbolizer != NULL) {
									ConfigByPointSymbolizer(pointSymbolizer, actor->GetProperty());
								} else {
									SetRandomRenderOption(actor->GetProperty());
								}
								vtkProp_ = actor;
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

bool Actor::IsVisible() const {
	return vtkProp_ != nullptr && vtkProp_->GetVisibility() != 0;
}
void Actor::SetVisible(bool show) {
	if (vtkProp_ != nullptr) {
		vtkProp_->SetVisibility(show ? 1 : 0);
	}
}

geo3dml::Symbolizer* Actor::MakeSymbozier() const {
	if (bindingGeometry_ == NULL) {
		return NULL;
	}
	if (vtkProp_ == NULL || !vtkProp_->IsA("vtkActor")) {
		return NULL;
	}
	vtkActor* actor = vtkActor::SafeDownCast(vtkProp_);
	g3dvtk::ObjectFactory g3dFactory;
	g3dvtk::TIN* tin = dynamic_cast<g3dvtk::TIN*>(bindingGeometry_);
	if (tin != NULL) {
		geo3dml::SurfaceSymbolizer* surfaceSym = g3dFactory.NewSurfaceSymbolizer();
		ToSurfaceSymbolizer(actor->GetProperty(), surfaceSym);
		return surfaceSym;
	} else {
		g3dvtk::CornerPointGrid* grid = dynamic_cast<g3dvtk::CornerPointGrid*>(bindingGeometry_);
		if (grid != NULL) {
			return NULL;
		} else {
			g3dvtk::UniformGrid* grid = dynamic_cast<g3dvtk::UniformGrid*>(bindingGeometry_);
			if (grid != NULL) {
				return NULL;
			} else {
				g3dvtk::LineString* lineString = dynamic_cast<g3dvtk::LineString*>(bindingGeometry_);
				if (lineString != NULL) {
					geo3dml::LineSymbolizer* lineSym = g3dFactory.NewLineSymbolizer();
					ToLineSymbolizer(actor->GetProperty(), lineSym);
					return lineSym;
				} else {
					g3dvtk::Point* point = dynamic_cast<g3dvtk::Point*>(bindingGeometry_);
					if (point != NULL) {
						geo3dml::PointSymbolizer* pointSym = g3dFactory.NewPointSymbolizer();
						ToPointSymbolizer(actor->GetProperty(), pointSym);
						return pointSym;
					} else {
						g3dvtk::MultiPoint* mPoint = dynamic_cast<g3dvtk::MultiPoint*>(bindingGeometry_);
						if (mPoint != NULL) {
							geo3dml::PointSymbolizer* pointSym = g3dFactory.NewPointSymbolizer();
							ToPointSymbolizer(actor->GetProperty(), pointSym);
							return pointSym;
						}
					}
				}
			}
		}
	}
	return NULL;
}

vtkProp* Actor::GetVTKProp() const {
	return vtkProp_;
}

void Actor::SetUserTransform(vtkTransform* t) {
	if (vtkProp_ == nullptr) {
		return;
	}
	if (vtkProp_->IsA("vtkActor")) {
		((vtkActor*)vtkProp_.Get())->SetUserTransform(t);
	} else if (vtkProp_->IsA("vtkActor2D")) {
		vtkMapper2D* mapper2D = ((vtkActor2D*)vtkProp_.Get())->GetMapper();
		if (mapper2D->IsA("vtkLabeledDataMapper")) {
			((vtkLabeledDataMapper*)mapper2D)->SetTransform(t);
		}
	}
}

void Actor::ConfigByPointSymbolizer(const geo3dml::PointSymbolizer* sym, vtkProperty* p) const {
	p->SetPointSize(sym->GetSize());
	ConfigByMaterial(sym->GetMaterial(), p);
}

void Actor::ConfigByLineSymbolizer(const geo3dml::LineSymbolizer* sym, vtkProperty* p) const {
	p->SetLineWidth(sym->GetWidth());
	ConfigByMaterial(sym->GetMaterial(), p);
}

void Actor::ConfigBySurfaceSymbolizer(const geo3dml::SurfaceSymbolizer* sym, vtkProperty* p) const {
	ConfigByMaterial(sym->GetFrontMaterial(), p);
	if (sym->IsVertexRenderEnabled()) {
		p->SetPointSize(sym->GetVertexSymbolizer()->GetSize());
		p->VertexVisibilityOn();
	} else {
		p->VertexVisibilityOff();
	}
	if (sym->IsFrameRenderEnabled()) {
		p->SetLineWidth(sym->GetFrameSymbolizer()->GetWidth());
		p->EdgeVisibilityOn();
	} else {
		p->EdgeVisibilityOff();
	}
}

void Actor::ConfigByMaterial(const geo3dml::Material& m, vtkProperty* p) const {
	geo3dml::Color diffuseColor = m.GetDiffuseColor();
	geo3dml::Color specularColor = m.GetSpecularColor();
	p->SetAmbient(m.GetAmbientIntensity());
	p->SetAmbientColor(diffuseColor.R(), diffuseColor.G(), diffuseColor.B());
	p->SetDiffuseColor(diffuseColor.R(), diffuseColor.G(), diffuseColor.B());
	p->SetSpecularColor(specularColor.R(), specularColor.G(), specularColor.B());
	p->SetOpacity(1 - m.GetTransparency());
}

void Actor::SetRandomRenderOption(vtkProperty* p) const {
	double r = 0, g = 0, b = 0;
	ColorMap* colorMap = ColorMap::NewDefaultMap();
	colorMap->RandomColor(r, g, b);
	delete colorMap;
	p->SetColor(r, g, b);
	p->SetPointSize(3);
	p->SetAmbient(0.25);
}

geo3dml::Material Actor::ToMaterial(vtkProperty* p) const {
	geo3dml::Material m;
	m.SetAmbientIntensity(p->GetAmbient());
	double* clr = p->GetDiffuseColor();
	m.SetDiffuseColor(geo3dml::Color(clr[0], clr[1], clr[2]));
	clr = p->GetSpecularColor();
	m.SetSpecularColor(geo3dml::Color(clr[0], clr[1], clr[2]));
	m.SetTransparency(1 - p->GetOpacity());
	return m;
}

void Actor::ToPointSymbolizer(vtkProperty* p, geo3dml::PointSymbolizer* sym) const {
	sym->SetSize(p->GetPointSize());
	sym->SetMaterial(ToMaterial(p));
}

void Actor::ToLineSymbolizer(vtkProperty* p, geo3dml::LineSymbolizer* sym) const {
	sym->SetWidth(p->GetLineWidth());
	sym->SetMaterial(ToMaterial(p));
}

void Actor::ToSurfaceSymbolizer(vtkProperty* p, geo3dml::SurfaceSymbolizer* sym) const {
	sym->SetFrontMaterial(ToMaterial(p));
}

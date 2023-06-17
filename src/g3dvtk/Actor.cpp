// UTF-8编码
#include <g3dvtk/Actor.h>
#include <g3dvtk/TIN.h>
#include <g3dvtk/CornerPointGrid.h>
#include <g3dvtk/UniformGrid.h>
#include <g3dvtk/LineString.h>
#include <g3dvtk/Point.h>
#include <g3dvtk/MultiPoint.h>
#include <g3dvtk/Annotation.h>
#include <g3dvtk/GTPVolume.h>
#include <g3dvtk/RectifiedGrid.h>
#include <g3dvtk/TetrahedronVolume.h>
#include <g3dvtk/CuboidVolume.h>
#include <g3dvtk/SGrid.h>
#include <g3dvtk/ObjectFactory.h>
#include <g3dvtk/ColorMap.h>
#include <vtkActor2D.h>
#include <vtkDataSetMapper.h>
#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageToStructuredGrid.h>
#include <vtkOpenGLActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkTexture.h>
#include <vtkTextureMapToCylinder.h>
#include <vtkTextureMapToPlane.h>
#include <vtkTextureMapToSphere.h>
#include <vtkTransformFilter.h>

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
	if (bindingGeometry_ == nullptr) {
		return;
	}
	g3dvtk::TIN* tin = dynamic_cast<g3dvtk::TIN*>(bindingGeometry_);
	if (tin != nullptr) {
		vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		geo3dml::SurfaceSymbolizer* surfaceSymbolizer = dynamic_cast<geo3dml::SurfaceSymbolizer*>(sym);
		if (surfaceSymbolizer != nullptr) {
			const geo3dml::Texture& texture = surfaceSymbolizer->GetFrontMaterial().GetTexture();
			if (texture.IsValid()) {
				vtkSmartPointer<vtkTextureMapToPlane> texPlane = vtkSmartPointer<vtkTextureMapToPlane>::New();
				texPlane->AutomaticPlaneGenerationOn();
				texPlane->SetInputData(tin->GetPolyData());
				mapper->SetInputConnection(texPlane->GetOutputPort());
				vtkNew<vtkImageReader2Factory> readerFactory;
				vtkSmartPointer<vtkImageReader2> texImage;
				texImage.TakeReference(readerFactory->CreateImageReader2(texture.GetImageURI().c_str()));
				texImage->SetFileName(texture.GetImageURI().c_str());
                vtkSmartPointer<vtkTexture> tex = vtkSmartPointer<vtkTexture>::New();
                tex->SetInputConnection(texImage->GetOutputPort());
                tex->InterpolateOn();
				switch (texture.GetWrapMode()) {
				case geo3dml::Texture::WrapMode::Repeat: {
					tex->SetWrap(vtkTexture::Repeat);
					break;
				}
				case geo3dml::Texture::WrapMode::MirrorRepeat: {
					tex->SetWrap(vtkTexture::MirroredRepeat);
					break;
				}
				case geo3dml::Texture::WrapMode::ClampToBorder: {
					const geo3dml::Color& borderColor = texture.GetBorderColor();
					tex->SetBorderColor(borderColor.R(), borderColor.G(), borderColor.B(), borderColor.A());
					tex->SetWrap(vtkTexture::ClampToBorder);
					break;
				}
				default: {
					tex->SetWrap(vtkTexture::ClampToEdge);
					break;
				}
				}
				actor->SetTexture(tex);
			} else {
				mapper->SetInputData(tin->GetPolyData());
			}
		} else {
			mapper->SetInputData(tin->GetPolyData());
		}
		mapper->Update();
		mapper->StaticOn();
		actor->SetMapper(mapper);
		if (surfaceSymbolizer != nullptr) {
			ConfigBySurfaceSymbolizer(surfaceSymbolizer, actor->GetProperty());
		} else {
			SetRandomRenderOption(actor->GetProperty());
		}
		vtkProp_ = actor;
	} else {
		g3dvtk::RectifiedGrid* rectGrid = dynamic_cast<g3dvtk::RectifiedGrid*>(bindingGeometry_);
		if (rectGrid != nullptr) {
			vtkSmartPointer<vtkImageToStructuredGrid> algo = vtkSmartPointer<vtkImageToStructuredGrid>::New();
			algo->SetInputData(rectGrid->GetUniformGrid());
			vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
			vtkNew<vtkMatrix4x4> matrix;
			G3DMatrixToVTKMatrix(rectGrid->ComputeTransformMatrix(), matrix);
			transform->SetMatrix(matrix);
			vtkNew<vtkTransformFilter> transFilter;
			transFilter->SetTransform(transform);
			transFilter->SetInputConnection(algo->GetOutputPort());
			vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
			mapper->SetInputConnection(transFilter->GetOutputPort());
			mapper->Update();	// 更新对象。否则将mapper设置为static后将不会再更新数据。
			mapper->StaticOn();
			vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
			actor->SetMapper(mapper);
			SetRandomRenderOption(actor->GetProperty());
			vtkProp_ = actor;
		} else {
			g3dvtk::GTPVolume* gtp = dynamic_cast<g3dvtk::GTPVolume*>(bindingGeometry_);
			if (gtp != nullptr) {
				vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
				mapper->SetInputData(gtp->GetVolumeData());
				mapper->StaticOn();
				vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
				actor->SetMapper(mapper);
				SetRandomRenderOption(actor->GetProperty());
				vtkProp_ = actor;
			} else {
				g3dvtk::CornerPointGrid* grid = dynamic_cast<g3dvtk::CornerPointGrid*>(bindingGeometry_);
				if (grid != nullptr) {
					vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
					mapper->SetInputData(grid->GetStructuredGrid());
					mapper->StaticOn();
					vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
					actor->SetMapper(mapper);
					SetRandomRenderOption(actor->GetProperty());
					vtkProp_ = actor;
				} else {
					g3dvtk::UniformGrid* grid = dynamic_cast<g3dvtk::UniformGrid*>(bindingGeometry_);
					if (grid != nullptr) {
						vtkSmartPointer<vtkImageToStructuredGrid> algo = vtkSmartPointer<vtkImageToStructuredGrid>::New();
						algo->SetInputData(grid->GetUniformGrid());
						vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
						mapper->SetInputConnection(algo->GetOutputPort());
						mapper->StaticOn();
						vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
						actor->SetMapper(mapper);
						SetRandomRenderOption(actor->GetProperty());
						vtkProp_ = actor;
					} else {
						g3dvtk::TetrahedronVolume* tetraVolume = dynamic_cast<g3dvtk::TetrahedronVolume*>(bindingGeometry_);
						if (tetraVolume != nullptr) {
							vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
							mapper->SetInputData(tetraVolume->GetVolumeData());
							mapper->StaticOn();
							vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
							actor->SetMapper(mapper);
							SetRandomRenderOption(actor->GetProperty());
							vtkProp_ = actor;
						} else {
							g3dvtk::CuboidVolume* cuboidVolume = dynamic_cast<g3dvtk::CuboidVolume*>(bindingGeometry_);
							if (cuboidVolume != nullptr) {
								vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
								mapper->SetInputData(cuboidVolume->GetVolumeData());
								mapper->StaticOn();
								vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
								actor->SetMapper(mapper);
								SetRandomRenderOption(actor->GetProperty());
								vtkProp_ = actor;
							} else {
								g3dvtk::SGrid* sGrid = dynamic_cast<g3dvtk::SGrid*>(bindingGeometry_);
								if (sGrid != nullptr) {
									vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
									mapper->SetInputData(sGrid->GetVolumeData());
									mapper->StaticOn();
									vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
									actor->SetMapper(mapper);
									SetRandomRenderOption(actor->GetProperty());
									vtkProp_ = actor;
								} else {
									g3dvtk::LineString* lineString = dynamic_cast<g3dvtk::LineString*>(bindingGeometry_);
									if (lineString != nullptr) {
										vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
										mapper->SetInputData(lineString->GetPolyData());
										mapper->StaticOn();
										vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
										actor->SetMapper(mapper);
										geo3dml::LineSymbolizer* lineSymbolizer = dynamic_cast<geo3dml::LineSymbolizer*>(sym);
										if (lineSymbolizer != nullptr) {
											ConfigByLineSymbolizer(lineSymbolizer, actor->GetProperty());
										} else {
											SetRandomRenderOption(actor->GetProperty());
										}
										vtkProp_ = actor;
									} else {
										g3dvtk::Point* point = dynamic_cast<g3dvtk::Point*>(bindingGeometry_);
										if (point != nullptr) {
											vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
											mapper->SetInputData(point->GetPolyData());
											mapper->StaticOn();
											vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
											actor->SetMapper(mapper);
											geo3dml::PointSymbolizer* pointSymbolizer = dynamic_cast<geo3dml::PointSymbolizer*>(sym);
											if (pointSymbolizer != nullptr) {
												ConfigByPointSymbolizer(pointSymbolizer, actor->GetProperty());
											} else {
												SetRandomRenderOption(actor->GetProperty());
											}
											vtkProp_ = actor;
										} else {
											g3dvtk::Annotation* annotation = dynamic_cast<g3dvtk::Annotation*>(bindingGeometry_);
											if (annotation != nullptr) {
												vtkSmartPointer<vtkLabeledDataMapper> labelMapper = vtkSmartPointer<vtkLabeledDataMapper>::New();
												annotation->ConfigLabelMapper(labelMapper);
												vtkSmartPointer<vtkActor2D> actor2D = vtkSmartPointer<vtkActor2D>::New();
												actor2D->SetMapper(labelMapper);
												vtkProp_ = actor2D;
											} else {
												g3dvtk::MultiPoint* mPoint = dynamic_cast<g3dvtk::MultiPoint*>(bindingGeometry_);
												if (mPoint != nullptr) {
													vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
													mapper->SetInputData(mPoint->GetPolyData());
													mapper->StaticOn();
													vtkSmartPointer<vtkOpenGLActor> actor = vtkSmartPointer<vtkOpenGLActor>::New();
													actor->SetMapper(mapper);
													geo3dml::PointSymbolizer* pointSymbolizer = dynamic_cast<geo3dml::PointSymbolizer*>(sym);
													if (pointSymbolizer != nullptr) {
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
	if (bindingGeometry_ == nullptr) {
		return nullptr;
	}
	if (vtkProp_ == nullptr || !vtkProp_->IsA("vtkActor")) {
		return nullptr;
	}
	vtkActor* actor = vtkActor::SafeDownCast(vtkProp_);
	g3dvtk::ObjectFactory g3dFactory;
	g3dvtk::TIN* tin = dynamic_cast<g3dvtk::TIN*>(bindingGeometry_);
	if (tin != nullptr) {
		geo3dml::SurfaceSymbolizer* surfaceSym = g3dFactory.NewSurfaceSymbolizer();
		ToSurfaceSymbolizer(actor->GetProperty(), surfaceSym);
		return surfaceSym;
	} else {
		g3dvtk::CornerPointGrid* grid = dynamic_cast<g3dvtk::CornerPointGrid*>(bindingGeometry_);
		if (grid != nullptr) {
			return nullptr;
		} else {
			g3dvtk::UniformGrid* grid = dynamic_cast<g3dvtk::UniformGrid*>(bindingGeometry_);
			if (grid != nullptr) {
				return nullptr;
			} else {
				g3dvtk::LineString* lineString = dynamic_cast<g3dvtk::LineString*>(bindingGeometry_);
				if (lineString != nullptr) {
					geo3dml::LineSymbolizer* lineSym = g3dFactory.NewLineSymbolizer();
					ToLineSymbolizer(actor->GetProperty(), lineSym);
					return lineSym;
				} else {
					g3dvtk::Point* point = dynamic_cast<g3dvtk::Point*>(bindingGeometry_);
					if (point != nullptr) {
						geo3dml::PointSymbolizer* pointSym = g3dFactory.NewPointSymbolizer();
						ToPointSymbolizer(actor->GetProperty(), pointSym);
						return pointSym;
					} else {
						g3dvtk::MultiPoint* mPoint = dynamic_cast<g3dvtk::MultiPoint*>(bindingGeometry_);
						if (mPoint != nullptr) {
							geo3dml::PointSymbolizer* pointSym = g3dFactory.NewPointSymbolizer();
							ToPointSymbolizer(actor->GetProperty(), pointSym);
							return pointSym;
						}
					}
				}
			}
		}
	}
	return nullptr;
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

void Actor::G3DMatrixToVTKMatrix(const geo3dml::Matrix4x4& g3dMatrix, vtkMatrix4x4* vtkMatrix) const {
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			vtkMatrix->SetElement(r, c, g3dMatrix.Element(r + 1, c + 1));
		}
	}
}

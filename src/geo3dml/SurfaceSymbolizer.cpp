#include <geo3dml/SurfaceSymbolizer.h>

using namespace geo3dml;

SurfaceSymbolizer::SurfaceSymbolizer() {
	isBackRenderEnabled_ = false;
	isVertexRenderEnabled_ = false;
	isFrameRenderEnabled_ = false;
}

SurfaceSymbolizer::~SurfaceSymbolizer() {

}

void SurfaceSymbolizer::SetFrontMaterial(const Material& m) {
	frontMaterial_ = m;
}

Material SurfaceSymbolizer::GetFrontMaterial() const {
	return frontMaterial_;
}

void SurfaceSymbolizer::EnableBackRender(bool enabled) {
	isBackRenderEnabled_ = enabled;
}

bool SurfaceSymbolizer::IsBackRenderEnabled() const {
	return isBackRenderEnabled_;
}

void SurfaceSymbolizer::SetBackMaterial(const Material& m) {
	backMaterial_ = m;
}

Material SurfaceSymbolizer::GetBackMaterial() const {
	return backMaterial_;
}

void SurfaceSymbolizer::EnableVertexRender(bool enabled) {
	isVertexRenderEnabled_ = enabled;
}

bool SurfaceSymbolizer::IsVertexRenderEnabled() const {
	return isVertexRenderEnabled_;
}

void SurfaceSymbolizer::SetVertexSymbolizer(const PointSymbolizer& pointSym) {
	vertexSymbolizer_ = pointSym;
}

PointSymbolizer SurfaceSymbolizer::GetVertexSymbolizer() const {
	return vertexSymbolizer_;
}

void SurfaceSymbolizer::EnableFrameRender(bool enabled) {
	isFrameRenderEnabled_ = enabled;
}

bool SurfaceSymbolizer::IsFrameRenderEnabled() const {
	return isFrameRenderEnabled_;
}

void SurfaceSymbolizer::SetFrameSymbolizer(const LineSymbolizer& lineSym) {
	frameSymbolizer_ = lineSym;
}

LineSymbolizer SurfaceSymbolizer::GetFrameSymbolizer() const {
	return frameSymbolizer_;
}

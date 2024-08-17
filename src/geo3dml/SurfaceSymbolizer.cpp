#include <geo3dml/SurfaceSymbolizer.h>

using namespace geo3dml;

SurfaceSymbolizer::SurfaceSymbolizer() {
	isBackRenderEnabled_ = false;
	isVertexRenderEnabled_ = false;
	isFrameRenderEnabled_ = false;
	vertexSymbolizer_ = nullptr;
	frameSymbolizer_ = nullptr;
}

SurfaceSymbolizer::~SurfaceSymbolizer() {
	if (vertexSymbolizer_ != nullptr) {
		delete vertexSymbolizer_;
	}
	if (frameSymbolizer_ != nullptr) {
		delete frameSymbolizer_;
	}
}

void SurfaceSymbolizer::SetFrontMaterial(const PBRMaterial& m) {
	frontMaterial_ = m;
}

const PBRMaterial& SurfaceSymbolizer::GetFrontMaterial() const {
	return frontMaterial_;
}

void SurfaceSymbolizer::EnableBackRender(bool enabled) {
	isBackRenderEnabled_ = enabled;
}

bool SurfaceSymbolizer::IsBackRenderEnabled() const {
	return isBackRenderEnabled_;
}

void SurfaceSymbolizer::SetBackMaterial(const PBRMaterial& m) {
	backMaterial_ = m;
}

const PBRMaterial& SurfaceSymbolizer::GetBackMaterial() const {
	return backMaterial_;
}

void SurfaceSymbolizer::EnableVertexRender(bool enabled) {
	isVertexRenderEnabled_ = enabled;
}

bool SurfaceSymbolizer::IsVertexRenderEnabled() const {
	return isVertexRenderEnabled_;
}

void SurfaceSymbolizer::SetVertexSymbolizer(PointSymbolizer* pointSym) {
	vertexSymbolizer_ = pointSym;
}

PointSymbolizer* SurfaceSymbolizer::GetVertexSymbolizer() const {
	return vertexSymbolizer_;
}

void SurfaceSymbolizer::EnableFrameRender(bool enabled) {
	isFrameRenderEnabled_ = enabled;
}

bool SurfaceSymbolizer::IsFrameRenderEnabled() const {
	return isFrameRenderEnabled_;
}

void SurfaceSymbolizer::SetFrameSymbolizer(LineSymbolizer* lineSym) {
	frameSymbolizer_ = lineSym;
}

LineSymbolizer* SurfaceSymbolizer::GetFrameSymbolizer() const {
	return frameSymbolizer_;
}

// UTF-8编码
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

Symbolizer* SurfaceSymbolizer::Clone() const {
    SurfaceSymbolizer* sym = new SurfaceSymbolizer();
    sym->isBackRenderEnabled_ = isBackRenderEnabled_;
    sym->isVertexRenderEnabled_ = isVertexRenderEnabled_;
    sym->isFrameRenderEnabled_ = isFrameRenderEnabled_;
    sym->frontMaterial_ = frontMaterial_;
    sym->backMaterial_ = backMaterial_;
    if (vertexSymbolizer_ != nullptr) {
        sym->vertexSymbolizer_ = dynamic_cast<PointSymbolizer*>(vertexSymbolizer_->Clone());
    }
    if (frameSymbolizer_ != nullptr) {
        sym->frameSymbolizer_ = dynamic_cast<LineSymbolizer*>(frameSymbolizer_->Clone());
    }
    return sym;
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
	if (vertexSymbolizer_ != nullptr) {
		delete vertexSymbolizer_;
	}
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
	if (frameSymbolizer_ != nullptr) {
		delete frameSymbolizer_;
	}
	frameSymbolizer_ = lineSym;
}

LineSymbolizer* SurfaceSymbolizer::GetFrameSymbolizer() const {
	return frameSymbolizer_;
}

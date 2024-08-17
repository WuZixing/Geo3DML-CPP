#pragma once

#include "PointSymbolizer.h"
#include "LineSymbolizer.h"

namespace geo3dml {

	class SurfaceSymbolizer : public Symbolizer {
	public:
		SurfaceSymbolizer();
		virtual ~SurfaceSymbolizer();

		//@{
		void SetFrontMaterial(const PBRMaterial& m);
		const PBRMaterial& GetFrontMaterial() const;
		//@}
		
		//@{
		void EnableBackRender(bool enabled = false);
		bool IsBackRenderEnabled() const;
		void SetBackMaterial(const PBRMaterial& m);
		const PBRMaterial& GetBackMaterial() const;
		//@}

		//@{
		void EnableVertexRender(bool enabled = false);
		bool IsVertexRenderEnabled() const;
		void SetVertexSymbolizer(PointSymbolizer* pointSym);
		PointSymbolizer* GetVertexSymbolizer() const;
		//@}

		//@{
		void EnableFrameRender(bool enabled = false);
		bool IsFrameRenderEnabled() const;
		void SetFrameSymbolizer(LineSymbolizer* lineSym);
		LineSymbolizer* GetFrameSymbolizer() const;
		//@}

	private:
		bool isBackRenderEnabled_, isVertexRenderEnabled_, isFrameRenderEnabled_;
		PBRMaterial frontMaterial_, backMaterial_;
		PointSymbolizer* vertexSymbolizer_;
		LineSymbolizer* frameSymbolizer_;
	};
}

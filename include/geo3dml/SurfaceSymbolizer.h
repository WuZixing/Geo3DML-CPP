#pragma once

#include "PointSymbolizer.h"
#include "LineSymbolizer.h"

namespace geo3dml {

	class SurfaceSymbolizer : public Symbolizer {
	public:
		SurfaceSymbolizer();
		virtual ~SurfaceSymbolizer();

		//@{
		void SetFrontMaterial(const Material& m);
		Material GetFrontMaterial() const;
		//@}
		
		//@{
		void EnableBackRender(bool enabled = false);
		bool IsBackRenderEnabled() const;
		void SetBackMaterial(const Material& m);
		Material GetBackMaterial() const;
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
		Material frontMaterial_, backMaterial_;
		PointSymbolizer* vertexSymbolizer_;
		LineSymbolizer* frameSymbolizer_;
	};
}

// UTF-8编码
#pragma once

#include "PointSymbolizer.h"
#include "LineSymbolizer.h"

namespace geo3dml {

	class SurfaceSymbolizer : public Symbolizer {
	public:
		SurfaceSymbolizer();
		virtual ~SurfaceSymbolizer();

		///@name 实现父类定义的接口。
		///@{
		virtual Symbolizer* Clone() const override;
		///@}

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
		/// @brief 设置顶点的可视化参数。
        /// @param pointSym 顶点的可视化参数。该指针所指的对象由本类负责管理。
		void SetVertexSymbolizer(PointSymbolizer* pointSym);
        /// @brief 取顶点的可视化参数。
        /// @return 顶点的可视化参数。返回的指针所指向的对象由本类负责管理。
		PointSymbolizer* GetVertexSymbolizer() const;
		//@}

		//@{
		void EnableFrameRender(bool enabled = false);
		bool IsFrameRenderEnabled() const;
		/// @brief 设置三角形边的可视化参数。
        /// @param lineSym 边的可视化参数。该指针所指的对象由本类负责管理。
		void SetFrameSymbolizer(LineSymbolizer* lineSym);
        /// @brief 取三角形边的可视化参数。
        /// @return 边的可视化参数。返回的指针所指向的对象由本类负责管理。
		LineSymbolizer* GetFrameSymbolizer() const;
		//@}

	private:
		bool isBackRenderEnabled_, isVertexRenderEnabled_, isFrameRenderEnabled_;
		PBRMaterial frontMaterial_, backMaterial_;
		PointSymbolizer* vertexSymbolizer_;
		LineSymbolizer* frameSymbolizer_;
	};
}

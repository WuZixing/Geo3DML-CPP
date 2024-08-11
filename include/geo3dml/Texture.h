// UTF-8编码
#pragma once

#include <string>
#include "Color.h"

namespace geo3dml {
    /// @brief 参照国标（GB/T958-2015 区域地质图图例）定义的图例符号。
    class GBSymbol {
    public:
        /// @brief 检查图例符号定义是否为空。
        /// @return 为空时返回true，否则返回false。
        bool IsEmpty() const;

        /// @brief 清除符号参数。
        void Clear();

        /// 图例代码。
        void SetCode(const std::string& code);
        const std::string& GetCode() const;

        /// 符号的前景色。
        void SetStrokeColor(const Color& clr);
        const Color& GetStrokeColor() const;

        /// 符号的填充色。
        void SetFillColor(const Color& clr);
        const Color& GetFillColor() const;

    private:
        /// 图例代码。
        std::string code_;
        /// 符号的前景颜色。
        Color strokeColor_;
        /// 符号的填充颜色。
        Color fillColor_;
    };

    /// @brief 纹理。暂时仅支持geo3dml:AbstractTexture所定义的基本纹理属性，主要包括图片文件地址和铺设模式。不支持纹理坐标等其它参数。
    /// 纹理图片可以是普通图片，也可以是国标定义的地质图图例符号。
    class Texture {
    public:
        /// @brief 纹理铺设模式
        enum class WrapMode {
            Default = 0,    ///< 单幅填充
            Repeat,         ///< 重复
            MirrorRepeat,   ///< 镜像重复
            ClampToEdge,    ///< 按纹理图片的边界扩展
            ClampToBorder   ///< 按定义的边界颜色扩展
        };

    public:
        Texture();

        bool IsValid() const;

        bool IsImageEmpty() const;
        bool IsGBSymbolEmpty() const;

        /// @name 基于图片的纹理。设置纹理图片将清除基于国标地质图图例符号的纹理。
        ///@{
        void SetImageURI(const std::string& uri);
        const std::string& GetImageURI() const;
        void SetImageMime(const std::string& mime);
        const std::string& GetImageMime() const;
        ///@}

        /// @name 基于国标（GB/T958-2015 区域地质图图例）图例符号的纹理。设置国标图例符号将清除基于图片的纹理。
        ///@{
        void SetGBSymbol(const GBSymbol& symbol);
        const GBSymbol& GetGBSymbol() const;
        ///@}

        void SetWrapMode(WrapMode mode);
        WrapMode GetWrapMode() const;
        void SetBorderColor(const Color& clr);
        const Color& GetBorderColor() const;
    
    private:
        std::string imageURI_, imageMime_;
        GBSymbol gbSymbol_;
        Color borderColor_;
        WrapMode wrapMode_;
    };
}

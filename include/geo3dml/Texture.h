// UTF-8编码
#pragma once

#include <string>
#include "Color.h"

namespace geo3dml {

    /// @brief 纹理。暂时仅支持geo3dml:AbstractTexture所定义的基本纹理属性，主要包括图片文件地址和铺设模式。不支持纹理坐标等其它参数。
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

        void SetImageURI(const std::string& uri);
        const std::string& GetImageURI() const;
        void SetImageMime(const std::string& mime);
        const std::string& GetImageMime() const;
        void SetWrapMode(WrapMode mode);
        WrapMode GetWrapMode() const;
        void SetBorderColor(const Color& clr);
        const Color& GetBorderColor() const;
    
    private:
        std::string imageURI_, imageMime_;
        Color borderColor_;
        WrapMode wrapMode_;
    };
}

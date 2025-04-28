// UTF-8编码
#pragma once

#include <geo3dml/Actor.h>

namespace geo3dml {
    namespace geometry {
        class Actor : public geo3dml::Actor {
        public:
            Actor();
            virtual ~Actor();

            /// @name 实现父类定义的接口。
            ///@{
            virtual void BindGeometry(geo3dml::Feature* feature, geo3dml::Geometry* geo, geo3dml::Symbolizer* sym);
            virtual geo3dml::Feature* GetBindingFeature() const;
            virtual geo3dml::Geometry* GetBindingGeometry() const;
            virtual bool IsVisible() const;
            virtual void SetVisible(bool show);
            virtual geo3dml::Symbolizer* MakeSymbozier() const;
            ///@}

        private:
            geo3dml::Feature* bindingFeature_;
            geo3dml::Geometry* bindingGeometry_;
            geo3dml::Symbolizer* symbolizer_;
            bool isVisible_;
        };
    }
}

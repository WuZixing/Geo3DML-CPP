// UTF-8编码
#pragma once

#include <geo3dml/Annotation.h>

namespace geo3dml {
    namespace geometry {
        class Annotation : public geo3dml::Annotation {
        public:
            Annotation();
            virtual ~Annotation();

        public:
            /// @name 实现父类定义的接口。
            ///@{
            virtual void SetLabelOfPointAt(int i, const std::string& s) override;
            virtual const std::string& GetLabelOfPointAt(int i) const override;
            ///@}

            /// @name 实现基类 geo3dml::MultiPoint 定义的接口。
            ///@{
            virtual void AddPoint(double x, double y, double z) override;
            virtual int GetPointCount() const override;
            virtual void GetPointAt(int i, double& x, double& y, double& z) const override;
            ///@}

            /// @name 基类 geo3dml::Geometry 定义的接口。
            ///@{
            virtual geo3dml::Box3D GetMinimumBoundingRectangle() const override;
            ///@}

        private:
            struct Note {
                Point3D pt;
                std::string label_;
            };
            std::vector<Note> notes_;
        };
    }
}

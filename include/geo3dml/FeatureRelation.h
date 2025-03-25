// UTF-8编码
#pragma once

#include "Feature.h"

namespace geo3dml {
    /// 地质要素的关系。
    class FeatureRelation : public Object {
    public:
        FeatureRelation();
        virtual ~FeatureRelation();

    public:
        /// @name 要素关系的名称。
        ///@{
        FeatureRelation& SetName(const std::string& name);
        const std::string& GetName() const;
        ///@}

        /// @name 关系中的源地质要素。
        ///@{
        /// @brief 设置关系中的源地质要素。
        /// @param featureId 源地质要素的ID。
        /// @return 返回关于本要素对象自身的引用。
        FeatureRelation& SetSourceFeatureId(const std::string& featureId);
        /// @brief 取关系中的源地质要素的ID。
        /// @return 源地质要素的ID。
        const std::string& GetSourceFeatureId() const;

        /// @name 设置源地质要素在关系中的角色。
        /// @param role 源地质要素在关系中的角色。
        /// @return 返回关于本要素对象自身的引用。
        FeatureRelation& SetSourceRole(const std::string& role);
        /// @brief 取源地质要素在关系中的角色。
        /// @return 源地质要素在关系中的角色。
        const std::string& GetSourceRole() const;
        ///@}

        /// @name 关系中的目标地质要素。目标地质要素可以有多个。
        ///@{
        /// @brief 添加关系中的目标地质要素。
        /// @param featureId 目标地质要素的ID。
        void AddTargetFeatureId(const std::string& featureId);
        /// @brief 查询目标地质要素的数目。
        /// @return 目标地质要素的数目。
        int GetTargetFeatureCount() const;
        /// @brief 查询目标地质要素的ID。
        /// @param i 目标地质要素的索引号（从0开始计数）。
        /// @return 目标地质要素的ID。
        const std::string& GetTargetFeatureId(int i);

        /// @brief 设置目标地质要素在关系中的角色。
        /// @param role 目标地质要素在关系中的角色。
        /// @return 返回关于本要素对象自身的引用。
        FeatureRelation& SetTargetRole(const std::string& role);
        /// @brief 取目标地质要素在关系中的角色。
        /// @return 目标地质要素在关系中的角色。
        const std::string GetTargetRole() const;
        ///@}

    private:
        /// 关系的名称。
        std::string name_;

        /// 源地质要素的ID。
        std::string sourceFeatureId_;
        /// 源地质要素在关系中的角色。
        std::string sourceRole_;

        /// 目标地质要素的ID。
        std::vector<std::string> targetFeatureIds_;
        /// 目标地质要素在关系中的角色。
        std::string targetRole_;
    };
}

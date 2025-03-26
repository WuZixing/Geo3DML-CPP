// UTF-8编码
#pragma once

#include "Feature.h"

namespace geo3dml {
    /// 地质要素的关系。
    class FeatureRelation : public Object {
    public:
        /// @brief 地质要素关系的类型。
        enum class RelationType {
            GENERAL,                ///< 通用的关系。
            GEOLOGICAL_HISTORY,     ///< 地质历史（或地质年代）关系。
            CONTACT,                ///< 接触关系。如不整合接触关系，源地质要素的角色是“上覆地层”（或“下伏地层”），目标地质要素的角色是“下伏地层”（或“上覆地层”）。
            INTRUSIVE,              ///< 侵入体与围岩形成侵入关系，其中关系的名称是“侵入”，源地质要素的角色是“侵入体”，目标地质要素的角色是“围岩”。
            GEOLOGICAL_STRUCTURE,   ///< 其它地质构造关系。
            AGGREGATION,            ///< 聚合关系，表达地质要素由一个或多个其它地质要素聚合而成的关系。如某个断层面由多个小断面聚合而成，其中源表示被组成的地质要素，目标则是组成的部分。该关系可用于描述地质要素之间的普通聚合关系，不一定具有明确的地质含义。
            BOUNDARY                ///< 地质要素由作为其边界的其它地质要素包围而成的关系。该关系的源是边界所围成的地质要素，目标则是组成边界的要素。
        };
        /// @name 地质要素关系的类型枚举值对应的名字。
        ///@{
        static RelationType NameToFeatureRelationType(const std::string& name);
        static std::string FeatureRelationTypeToName(RelationType t);
        ///@}

    public:
        FeatureRelation(RelationType type);
        virtual ~FeatureRelation();

    public:
        /// 取地质要素关系的类别。
        RelationType GetRelationType() const;

        /// @name 要素关系实例的名称（不是抽象关系的名称）。如“要素A与B的年代关系”等。
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

        /// @brief 设置源地质要素在关系中的角色。
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
        const std::string& GetTargetRole() const;
        ///@}

    private:
        /// 关系的类别。
        RelationType type_;

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

// UTF-8编码
#pragma once
#include "AbstractMetadata.h"

namespace geo3dml {
    /// @brief 项目/工程的元数据信息。
    class ProjectMetadata : public AbstractMetadata {
    public:
        /// @name 重载父类定义的方法。
        ///@{
        virtual bool IsEmpty() const override;
        ///@}

        /// @brief 检查工作项目信息是否为空。
        /// @return 工作项目信息为空时返回true，否则返回false。
        bool IsProjectInfoEmpty() const;
        
        /// @name 工作项目的名字。
        ///@{
        const std::string& GetProjectName() const;
        void SetProjectName(const std::string& name);
        ///@}

        /// @name 工作项目的编号。
        ///@{
        const std::string& GetProjectCode() const;
        void SetProjectCode(const std::string& code);
        ///@}

        /// @name 工作项目的起止日期。
        ///@{
        const std::string& GetStartDate() const;
        void SetStartDate(const std::string& s);
        const std::string& GetCompleteDate() const;
        void SetCompleteDate(const std::string& s);
        ///@}

        /// @name 工作项目承包商。
        ///@{
        const std::string& GetContractor() const;
        void SetContractor(const std::string& contractor);
        ///@}

    private:
        /// 工作项目的名字。
        std::string projectName_;
        /// 工作项目的编号。
        std::string projectCode_;
        /// 工作项目的起止日期。
        std::string startDate_, completeDate_;
        /// 工作项目承包商的名字。
        std::string contractor_;
    };
}

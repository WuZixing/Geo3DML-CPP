// UTF-8编码
#pragma once

#include <string>

namespace geo3dml {
    /// @brief Geo3DML元数据基类。
    class AbstractMetadata {
	public:
		virtual ~AbstractMetadata();

    public:
		/// @brief 检查元数据信息是否为空。
		/// @return 
		virtual bool IsEmpty() const;

        /// @brief 对象的说明信息。
        const std::string& GetDescription() const;
        void SetDescription(const std::string& s);

		/// @name 责任人、单位与联系方式。
		///@{
		/// @brief 检查联系人信息是否为空。
		/// @return 联系人信息为空时返回true，否则返回false。
		bool IsContactEmpty() const;
		/// 责任人名字。
		const std::string& GetResponsibleIndividualName() const;
		void SetResponsibleIndividualName(const std::string& name);
		/// 责任单位名字。
		const std::string& GetResponsibleOrganisationName() const;
		void SetResponsibleOrganisationName(const std::string& name);
		/// 联系电话。
		const std::string& GetContactPhone() const;
		void SetContactPhone(const std::string& phone);
		/// 联系地址。
		const std::string& GetContactAddress() const;
		void SetContactAddress(const std::string& address);
		/// Email地址。
		const std::string& GetContactEmail() const;
		void SetContactEmail(const std::string& email);
		///@}

    private:
        std::string description_;
		std::string nameOfResponsibleIndividual_, nameOfResponsibleOrganisation_, contactPhone_, contactAddress_, contactEmail_;
    };
}

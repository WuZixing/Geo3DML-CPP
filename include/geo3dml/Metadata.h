// UTF-8编码
#pragma once

#include <string>

namespace geo3dml {

    /// @brief 模型的元数据。
    class Metadata {
    public:
		Metadata();
		~Metadata();

		/// 模型构建的时间，如“2013-11-13T14:20:33”、“2013-11-13”、“2013年11月13日”等。
		///@{
		/// @brief 取模型构建时间。
		/// @param isDateTime 输出值为true时表示返回的时间字符串为日期和时间的组合，否则表示返回的字符串为日期。
		/// @return 返回模型构建时间。
		const std::string& GetDateStamp(bool& isDateTime) const;
		void SetDateStamp(const std::string& s, bool isDateIime = false);
		///@}

		/// @brief 模型的说明信息。
		const std::string& GetDescription() const;
		void SetDescription(const std::string& s);

		/// @brief 模型的版本。
		const std::string& GetVersion() const;
		void SetVersion(const std::string& s);

		/// @brief 建模工具名称。
		const std::string& GetToolName() const;
		void SetToolName(const std::string& s);

		/// @brief 建模工具的版本号。
		const std::string& GetToolVersion() const;
		void SetToolVersion(const std::string& s);

		/// @name 空间坐标参照系。
		///@{
		/// 对应于元素"CoordinateReferenceSystemIdentifier"。
		const std::string& GetCoordRefSysID() const;
		void SetCoordRefSysID(const std::string& crsID);
		/// 对应于元素"CoordinateSystemType"。
		const std::string& GetCoordSysType() const;
		void SetCoordSysType(const std::string& sysType);
		/// 对应于元素"CoordinateSystemIdentifier"。
		const std::string& GetCoordSysID() const;
		void SetCoordSysID(const std::string& csID);
		///@}

		/// @name 责任人、单位与联系方式。
		///@{
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
		bool isDateStampDateTime_;
		std::string dateStamp_, description_, version_, toolName_, toolVersion_;
		std::string coordRefSysId_, coordSysType_, coordSysId_;
		std::string nameOfResponsibleIndividual_, nameOfResponsibleOrganisation_, contactPhone_, contactAddress_, contactEmail_;
    };
}

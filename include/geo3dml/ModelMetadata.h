// UTF-8编码
#pragma once
#include "AbstractMetadata.h"

namespace geo3dml {

    /// @brief 模型的元数据。
    class ModelMetadata : public AbstractMetadata {
    public:
		ModelMetadata();
		~ModelMetadata();

		/// 模型构建的时间，如“2013-11-13T14:20:33”、“2013-11-13”、“2013年11月13日”等。
		///@{
		/// @brief 取模型构建时间。
		/// @param isDateTime 输出值为true时表示返回的时间字符串为日期和时间的组合，否则表示返回的字符串为日期。
		/// @return 返回模型构建时间。
		const std::string& GetDateStamp(bool& isDateTime) const;
		void SetDateStamp(const std::string& s, bool isDateIime = false);
		///@}

		/// @brief 模型的版本。
		const std::string& GetVersion() const;
		void SetVersion(const std::string& s);

		/// @brief 建模工具名称。
		const std::string& GetToolName() const;
		void SetToolName(const std::string& s);

		/// @brief 建模工具的版本号。
		const std::string& GetToolVersion() const;
		void SetToolVersion(const std::string& s);

		/// @brief 模型的专题类型，如水文地质、工程地质等。
		const std::string& GetTopicCategory() const;
		void SetTopicCategory(const std::string& topic);

		/// @name 空间坐标参照系。
		///@{
		/// 对应于元素"CoordinateReferenceSystem:Identifier"。
		const std::string& GetCoordRefSysID() const;
		void SetCoordRefSysID(const std::string& crsID);
		/// 对应于元素"CoordinateReferenceSystem:Parameter"。
		const std::string& GetCoordRefSysParam() const;
		void SetCoordRefSysParam(const std::string& crsParam);
		/// 对应于元素"VerticalReferenceSystem:Category"。
		const std::string& GetVerticalRefSysCategory() const;
		void SetVerticalRefSysCategory(const std::string& vrsCategory);
		/// 对应于元素"VerticalReferenceSystem:ReferenceSystem"。
		const std::string& GetVerticalRefSysValue() const;
		void SetVerticalRefSysValue(const std::string& vRefSys);
		///@}

	private:
		bool isDateStampDateTime_;
		std::string dateStamp_, version_, toolName_, toolVersion_, topicCategory_;
		std::string coordRefSysId_, coordRefSysParam_, verticalRefSysCategory_, verticalRefSysValue_;
    };
}

// UTF-8编码
#pragma once

#include <string>

namespace g3dxml {

	/// Versions of Geo3DML XML schema.
	enum SchemaVersion {
		Schema_Unknown,
		Schema_1_0,		///< v1.0，即中国地质调查局标准。
		Schema_2_0,		///< v2.0，即中国地理信息协会标准。
		Schema_2_x,		///< v2.x
	};
	std::string SchemaVersionToString(SchemaVersion v);
	SchemaVersion StringToSchemaVersion(const std::string& s);

	class XMLIO {
	public:
		XMLIO();
		virtual ~XMLIO();

		bool IsOK() const;
		std::string Error() const;

	protected:
		void SetStatus(bool isOK, const std::string& message = "");

	private:
		bool isOK_;
		std::string errorMessage_;
	};
}

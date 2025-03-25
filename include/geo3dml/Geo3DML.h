// UTF-8编码
#pragma once

#include <string>

namespace geo3dml {
	class Object {
	public:
		/// @brief 生成一个新的对象ID。
		/// @return 新ID。
		static std::string NewID();

	public:
		Object();
		virtual ~Object();

		const std::string& GetID() const;
		void SetID(const std::string& id);

	private:
		std::string id_;
	};
}

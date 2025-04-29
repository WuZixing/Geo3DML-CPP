// UTF-8编码
#pragma once

namespace geo3dml {
	/// Visualization parameter.
	class Symbolizer {
	public:
		Symbolizer();
		virtual ~Symbolizer();

        /// @brief 复制可视化参数对象。
        /// @return 复制的可视化参数对象。该指针所指向的对象由调用者负责管理。
        virtual Symbolizer* Clone() const = 0;
	};
}

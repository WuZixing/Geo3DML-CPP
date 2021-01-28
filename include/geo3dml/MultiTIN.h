#pragma once

#include "TIN.h"

namespace geo3dml {

	class MultiTIN: public Geometry {
	public:
		MultiTIN();
		virtual ~MultiTIN();

	public:
		virtual void AddTIN(TIN* tin) = 0;
		virtual int GetTINCount() const = 0;
		virtual TIN* GetTIN(int i) const = 0;
	};
}

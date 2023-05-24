#pragma once

#include <string>
#include <vector>
#include "StyleRule.h"
#include "Feature.h"

namespace geo3dml {

	class Style {
	public:
		Style();
		virtual ~Style();

		void SetID(const std::string& id);
		std::string GetID() const;

		void SetName(const std::string& name);
		std::string GetName() const;

		void AddRule(StyleRule* rule);
		int GetRuleCount() const;
		StyleRule* GetRuleAt(int i);
		StyleRule* MatchWithFeature(Feature* f) const;

	protected:
		/// 保持当前类为存续类而定义的接口。
		virtual void Reserved() = 0;

	private:
		std::string id_, name_;
		std::vector<StyleRule*> rules_;
	};
}

#pragma once

#include <string>
#include <vector>
#include "StyleRule.h"
#include "Feature.h"

namespace geo3dml {

	class Geo3DStyle {
	public:
		Geo3DStyle();
		virtual ~Geo3DStyle();

		void SetID(const std::string& id);
		std::string GetID() const;

		void SetName(const std::string& name);
		std::string GetName() const;

		void AddRule(StyleRule* rule);
		int GetRuleCount() const;
		StyleRule* GetRuleAt(int i);
		StyleRule* MatchWithFeature(Feature* f) const;

	protected:
		virtual void Reserved() = 0;

	private:
		std::string id_, name_;
		std::vector<StyleRule*> rules_;
	};
}

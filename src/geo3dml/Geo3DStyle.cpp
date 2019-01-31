#include <geo3dml/Geo3DStyle.h>

using namespace geo3dml;

Geo3DStyle::Geo3DStyle() {

}

Geo3DStyle::~Geo3DStyle() {
	std::vector<StyleRule*>::const_iterator ruleItor = rules_.cbegin();
	while (ruleItor != rules_.cend()) {
		delete *ruleItor;
		++ruleItor;
	}
}

void Geo3DStyle::SetID(const std::string& id) {
	id_ = id;
}

std::string Geo3DStyle::GetID() const {
	return id_;
}

void Geo3DStyle::SetName(const std::string& name) {
	name_ = name;
}

std::string Geo3DStyle::GetName() const {
	return name_;
}

void Geo3DStyle::AddRule(StyleRule* rule) {
	if (rule == NULL) {
		return;
	}
	std::vector<StyleRule*>::const_iterator ruleItor = rules_.cbegin();
	while (ruleItor != rules_.cend()) {
		if (*ruleItor == rule) {
			return;
		}
		++ruleItor;
	}
	rules_.push_back(rule);
}

int Geo3DStyle::GetRuleCount() const {
	return (int)rules_.size();
}

StyleRule* Geo3DStyle::GetRuleAt(int i) {
	return rules_.at(i);
}

StyleRule* Geo3DStyle::MatchWithFeature(Feature* f) const {
	std::vector<StyleRule*>::const_iterator ruleItor = rules_.cbegin();
	while (ruleItor != rules_.cend()) {
		if ((*ruleItor)->DoesFeatureMatch(f)) {
			return *ruleItor;
		}
		++ruleItor;
	}
	return NULL;
}

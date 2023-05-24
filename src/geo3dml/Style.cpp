#include <geo3dml/Style.h>

using namespace geo3dml;

Style::Style() {

}

Style::~Style() {
	std::vector<StyleRule*>::const_iterator ruleItor = rules_.cbegin();
	while (ruleItor != rules_.cend()) {
		delete *ruleItor;
		++ruleItor;
	}
}

void Style::SetID(const std::string& id) {
	id_ = id;
}

std::string Style::GetID() const {
	return id_;
}

void Style::SetName(const std::string& name) {
	name_ = name;
}

std::string Style::GetName() const {
	return name_;
}

void Style::AddRule(StyleRule* rule) {
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

int Style::GetRuleCount() const {
	return (int)rules_.size();
}

StyleRule* Style::GetRuleAt(int i) {
	return rules_.at(i);
}

StyleRule* Style::MatchWithFeature(Feature* f) const {
	std::vector<StyleRule*>::const_iterator ruleItor = rules_.cbegin();
	while (ruleItor != rules_.cend()) {
		if ((*ruleItor)->DoesFeatureMatch(f)) {
			return *ruleItor;
		}
		++ruleItor;
	}
	return NULL;
}

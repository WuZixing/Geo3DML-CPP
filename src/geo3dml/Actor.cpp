#include <geo3dml/Actor.h>

using namespace geo3dml;

Actor::Actor() {

}

Actor::~Actor() {

}

void Actor::SetName(const std::string& name) {
	name_ = name;
}

std::string Actor::GetName() const {
	return name_;
}

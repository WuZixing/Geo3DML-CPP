// UTF-8编码
#include "Annotation.h"

using namespace geo3dml::geometry;

Annotation::Annotation() {

}

Annotation::~Annotation() {

}

void Annotation::SetLabelOfPointAt(int i, const std::string& s) {
    notes_[i].label_ = s;
}

const std::string& Annotation::GetLabelOfPointAt(int i) const {
    return notes_[i].label_;
}

void Annotation::AddPoint(double x, double y, double z) {
    Note note;
    note.pt.x = x;
    note.pt.y = y;
    note.pt.z = z;
    notes_.emplace_back(note);
}

int Annotation::GetPointCount() const {
    return notes_.size();
}

void Annotation::GetPointAt(int i, double& x, double& y, double& z) const {
    const Note& note = notes_.at(i);
    x = note.pt.x;
    y = note.pt.y;
    z = note.pt.z;
}

geo3dml::Box3D Annotation::GetMinimumBoundingRectangle() const {
    geo3dml::Box3D box;
    for (auto citor = notes_.cbegin(); citor != notes_.cend(); ++citor) {
        box.ExtendWith(citor->pt);
    }
    return box;
}

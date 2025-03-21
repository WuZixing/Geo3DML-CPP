// UTF-8编码
#include "ShapeProperty.h"

using namespace geo3dml::geometry;

ShapeProperty::ShapeProperty() {

}

ShapeProperty::~ShapeProperty() {

}

void ShapeProperty::FillDoubleValue(const std::string& fieldName, int numberOfValues, double v) {
    Field field = GetField(fieldName);
    if (field.DataType() != Field::ValueType::Double) {
        return;
    }
    auto itor = doubleFields_.find(fieldName);
    if (itor == doubleFields_.end()) {
        doubleFields_[fieldName] = std::vector<double>(numberOfValues, v);
    } else {
        itor->second.assign(numberOfValues, v);
    }
}

double ShapeProperty::DoubleValue(const std::string& fieldName, int targetIndex) const {
    auto citor = doubleFields_.find(fieldName);
    if (citor != doubleFields_.cend()) {
        return citor->second[targetIndex];
    } else {
        return 0;
    }
}

geo3dml::ShapeProperty& ShapeProperty::DoubleValue(const std::string& fieldName, int targetIndex, double v) {
    auto itor = doubleFields_.find(fieldName);
    if (itor != doubleFields_.end()) {
        itor->second[targetIndex] = v;
    }
    return *this;
}

void ShapeProperty::FillTextValue(const std::string& fieldName, int numberOfValues, const std::string& v) {
    Field field = GetField(fieldName);
    if (field.DataType() != Field::ValueType::Text && field.DataType() != Field::ValueType::Category) {
        return;
    }
    auto itor = textFields_.find(fieldName);
    if (itor == textFields_.end()) {
        textFields_[fieldName] = std::vector<std::string>(numberOfValues, v);
    } else {
        itor->second.assign(numberOfValues, v);
    }
}

std::string ShapeProperty::TextValue(const std::string& fieldName, int targetIndex) const {
    auto citor = textFields_.find(fieldName);
    if (citor != textFields_.cend()) {
        return citor->second[targetIndex];
    } else {
        return std::string();
    }
}

geo3dml::ShapeProperty& ShapeProperty::TextValue(const std::string& fieldName, int targetIndex, const std::string& v) {
    auto itor = textFields_.find(fieldName);
    if (itor != textFields_.end()) {
        itor->second[targetIndex] = v;
    }
    return *this;
}

void ShapeProperty::FillIntValue(const std::string& fieldName, int numberOfValues, int v) {
    Field field = GetField(fieldName);
    if (field.DataType() != Field::ValueType::Integer) {
        return;
    }
    auto itor = intFields_.find(fieldName);
    if (itor == intFields_.end()) {
        intFields_[fieldName] = std::vector<int>(numberOfValues, v);
    } else {
        itor->second.assign(numberOfValues, v);
    }
}

int ShapeProperty::IntValue(const std::string& fieldName, int targetIndex) const {
    auto citor = intFields_.find(fieldName);
    if (citor != intFields_.cend()) {
        return citor->second[targetIndex];
    } else {
        return 0;
    }
}

geo3dml::ShapeProperty& ShapeProperty::IntValue(const std::string& fieldName, int targetIndex, int v) {
    auto itor = intFields_.find(fieldName);
    if (itor != intFields_.end()) {
        itor->second[targetIndex] = v;
    }
    return *this;
}

void ShapeProperty::FillBooleanValue(const std::string& fieldName, int numberOfValues, bool v) {
    Field field = GetField(fieldName);
    if (field.DataType() != Field::ValueType::Boolean) {
        return;
    }
    auto itor = boolFields_.find(fieldName);
    if (itor == boolFields_.end()) {
        boolFields_[fieldName] = std::vector<bool>(numberOfValues, v);
    } else {
        itor->second.assign(numberOfValues, v);
    }
}

bool ShapeProperty::BooleanValue(const std::string& fieldName, int targetIndex) const {
    auto citor = boolFields_.find(fieldName);
    if (citor != boolFields_.cend()) {
        return citor->second[targetIndex];
    } else {
        return false;
    }
}

geo3dml::ShapeProperty& ShapeProperty::BooleanValue(const std::string& fieldName, int targetIndex, bool v) {
    auto itor = boolFields_.find(fieldName);
    if (itor != boolFields_.end()) {
        itor->second[targetIndex] = v;
    }
    return *this;
}

double ShapeProperty::DoubleValue(int fieldIndex, int targetIndex) const {
    const auto& field = GetFieldAt(fieldIndex);
    return DoubleValue(field.Name(), targetIndex);
}

geo3dml::ShapeProperty& ShapeProperty::DoubleValue(int fieldIndex, int targetIndex, double v) {
    const auto& field = GetFieldAt(fieldIndex);
    return DoubleValue(field.Name(), targetIndex, v);
}

std::string ShapeProperty::TextValue(int fieldIndex, int targetIndex) const {
    const auto& field = GetFieldAt(fieldIndex);
    return TextValue(field.Name(), targetIndex);
}

geo3dml::ShapeProperty& ShapeProperty::TextValue(int fieldIndex, int targetIndex, const std::string& v) {
    const auto& field = GetFieldAt(fieldIndex);
    return TextValue(field.Name(), targetIndex, v);
}

int ShapeProperty::IntValue(int fieldIndex, int targetIndex) const {
    const auto& field = GetFieldAt(fieldIndex);
    return IntValue(field.Name(), targetIndex);
}

geo3dml::ShapeProperty& ShapeProperty::IntValue(int fieldIndex, int targetIndex, int v) {
    const auto& field = GetFieldAt(fieldIndex);
    return IntValue(field.Name(), targetIndex, v);
}

bool ShapeProperty::BooleanValue(int fieldIndex, int targetIndex) const {
    const auto& field = GetFieldAt(fieldIndex);
    return BooleanValue(field.Name(), targetIndex);
}

geo3dml::ShapeProperty& ShapeProperty::BooleanValue(int fieldIndex, int targetIndex, bool v) {
    const auto& field = GetFieldAt(fieldIndex);
    return BooleanValue(field.Name(), targetIndex, v);
}

int ShapeProperty::GetValueCount(int fieldIndex) const {
    const Field& field = GetFieldAt(fieldIndex);
    switch (field.DataType()) {
    case Field::ValueType::Integer: {
        auto citor = intFields_.find(field.Name());
        if (citor != intFields_.cend()) {
            return citor->second.size();
        } else {
            break;
        }
    }
    case Field::ValueType::Double: {
        auto citor = doubleFields_.find(field.Name());
        if (citor != doubleFields_.cend()) {
            return citor->second.size();
        } else {
            break;
        }
    }
    case Field::ValueType::Boolean: {
        auto citor = boolFields_.find(field.Name());
        if (citor != boolFields_.cend()) {
            return citor->second.size();
        } else {
            break;
        }
    }
    case Field::ValueType::Text:
    case Field::ValueType::Category: {
        auto citor = textFields_.find(field.Name());
        if (citor != textFields_.cend()) {
            return citor->second.size();
        } else {
            break;
        }
    }
    default:
        break;
    }
    return 0;
}

int ShapeProperty::GetValueCount(const std::string& fieldName) const {
    int fieldIndex = GetFieldIndex(fieldName);
    if (fieldIndex >= 0) {
        return GetValueCount(fieldIndex);
    } else {
        return 0;
    }
}
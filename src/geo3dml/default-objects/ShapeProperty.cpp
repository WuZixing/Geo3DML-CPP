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
    int fieldIndex = GetFieldIndex(field.Name());
    auto itor = doubleFields_.find(fieldIndex);
    if (itor == doubleFields_.end()) {
        doubleFields_[fieldIndex] = std::vector<double>(numberOfValues, v);
    } else {
        itor->second.assign(numberOfValues, v);
    }
}

double ShapeProperty::DoubleValue(const std::string& fieldName, int targetIndex) const {
    int fieldIndex = GetFieldIndex(fieldName);
    return DoubleValue(fieldIndex, targetIndex);
}

geo3dml::ShapeProperty& ShapeProperty::DoubleValue(const std::string& fieldName, int targetIndex, double v) {
    int fieldIndex = GetFieldIndex(fieldName);
    return DoubleValue(fieldIndex, targetIndex, v);
}

void ShapeProperty::FillTextValue(const std::string& fieldName, int numberOfValues, const std::string& v) {
    Field field = GetField(fieldName);
    if (field.DataType() != Field::ValueType::Text && field.DataType() != Field::ValueType::Category) {
        return;
    }
    int fieldIndex = GetFieldIndex(field.Name());
    auto itor = textFields_.find(fieldIndex);
    if (itor == textFields_.end()) {
        textFields_[fieldIndex] = std::vector<std::string>(numberOfValues, v);
    } else {
        itor->second.assign(numberOfValues, v);
    }
}

std::string ShapeProperty::TextValue(const std::string& fieldName, int targetIndex) const {
    int fieldIndex = GetFieldIndex(fieldName);
    return TextValue(fieldIndex, targetIndex);
}

geo3dml::ShapeProperty& ShapeProperty::TextValue(const std::string& fieldName, int targetIndex, const std::string& v) {
    int fieldIndex = GetFieldIndex(fieldName);
    return TextValue(fieldIndex, targetIndex, v);
}

void ShapeProperty::FillIntValue(const std::string& fieldName, int numberOfValues, int v) {
    Field field = GetField(fieldName);
    if (field.DataType() != Field::ValueType::Integer) {
        return;
    }
    int fieldIndex = GetFieldIndex(fieldName);
    auto itor = intFields_.find(fieldIndex);
    if (itor == intFields_.end()) {
        intFields_[fieldIndex] = std::vector<int>(numberOfValues, v);
    } else {
        itor->second.assign(numberOfValues, v);
    }
}

int ShapeProperty::IntValue(const std::string& fieldName, int targetIndex) const {
    int fieldIndex = GetFieldIndex(fieldName);
    return IntValue(fieldIndex, targetIndex);
}

geo3dml::ShapeProperty& ShapeProperty::IntValue(const std::string& fieldName, int targetIndex, int v) {
    int fieldIndex = GetFieldIndex(fieldName);
    return IntValue(fieldIndex, targetIndex, v);
}

void ShapeProperty::FillBooleanValue(const std::string& fieldName, int numberOfValues, bool v) {
    Field field = GetField(fieldName);
    if (field.DataType() != Field::ValueType::Boolean) {
        return;
    }
    int fieldIndex = GetFieldIndex(fieldName);
    auto itor = boolFields_.find(fieldIndex);
    if (itor == boolFields_.end()) {
        boolFields_[fieldIndex] = std::vector<bool>(numberOfValues, v);
    } else {
        itor->second.assign(numberOfValues, v);
    }
}

bool ShapeProperty::BooleanValue(const std::string& fieldName, int targetIndex) const {
    int fieldIndex = GetFieldIndex(fieldName);
    return BooleanValue(fieldIndex, targetIndex);
}

geo3dml::ShapeProperty& ShapeProperty::BooleanValue(const std::string& fieldName, int targetIndex, bool v) {
    int fieldIndex = GetFieldIndex(fieldName);
    return BooleanValue(fieldIndex, targetIndex, v);
}

double ShapeProperty::DoubleValue(int fieldIndex, int targetIndex) const {
    auto citor = doubleFields_.find(fieldIndex);
    if (citor != doubleFields_.cend()) {
        return citor->second[targetIndex];
    } else {
        return 0;
    }
}

geo3dml::ShapeProperty& ShapeProperty::DoubleValue(int fieldIndex, int targetIndex, double v) {
    auto itor = doubleFields_.find(fieldIndex);
    if (itor == doubleFields_.end()) {
        doubleFields_[fieldIndex] = std::vector<double>(targetIndex + 1, v);
    } else {
        // 只允许向当前数组末尾添加元素。
        if (targetIndex < itor->second.size()) {
            itor->second[targetIndex] = v;
        } else if (targetIndex == itor->second.size()){
            itor->second.push_back(v);
        }
    }
    return *this;
}

std::string ShapeProperty::TextValue(int fieldIndex, int targetIndex) const {
    auto citor = textFields_.find(fieldIndex);
    if (citor != textFields_.cend()) {
        return citor->second[targetIndex];
    } else {
        return std::string();
    }
}

geo3dml::ShapeProperty& ShapeProperty::TextValue(int fieldIndex, int targetIndex, const std::string& v) {
    auto itor = textFields_.find(fieldIndex);
    if (itor == textFields_.end()) {
        textFields_[fieldIndex] = std::vector<std::string>(targetIndex + 1, v);
    } else {
        if (targetIndex < itor->second.size()) {
            itor->second[targetIndex] = v;
        } else if (targetIndex == itor->second.size()) {
            itor->second.emplace_back(v);
        }
    }
    return *this;
}

int ShapeProperty::IntValue(int fieldIndex, int targetIndex) const {
    auto citor = intFields_.find(fieldIndex);
    if (citor != intFields_.cend()) {
        return citor->second[targetIndex];
    } else {
        return 0;
    }
}

geo3dml::ShapeProperty& ShapeProperty::IntValue(int fieldIndex, int targetIndex, int v) {
    auto itor = intFields_.find(fieldIndex);
    if (itor == intFields_.end()) {
        intFields_[fieldIndex] = std::vector<int>(targetIndex + 1, v);
    } else {
        if (targetIndex < itor->second.size()) {
            itor->second[targetIndex] = v;
        } else if (targetIndex == itor->second.size()) {
            itor->second.push_back(v);
        }
    }
    return *this;
}

bool ShapeProperty::BooleanValue(int fieldIndex, int targetIndex) const {
    auto citor = boolFields_.find(fieldIndex);
    if (citor != boolFields_.cend()) {
        return citor->second[targetIndex];
    } else {
        return false;
    }
}

geo3dml::ShapeProperty& ShapeProperty::BooleanValue(int fieldIndex, int targetIndex, bool v) {
    auto itor = boolFields_.find(fieldIndex);
    if (itor == boolFields_.end()) {
        boolFields_[fieldIndex] = std::vector<bool>(targetIndex + 1, v);
    } else {
        if (targetIndex < itor->second.size()) {
            itor->second[targetIndex] = v;
        } else if (targetIndex == itor->second.size()){
            itor->second.push_back(v);
        }
    }
    return *this;
}

int ShapeProperty::GetValueCount(int fieldIndex) const {
    const Field& field = GetFieldAt(fieldIndex);
    switch (field.DataType()) {
    case Field::ValueType::Integer: {
        auto citor = intFields_.find(fieldIndex);
        if (citor != intFields_.cend()) {
            return citor->second.size();
        } else {
            break;
        }
    }
    case Field::ValueType::Double: {
        auto citor = doubleFields_.find(fieldIndex);
        if (citor != doubleFields_.cend()) {
            return citor->second.size();
        } else {
            break;
        }
    }
    case Field::ValueType::Boolean: {
        auto citor = boolFields_.find(fieldIndex);
        if (citor != boolFields_.cend()) {
            return citor->second.size();
        } else {
            break;
        }
    }
    case Field::ValueType::Text:
    case Field::ValueType::Category: {
        auto citor = textFields_.find(fieldIndex);
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
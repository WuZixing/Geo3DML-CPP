#include <g3dvtk/ShapeProperty.h>
#include <vtkDoubleArray.h>
#include <vtkStringArray.h>
#include <vtkIntArray.h>
#include <vtkUnsignedCharArray.h>

using namespace g3dvtk;

ShapeProperty::ShapeProperty() {
	dataSet_ = vtkSmartPointer<vtkDataSetAttributes>::New();
	baseIndexOfFields_ = dataSet_->GetNumberOfArrays();
}

ShapeProperty::~ShapeProperty() {

}

void ShapeProperty::BindDataSet(vtkDataSetAttributes* ds) {
	g3d_lock_guard lck(mtx_);
	// substitue ds for dataset_.
	baseIndexOfFields_ = ds->GetNumberOfArrays();
	int arrayNum = dataSet_->GetNumberOfArrays();
	for (int i = 0; i < arrayNum; ++i) {
		ds->AddArray(dataSet_->GetAbstractArray(i));
	}
	dataSet_ = ds;
}

bool ShapeProperty::AddField(const geo3dml::Field& f) {
	g3d_lock_guard lck(mtx_);
	switch (f.DataType()) {
	case geo3dml::Field::Boolean:
	case geo3dml::Field::Double:
	case geo3dml::Field::Integer:
	case geo3dml::Field::Text:
		break;
	default:
		return false;
	}
	if (!geo3dml::ShapeProperty::AddField(f)) {
		return false;
	}
	// change field's temporary name to real name.
	std::string fieldName = f.Name();
	int fieldIndex = GetFieldIndex(fieldName);
	vtkAbstractArray* dataArray = dataSet_->GetAbstractArray(GetTemporaryNameOfField(fieldIndex).c_str());
	if (dataArray != NULL) {
		dataArray->SetName(fieldName.c_str());
	} else {
		switch (f.DataType()) {
		case geo3dml::Field::Boolean: {
			vtkSmartPointer<vtkUnsignedCharArray> charArray = vtkSmartPointer<vtkUnsignedCharArray>::New();
			charArray->SetName(fieldName.c_str());
			dataSet_->AddArray(charArray);
			break;
		}
		case geo3dml::Field::Double: {
			vtkSmartPointer<vtkDoubleArray> doubleArray = vtkSmartPointer<vtkDoubleArray>::New();
			doubleArray->SetName(fieldName.c_str());
			dataSet_->AddArray(doubleArray);
			break;
		}
		case geo3dml::Field::Integer: {
			vtkSmartPointer<vtkIntArray> intArray = vtkSmartPointer<vtkIntArray>::New();
			intArray->SetName(fieldName.c_str());
			dataSet_->AddArray(intArray);
			break;
		}
		case geo3dml::Field::Text: {
			vtkSmartPointer<vtkStringArray> stringArray = vtkSmartPointer<vtkStringArray>::New();
			stringArray->SetName(fieldName.c_str());
			dataSet_->AddArray(stringArray);
			break;
		}
		default:
			break;
		}
	}
	return true;
}

void ShapeProperty::FillDoubleValue(const std::string field, int numberOfValues, double v) {
	g3d_lock_guard lck(mtx_);
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(field.c_str());
	if (ary == NULL) {
		vtkSmartPointer<vtkDoubleArray> dataArray = vtkSmartPointer<vtkDoubleArray>::New();
		dataArray->SetName(field.c_str());
		dataArray->SetNumberOfComponents(1);
		dataArray->SetNumberOfTuples(numberOfValues);
		dataArray->Fill(v);
		dataArray->Modified();
		dataSet_->AddArray(dataArray);
	} else {
		vtkDoubleArray* doubleArray = vtkDoubleArray::SafeDownCast(ary);
		if (doubleArray != NULL) {
			doubleArray->SetNumberOfTuples(numberOfValues);
			doubleArray->Fill(v);
			doubleArray->Modified();
		}
	}
}

double ShapeProperty::DoubleValue(const std::string& field, int targetIndex) {
	g3d_lock_guard lck(mtx_);
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(field.c_str());
	if (ary == NULL) {
		return 0;
	}
	vtkDoubleArray* doubleArray = vtkDoubleArray::SafeDownCast(ary);
	if (doubleArray != NULL) {
		return doubleArray->GetValue(targetIndex);
	} else {
		return 0;
	}
}

ShapeProperty& ShapeProperty::DoubleValue(const std::string& field, int targetIndex, double v) {
	g3d_lock_guard lck(mtx_);
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(field.c_str());
	if (ary == NULL) {
		vtkSmartPointer<vtkDoubleArray> dataArray = vtkSmartPointer<vtkDoubleArray>::New();
		dataArray->SetName(field.c_str());
		dataArray->SetNumberOfComponents(1);
		dataSet_->AddArray(dataArray);
		ary = dataArray.Get();
	}
	vtkDoubleArray* doubleArray = vtkDoubleArray::SafeDownCast(ary);
	if (doubleArray == NULL) {
		return *this;
	}
	doubleArray->InsertValue(targetIndex, v);
	doubleArray->Modified();
	return *this;
}

void ShapeProperty::FillTextValue(const std::string& field, int numberOfValues, const std::string& v) {
	g3d_lock_guard lck(mtx_);
	vtkStringArray* stringArray = NULL;
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(field.c_str());
	if (ary == NULL) {
		vtkSmartPointer<vtkStringArray> dataArray = vtkSmartPointer<vtkStringArray>::New();
		dataArray->SetName(field.c_str());
		dataArray->SetNumberOfComponents(1);
		dataSet_->AddArray(dataArray);
		stringArray = dataArray.Get();
	} else {
		stringArray = vtkStringArray::SafeDownCast(ary);
	}
	if (stringArray != NULL) {
		stringArray->SetNumberOfTuples(numberOfValues);
		for (int i = 0; i < numberOfValues; ++i) {
			stringArray->SetValue(i, v.c_str());
		}
		stringArray->Modified();
	}
}

std::string ShapeProperty::TextValue(const std::string& field, int targetIndex) {
	g3d_lock_guard lck(mtx_);
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(field.c_str());
	if (ary == NULL) {
		return "";
	}
	vtkStringArray* stringArray = vtkStringArray::SafeDownCast(ary);
	if (stringArray != NULL) {
		return stringArray->GetValue(targetIndex);
	} else {
		return "";
	}
}

ShapeProperty& ShapeProperty::TextValue(const std::string& field, int targetIndex, const std::string& v) {
	g3d_lock_guard lck(mtx_);
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(field.c_str());
	if (ary == NULL) {
		vtkSmartPointer<vtkStringArray> dataArray = vtkSmartPointer<vtkStringArray>::New();
		dataArray->SetName(field.c_str());
		dataArray->SetNumberOfComponents(1);
		dataSet_->AddArray(dataArray);
		ary = dataArray;
	}
	vtkStringArray* stringArray = vtkStringArray::SafeDownCast(ary);
	if (stringArray == NULL) {
		return *this;
	}
	stringArray->InsertValue(targetIndex, v.c_str());
	stringArray->Modified();
	return *this;
}

void ShapeProperty::FillIntValue(const std::string& field, int numberOfValues, int v) {
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(field.c_str());
	if (ary == NULL) {
		vtkSmartPointer<vtkIntArray> dataArray = vtkSmartPointer<vtkIntArray>::New();
		dataArray->SetName(field.c_str());
		dataArray->SetNumberOfComponents(1);
		dataArray->SetNumberOfTuples(numberOfValues);
		dataArray->Fill(v);
		dataArray->Modified();
		dataSet_->AddArray(dataArray);
	} else {
		vtkIntArray* intArray = vtkIntArray::SafeDownCast(ary);
		if (intArray != NULL) {
			intArray->SetNumberOfTuples(numberOfValues);
			intArray->Fill(v);
			intArray->Modified();
		}
	}
}

int ShapeProperty::IntValue(const std::string& field, int targetIndex) {
	g3d_lock_guard lck(mtx_);
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(field.c_str());
	if (ary == NULL) {
		return 0;
	}
	vtkIntArray* intArray = vtkIntArray::SafeDownCast(ary);
	if (intArray != NULL) {
		return intArray->GetValue(targetIndex);
	} else {
		return 0;
	}
}

ShapeProperty& ShapeProperty::IntValue(const std::string& field, int targetIndex, int v) {
	g3d_lock_guard lck(mtx_);
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(field.c_str());
	if (ary == NULL) {
		vtkSmartPointer<vtkIntArray> dataArray = vtkSmartPointer<vtkIntArray>::New();
		dataArray->SetName(field.c_str());
		dataArray->SetNumberOfComponents(1);
		dataSet_->AddArray(dataArray);
		ary = dataArray.Get();
	}
	vtkIntArray* intArray = vtkIntArray::SafeDownCast(ary);
	if (intArray == NULL) {
		return *this;
	}
	intArray->InsertValue(targetIndex, v);
	intArray->Modified();
	return *this;
}

void ShapeProperty::FillBooleanValue(const std::string& field, int numberOfValues, bool v) {
	unsigned char cv = v ? (unsigned char)1 : (unsigned char)0;
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(field.c_str());
	if (ary == NULL) {
		vtkSmartPointer<vtkUnsignedCharArray> dataArray = vtkSmartPointer<vtkUnsignedCharArray>::New();
		dataArray->SetName(field.c_str());
		dataArray->SetNumberOfComponents(1);
		dataArray->SetNumberOfTuples(numberOfValues);
		dataArray->Fill(cv);
		dataArray->Modified();
		dataSet_->AddArray(dataArray);
	} else {
		vtkUnsignedCharArray* charArray = vtkUnsignedCharArray::SafeDownCast(ary);
		if (charArray != NULL) {
			charArray->SetNumberOfTuples(numberOfValues);
			charArray->Fill(cv);
			charArray->Modified();
		}
	}
}

bool ShapeProperty::BooleanValue(const std::string& field, int targetIndex) {
	g3d_lock_guard lck(mtx_);
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(field.c_str());
	if (ary == NULL) {
		return false;
	}
	vtkUnsignedCharArray* charArray = vtkUnsignedCharArray::SafeDownCast(ary);
	if (charArray != NULL) {
		return charArray->GetValue(targetIndex);
	} else {
		return false;
	}
}

ShapeProperty& ShapeProperty::BooleanValue(const std::string& field, int targetIndex, bool v) {
	g3d_lock_guard lck(mtx_);
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(field.c_str());
	if (ary == NULL) {
		vtkSmartPointer<vtkUnsignedCharArray> dataArray = vtkSmartPointer<vtkUnsignedCharArray>::New();
		dataArray->SetName(field.c_str());
		dataArray->SetNumberOfComponents(1);
		dataSet_->AddArray(dataArray);
		ary = dataArray.Get();
	}
	vtkUnsignedCharArray* charArray = vtkUnsignedCharArray::SafeDownCast(ary);
	if (charArray == NULL) {
		return *this;
	}
	charArray->InsertValue(targetIndex, v ? (unsigned char)1 : (unsigned char)0);
	charArray->Modified();
	return *this;
}

double ShapeProperty::DoubleValue(int fieldIndex, int targetIndex) {
	g3d_lock_guard lck(mtx_);
	std::string fieldName;
	if (fieldIndex < GetFieldCount()) {
		fieldName = GetFieldAt(fieldIndex).Name();
	} else {
		fieldName = GetTemporaryNameOfField(fieldIndex);
	}
	return DoubleValue(fieldName, targetIndex);
}

ShapeProperty& ShapeProperty::DoubleValue(int fieldIndex, int targetIndex, double v) {
	g3d_lock_guard lck(mtx_);
	std::string fieldName;
	if (fieldIndex < GetFieldCount()) {
		fieldName = GetFieldAt(fieldIndex).Name();
	} else {
		fieldName = GetTemporaryNameOfField(fieldIndex);
	}
	return DoubleValue(fieldName, targetIndex, v);
}

std::string ShapeProperty::TextValue(int fieldIndex, int targetIndex) {
	g3d_lock_guard lck(mtx_);
	std::string fieldName;
	if (fieldIndex < GetFieldCount()) {
		fieldName = GetFieldAt(fieldIndex).Name();
	} else {
		fieldName = GetTemporaryNameOfField(fieldIndex);
	}
	return TextValue(fieldName, targetIndex);
}

ShapeProperty& ShapeProperty::TextValue(int fieldIndex, int targetIndex, const std::string& v) {
	g3d_lock_guard lck(mtx_);
	std::string fieldName;
	if (fieldIndex < GetFieldCount()) {
		fieldName = GetFieldAt(fieldIndex).Name();
	} else {
		fieldName = GetTemporaryNameOfField(fieldIndex);
	}
	return TextValue(fieldName, targetIndex, v);
}

int ShapeProperty::IntValue(int fieldIndex, int targetIndex) {
	g3d_lock_guard lck(mtx_);
	std::string fieldName;
	if (fieldIndex < GetFieldCount()) {
		fieldName = GetFieldAt(fieldIndex).Name();
	} else {
		fieldName = GetTemporaryNameOfField(fieldIndex);
	}
	return IntValue(fieldName, targetIndex);
}

ShapeProperty& ShapeProperty::IntValue(int fieldIndex, int targetIndex, int v) {
	g3d_lock_guard lck(mtx_);
	std::string fieldName;
	if (fieldIndex < GetFieldCount()) {
		fieldName = GetFieldAt(fieldIndex).Name();
	} else {
		fieldName = GetTemporaryNameOfField(fieldIndex);
	}
	return IntValue(fieldName, targetIndex, v);
}

bool ShapeProperty::BooleanValue(int fieldIndex, int targetIndex) {
	g3d_lock_guard lck(mtx_);
	std::string fieldName;
	if (fieldIndex < GetFieldCount()) {
		fieldName = GetFieldAt(fieldIndex).Name();
	} else {
		fieldName = GetTemporaryNameOfField(fieldIndex);
	}
	return BooleanValue(fieldName, targetIndex);
}

ShapeProperty& ShapeProperty::BooleanValue(int fieldIndex, int targetIndex, bool v) {
	g3d_lock_guard lck(mtx_);
	std::string fieldName;
	if (fieldIndex < GetFieldCount()) {
		fieldName = GetFieldAt(fieldIndex).Name();
	} else {
		fieldName = GetTemporaryNameOfField(fieldIndex);
	}
	return BooleanValue(fieldName, targetIndex, v);
}

int ShapeProperty::GetValueCount(int fieldIndex) {
	g3d_lock_guard lck(mtx_);
	std::string fieldName;
	if (fieldIndex < GetFieldCount()) {
		fieldName = GetFieldAt(fieldIndex).Name();
	} else {
		fieldName = GetTemporaryNameOfField(fieldIndex);
	}
	return GetValueCount(fieldName);
}

int ShapeProperty::GetValueCount(const std::string& fieldName) {
	g3d_lock_guard lck(mtx_);
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(fieldName.c_str());
	if (ary != NULL) {
		return ary->GetNumberOfTuples();
	} else {
		return 0;
	}
}

std::string ShapeProperty::GetTemporaryNameOfField(int fieldIndex) {
	char name[64] = {'\0'};
	snprintf(name, 64, "_%d_", fieldIndex);
	return name;
}

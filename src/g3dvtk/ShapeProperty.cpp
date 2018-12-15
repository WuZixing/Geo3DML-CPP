#include <g3dvtk/ShapeProperty.h>
#include <vtkDoubleArray.h>
#include <vtkStringArray.h>
#include <vtkIntArray.h>
#include <vtkUnsignedCharArray.h>

using namespace g3dvtk;

ShapeProperty::ShapeProperty() {
	dataSet_ = vtkDataSetAttributes::New();
}

ShapeProperty::~ShapeProperty() {

}

void ShapeProperty::BindDataSet(vtkDataSetAttributes* ds) {
	g3d_lock_guard lck(mtx_);
	// substitue ds for dataset_.
	int arrayNum = dataSet_->GetNumberOfArrays();
	for (int i = 0; i < arrayNum; ++i) {
		ds->AddArray(dataSet_->GetAbstractArray(i));
	}
	dataSet_->Delete();
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
	vtkAbstractArray* dataArray = dataSet_->GetAbstractArray(f.Name().c_str());
	if (dataArray == NULL) {
		switch (f.DataType()) {
		case geo3dml::Field::Boolean: {
			vtkSmartPointer<vtkUnsignedCharArray> charArray = vtkSmartPointer<vtkUnsignedCharArray>::New();
			charArray->SetName(f.Name().c_str());
			dataSet_->AddArray(charArray);
			break;
		}
		case geo3dml::Field::Double: {
			vtkSmartPointer<vtkDoubleArray> doubleArray = vtkSmartPointer<vtkDoubleArray>::New();
			doubleArray->SetName(f.Name().c_str());
			dataSet_->AddArray(doubleArray);
			break;
		}
		case geo3dml::Field::Integer: {
			vtkSmartPointer<vtkIntArray> intArray = vtkSmartPointer<vtkIntArray>::New();
			intArray->SetName(f.Name().c_str());
			dataSet_->AddArray(intArray);
			break;
		}
		case geo3dml::Field::Text: {
			vtkSmartPointer<vtkStringArray> stringArray = vtkSmartPointer<vtkStringArray>::New();
			stringArray->SetName(f.Name().c_str());
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
	// vtkDatasetAttributes may hava a default attibute of ghost cells, so the actual field index in vtkDatasetAttributes may not equal to this fieldIndex,
	// which means check field by name is the safe way to visit the right attibute.
	const geo3dml::Field& field = GetFieldAt(fieldIndex);
	return DoubleValue(field.Name(), targetIndex);
}

ShapeProperty& ShapeProperty::DoubleValue(int fieldIndex, int targetIndex, double v) {
	g3d_lock_guard lck(mtx_);
	const geo3dml::Field& field = GetFieldAt(fieldIndex);
	return DoubleValue(field.Name(), targetIndex, v);
}

std::string ShapeProperty::TextValue(int fieldIndex, int targetIndex) {
	g3d_lock_guard lck(mtx_);
	const geo3dml::Field& field = GetFieldAt(fieldIndex);
	return TextValue(field.Name(), targetIndex);
}

ShapeProperty& ShapeProperty::TextValue(int fieldIndex, int targetIndex, const std::string& v) {
	g3d_lock_guard lck(mtx_);
	const geo3dml::Field& field = GetFieldAt(fieldIndex);
	return TextValue(field.Name(), targetIndex, v);
}

int ShapeProperty::IntValue(int fieldIndex, int targetIndex) {
	g3d_lock_guard lck(mtx_);
	const geo3dml::Field& field = GetFieldAt(fieldIndex);
	return IntValue(field.Name(), targetIndex);
}

ShapeProperty& ShapeProperty::IntValue(int fieldIndex, int targetIndex, int v) {
	g3d_lock_guard lck(mtx_);
	const geo3dml::Field& field = GetFieldAt(fieldIndex);
	return IntValue(field.Name(), targetIndex, v);
}

bool ShapeProperty::BooleanValue(int fieldIndex, int targetIndex) {
	g3d_lock_guard lck(mtx_);
	const geo3dml::Field& field = GetFieldAt(fieldIndex);
	return BooleanValue(field.Name(), targetIndex);
}

ShapeProperty& ShapeProperty::BooleanValue(int fieldIndex, int targetIndex, bool v) {
	g3d_lock_guard lck(mtx_);
	const geo3dml::Field& field = GetFieldAt(fieldIndex);
	return BooleanValue(field.Name(), targetIndex, v);
}

int ShapeProperty::GetValueCount(int fieldIndex) {
	g3d_lock_guard lck(mtx_);
	const geo3dml::Field& field = GetFieldAt(fieldIndex);
	vtkAbstractArray* ary = dataSet_->GetAbstractArray(field.Name().c_str());
	if (ary != NULL) {
		return ary->GetNumberOfTuples();
	} else {
		return 0;
	}
}

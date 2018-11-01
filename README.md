# Geo3DML-CPP

Geo3DML C++ SDK.

包含三个库：

1. **geo3dml**

定义Geo3DML规定的数据结构。
其中，几何数据结构是抽象的，开发者可以基于自有系统的内部数据结构来实现，以期达到导入导出Geo3DML数据时避免内存数据相互转换的目的。

2. **g3dxml**

Geo3DML XML文件读写库。仅支持UTF8编码。

3. **g3dvtk**

可选。基于VTK实现了Geo3DML的几何数据结构。
